///////////////////////////////////////////////////////////////////////
//	
//	main.cpp
//	
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "debug.h"
#include "settingsmap.h"
#include "render.h"
#include "uibutton.h"

SDL_Window *window;
SDL_Renderer *renderer;

SettingsMap Settings;

std::map< std::string, UIButton > MainMenuButtons;

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

	//Engine shutdown
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////////////////////////

int MainMenu_Init(int x, int y)
{	
	UIButton btn;
	std::vector<int> vec(2);
	
	btn.renderer = renderer;
	btn.w = 235;
	btn.h = 43;
	btn.state = 0;

	for (int i = 0; i <= 9; i++)
	{
		btn.x = x;
		btn.y = y;

		btn.actorVertices.clear();

		vec[0] = btn.x;
		vec[1] = btn.y;
		btn.actorVertices.push_back( vec );

		vec[0] = -((btn.x + btn.w) - 1);
		vec[1] = btn.y;
		btn.actorVertices.push_back( vec );

		vec[0] = -((btn.x + btn.w) - 1);
		vec[1] = -((btn.y + btn.h) - 1);
		btn.actorVertices.push_back( vec );

		vec[0] = btn.x;
		vec[1] = -((btn.y + btn.h) - 1);
		btn.actorVertices.push_back( vec );
		
		MainMenuButtons["BTN_ID_" + std::to_string(i)] = btn;

		y += (btn.h + 15);
	}

	return 0;
}

std::vector< int>* MainMenu_Click(int mx, int my)
{
	std::vector< std::vector<int> > actorVtcs(4);
	std::vector< int > vtx;
	
	UIButton btn;
	bool vtxX = false;
	bool vtxY = false;
	int vtxpc;

	std::map< std::string, UIButton >::iterator a;
	for (a = MainMenuButtons.begin(); a != MainMenuButtons.end(); a++)
	{
		actorVtcs = a->second.actorVertices;
		
		vtxpc = 0;
		
		std::vector< std::vector<int> >::iterator b;
		for (b = actorVtcs.begin(); b != actorVtcs.end(); b++)
		{
			vtx = *b;

			vtxX = false;
			vtxY = false;

			mx = std::abs(mx);
			my = std::abs(my);
			
			if (vtx[0] < 0) 
				mx = -1 * mx;
			
			if (vtx[1] < 0) 
				my = -1 * my;
			
			// test X
			if (mx >= vtx[0])
				vtxX = true;

			// test Y
			if (my >= vtx[1]) 
				vtxY = true;

			if (vtxX && vtxY)
				vtxpc++;
			
			std::cout << "mx(" << mx << ") vx(" << vtx[0] << ") | " 
				      << "my(" << my << ") vy(" << vtx[1] << ") >>> " << vtxX <<' ' <<vtxY<<  std::endl;
		}

		std::cout << std::endl;

		if (vtxpc == actorVtcs.size())
		{
			//return &vtx;
			std::cout << "button clicked! >> actor " << a->first << " " << vtxpc << "/" << actorVtcs.size() << std::endl << std::endl;
			MainMenuButtons[a->first].state=1;
			break;
		}
	}

	return NULL;
}

int MainMenu_Draw()
{
	UIButton btn;
	
	std::map< std::string, UIButton >::iterator i;
	for (i = MainMenuButtons.begin(); i != MainMenuButtons.end(); i++)
	{
		btn = i->second;
		std::cout<< btn.state << std::endl;
		btn.Draw();
	}

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////////////////////////

int processEvents(SDL_Event *pEvents, bool *pQuit)
{
	SDL_Event events = *pEvents;
	std::vector <int>* button_clicked;

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
				button_clicked = MainMenu_Click(events.button.x, events.button.y);
				break;

			case SDL_BUTTON_RIGHT:
				break;

			default:
				break;
		}
	}

	return 0;
}

int renderGameState() 
{
	MainMenu_Draw();

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
	engineInit();
	
	Settings.SetValue("App.Title", "Project \"BOOT\"");
	Settings.SetValue("App.Version", "0.0.0 dev");
	
	Settings.LoadIni("config/settings.ini");
	
	std::string str = Settings.GetValue("App.Title");
	char *cstr = new char [str.length()+1];
	std::strcpy (cstr, str.c_str());
	const char *APP_NAME = cstr;
			
	int ResW = std::stoi(Settings.GetValue("Engine.Screen.Width"));
	int ResH = std::stoi(Settings.GetValue("Engine.Screen.Height"));

	window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ResW, ResH, SDL_WINDOW_SHOWN);
	if (window == nullptr) { logSDLError(std::cout, "CreateWindow"); return 2; }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) { logSDLError(std::cout, "CreateRenderer"); return 3; }

	MainMenu_Init(110, 85);

	gameLoop();

	// TEST: Save Ini
	//Settings.SaveIni();

	engineShutdown();
		
	return 0;
}