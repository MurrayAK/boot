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
#include "settings_map.h"
#include "render.h"
#include "ui_button.h"

enum MouseEvent { MOUSE_CLICK_LEFT, MOUSE_MOTION };

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

bool VectorInVertices(std::vector<int> vec, std::vector< std::vector<int> > vtcs)
{
	std::vector<int> vtx;
	bool vtxX = false;
	bool vtxY = false;
	int vtxpc = 0;

	std::vector< std::vector<int> >::iterator i;
	for (i = vtcs.begin(); i != vtcs.end(); i++)
	{
		vtx = *i;

		vtxX = false;
		vtxY = false;

		vec[0] = std::abs(vec[0]);
		vec[1] = std::abs(vec[1]);
			
		if (vtx[0] < 0) 
			vec[0] = -1 * vec[0];
			
		if (vtx[1] < 0) 
			vec[1] = -1 * vec[1];
			
		// test X
		if (vec[0] >= vtx[0])
			vtxX = true;

		// test Y
		if (vec[1] >= vtx[1]) 
			vtxY = true;

		if (vtxX && vtxY)
			vtxpc++;
		else
			return false;

		//std::cout << "vecx(" << vec[0] << ") vtxx(" << vtx[0] << ") | " 
		//	      << "vecy(" << vec[1] << ") vtxy(" << vtx[1] << ") >>> " << vtxX << " " << vtxY << std::endl;
	}

	std::cout << std::endl;

	if (vtxpc == vtcs.size())
		return true;

	return false;
}

int MainMenu_ButtonEvent_MouseClickLeft(std::string button_id)
{
	if (MainMenuButtons[button_id].pushed == false)
		MainMenuButtons[button_id].pushed = true;
	else
		MainMenuButtons[button_id].pushed = false;

	return 0;
}

int MainMenu_ButtonEvent(int mx, int my, MouseEvent event)
{
	std::vector<int> vec(2);
	std::vector< std::vector<int> > vtcs(4);

	vec[0] = mx;
	vec[1] = my;

	std::map< std::string, UIButton >::iterator i;
	for (i = MainMenuButtons.begin(); i != MainMenuButtons.end(); i++)
	{
		vtcs = i->second.actorVertices;

		if (VectorInVertices(vec, vtcs))
		{
			//std::cout << "button event! >> i->first << std::endl << std::endl;
			
			switch (event)
			{
				case MOUSE_CLICK_LEFT:
					MainMenu_ButtonEvent_MouseClickLeft( i->first );
					break;

				case MOUSE_MOTION:
					MainMenuButtons[i->first].hover = true;
					break;
			}

			break;
		}
		else 
		{
			switch (event)
			{
				case MOUSE_MOTION:
					MainMenuButtons[i->first].hover = false;
					break;
			}
		}
	}

	return 0;
}

int MainMenu_Draw()
{
	UIButton btn;
	
	std::map< std::string, UIButton >::iterator i;
	for (i = MainMenuButtons.begin(); i != MainMenuButtons.end(); i++)
	{
		btn = i->second;
		btn.Draw();
	}

	return 0;
}

int MainMenu_Init(int x, int y)
{	
	UIButton btn;
	std::vector<int> vec(2);
	
	btn.renderer = renderer;
	btn.w = 235;
	btn.h = 43;
	btn.pushed = false;
	btn.hover = false;

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

// ////////////////////////////////////////////////////////////////////////////////////////////////////

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