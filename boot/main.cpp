#include "main.h"

#include "setmap.h"
#include "render.h"
#include "render_startup.h"

int main( int argc, 
		  char* *argv );

int gameLoop();

int processEvents( SDL_Event *eventsptr,
				   bool *quitptr );

int renderGameState();

int engineInit();
int engineShutdown();

SDL_Window *window;
SDL_Renderer *renderer;

SettingsMap Settings;

int main( int argc, 
		  char **argv ) 
{
	engineInit();

	Settings.SetValue("App.Title", "Project \"BOOT\"");
	Settings.SetValue("App.Version", "0.0.0 dev");
	
	Settings.LoadIni("config/settings.ini");
	
	std::string str = Settings.GetValue("App.Title");
	char* cstr = new char [ str.length() + 1 ];
	std::strcpy (cstr, str.c_str());
	const char* APP_NAME = cstr;
	
	int ResW = std::stoi( Settings.GetValue("Engine.Screen.Width") );
	int ResH = std::stoi( Settings.GetValue("Engine.Screen.Height") );

	window = SDL_CreateWindow( APP_NAME, 
		                       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							   ResW, ResH, 
							   SDL_WINDOW_SHOWN );

	if (window == nullptr) { logSDLError(std::cout, "CreateWindow"); return 2; }

	renderer = SDL_CreateRenderer( window, -1, 
		                           SDL_RENDERER_ACCELERATED | 
								   SDL_RENDERER_PRESENTVSYNC );

	if (renderer == nullptr) { logSDLError(std::cout, "CreateRenderer"); return 3; }

	StartupScreen_Init();

	gameLoop();

	// TEST: Save Ini
	//Settings.SaveIni();

	engineShutdown();
		
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

int processEvents( SDL_Event *eventsptr, 
				   bool *quitptr )
{
	SDL_Event &events = *eventsptr;
	bool &quit = *quitptr;

	switch (events.type)
	{
		case SDL_QUIT:
			quit = true;
			break;
		
		case SDL_KEYDOWN:
		{
			switch (events.key.keysym.sym) 
			{
				case SDLK_ESCAPE:
					quit = true;
					break;

				default:
					break;
			}

			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{ 
			switch (events.button.button) 
			{
				case SDL_BUTTON_LEFT:
					StartupScreen_ButtonEventHandler_Mouse( events.button.x, 
													        events.button.y, 
													        MOUSE_CLICK_LEFT );
					break;
				
				case SDL_BUTTON_RIGHT:
					break;

				default:
					break;
			}

			break;
		}

		case SDL_MOUSEMOTION:
		{
			StartupScreen_ButtonEventHandler_Mouse( events.button.x, 
											        events.button.y, 
											        MOUSE_MOTION );
			break;
		}

		default:
			break;
	}

	return 0;
}

int renderGameState() 
{
	StartupScreen_Draw();

	return 0;
}

int engineInit() 
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

	return 0;
}

int engineShutdown() 
{
	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Engine shutdown
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}