///////////////////////////////////////////////////////////////////////
//	main.cpp
///////////////////////////////////////////////////////////////////////

#include "setmap.h"
#include "render.h"
#include "render_opengl.h"
#include "main_menu.h"

SettingsMap Settings;

int engineInit(const char* APP_NAME, int w, int h) 
{
	// Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	// Start up SDL-IMAGE and make sure it went ok
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError(std::cout, "IMG_Init");
		return 1;
	}

	// Start up SDL-TTF and make sure it went ok
	if (TTF_Init() != 0) {
		logSDLError(std::cout, "TTF_Init");
		return 1;
	}

	// Use OpenGL 3.1 core
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	// Create Window and Context
	gWindow = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) { logSDLError(std::cout, "glCreateWindow"); return 2; }

	gContext = SDL_GL_CreateContext( gWindow );
	if (gContext == nullptr) { logSDLError(std::cout, "glCreateContext"); return 3; }

	// Init GLEW?
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) { logSDLError(std::cout, "Init GLEW"); return 4; }

	// Use Vsync
	if (SDL_GL_SetSwapInterval( 1 ) < 0) { logSDLError(std::cout, "VSync"); return 5; }

	return 0;
}

int engineInitGL() 
{
	// Generate program
	gProgramID = glCreateProgram();

	// Create vertex shader
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

	//Get vertex source
	const GLchar* vertexShaderSource[] = {
		"#version 130\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	// Set vertex source
	glShaderSource( vertexShader, 1, vertexShaderSource, NULL );

	// Compile vertex source
	glCompileShader( vertexShader );

	// Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
	if( vShaderCompiled != GL_TRUE )
	{
		printf( "Unable to compile vertex shader %d!\n", vertexShader );
		printShaderLog( vertexShader );
        return 7;
	}
	else
	{
		// Attach vertex shader to program
		glAttachShader( gProgramID, vertexShader );


		// Create fragment shader
		GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

		// Get fragment source
		const GLchar* fragmentShaderSource[] =
		{
			"#version 130\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
		};

		// Set fragment source
		glShaderSource( fragmentShader, 1, fragmentShaderSource, NULL );

		// Compile fragment source
		glCompileShader( fragmentShader );

		// Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled );
		if (fShaderCompiled != GL_TRUE)
		{
			printf( "Unable to compile fragment shader %d!\n", fragmentShader );
			printShaderLog( fragmentShader );
			return 8;
		}
		else
		{
			// Attach fragment shader to program
			glAttachShader( gProgramID, fragmentShader );
			
			// Link program
			glLinkProgram( gProgramID );

			// Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv( gProgramID, GL_LINK_STATUS, &programSuccess );
			if (programSuccess != GL_TRUE)
			{
				printf( "Error linking program %d!\n", gProgramID );
				printProgramLog( gProgramID );
				return 9;
			}
			else
			{
				// Get vertex attribute location
				gVertexPos2DLocation = glGetAttribLocation( gProgramID, "LVertexPos2D" );
				if (gVertexPos2DLocation == -1)
				{
					printf( "LVertexPos2D is not a valid glsl program variable!\n" );
					return 10;
				}
				else
				{
					// Initialize clear color
					glClearColor( 0.f, 0.f, 0.f, 1.f );

					// VBO data
					GLfloat vertexData[] = {
						-0.5f, -0.5f,
						 0.5f, -0.5f,
						 0.5f,  0.5f,
						-0.5f,  0.5f
					};

					// IBO data
					GLuint indexData[] = { 0, 1, 2, 3 };

					// Create VBO
					glGenBuffers( 1, &gVBO );
					glBindBuffer( GL_ARRAY_BUFFER, gVBO );
					glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

					// Create IBO
					glGenBuffers( 1, &gIBO );
					glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
					glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
				}
			}
		}
	}
	
	return 0;
}

int engineShutdown() 
{
	// Cleanup
	
	// Deallocate program
	glDeleteProgram( gProgramID );
	
	SDL_DestroyWindow(window);
	gWindow = NULL;

	// Engine shutdown
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

int processEvents(SDL_Event *pEvents, bool *pQuit)
{
	SDL_Event events = *pEvents;

	if (events.type == SDL_QUIT) *pQuit = true;

	// Keyboard events
	if (events.type == SDL_KEYDOWN) 
	{
		switch (events.key.keysym.sym) 
		{
			case SDLK_ESCAPE:
				*pQuit = true;
				break;

			default:
				break;
		}
	}

	// Mouse button events
	if (events.type == SDL_MOUSEBUTTONDOWN) 
	{
		switch (events.button.button) 
		{
			case SDL_BUTTON_LEFT:
				MainMenu_ButtonEvent(events.button.x, events.button.y, MOUSE_CLICK_LEFT);
				break;

			case SDL_BUTTON_RIGHT:
				break;

			default:
				break;
		}
	}

	if (events.type == SDL_MOUSEMOTION)
		MainMenu_ButtonEvent(events.button.x, events.button.y, MOUSE_MOTION);

	return 0;
}

int renderGameState() 
{
	//MainMenu_Draw();

	return 0;
}

int gameLoop() 
{
	SDL_Event events;

	bool quit = false;

	while (!quit)
	{
		// Event handling - Input
		while (SDL_PollEvent(&events)) 
			processEvents(&events, &quit);

		// Update data
		// 

		// Rendering
		SDL_RenderClear(renderer); // Clear screen
		renderGameState(); // Render the game state
		SDL_RenderPresent(renderer); // Update the screen
	}

	return 0;
}

int main(int argc, char **argv) 
{
	Settings.SetValue("App.Title", "Project \"BOOT\"");
	Settings.SetValue("App.Version", "0.0.0 dev");
	
	Settings.LoadIni("config/settings.ini");
	
	std::string str = Settings.GetValue("App.Title");
	char *cstr = new char [str.length()+1];
	std::strcpy (cstr, str.c_str());
	const char *APP_NAME = cstr;
	
	int ResW = std::stoi(Settings.GetValue("Engine.Screen.Width"));
	int ResH = std::stoi(Settings.GetValue("Engine.Screen.Height"));

	engineInit(APP_NAME, ResW, ResH);

	engineInitGL();

	MainMenu_Init(110, 85);

	gameLoop();

	// TEST: Save Ini
	//Settings.SaveIni();

	engineShutdown();
		
	return 0;
}