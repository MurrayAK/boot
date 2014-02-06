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

SettingsMap Settings("config\\settings.ini");

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

int engineShutdown(SDL_Window *window, SDL_Renderer *renderer) 
{
	// Cleanup
	
	// TODO: wipe hash tables

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Engine shutdown
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

int processEvents(SDL_Event events, bool *pQuit) 
{
	if (events.type == SDL_QUIT) *pQuit = true;

	// Keyboard events
	if (events.type == SDL_KEYDOWN) 
	{
		switch (events.key.keysym.sym) {
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
		switch (events.button.button) {
			case SDL_BUTTON_LEFT:
				break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
		}
	}

	return 0;
}

int renderGameState(SDL_Renderer *renderer) 
{
	//UIButton btn(renderer, 220, 35, 100, 100);
	//btn.Draw();

	return 0;
}

int gameLoop(SDL_Renderer *renderer) 
{
	SDL_Event events;

	bool quit = false;

	while (!quit)
	{
		// Event handling
		while (SDL_PollEvent(&events)) 
			processEvents(events, &quit);

		// Rendering
		SDL_RenderClear(renderer); // Clear screen
		renderGameState(renderer); // Render the game state
		SDL_RenderPresent(renderer); // Update the screen
	}

	return 0;
}

int main(int argc, char **argv) 
{
	engineInit();
	
	Settings.SetValue("APP_NAME", "Project \"BOOT\"");
	Settings.SetValue("APP_VERSION", "0.0.0 dev");
	
	std::string str = Settings.GetValue("APP_NAME");
	char *cstr = new char [str.length()+1];
	std::strcpy (cstr, str.c_str());
	const char *APP_NAME = cstr;

	int ResW = std::stoi(Settings.GetValue("ResW", "Engine"));
	int ResH = std::stoi(Settings.GetValue("ResH", "Engine"));

	// Save Ini test
	//Settings.SaveIni();

	SDL_Window *window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ResW, ResH, SDL_WINDOW_SHOWN);
	if (window == nullptr) { logSDLError(std::cout, "CreateWindow"); return 2; }

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) { logSDLError(std::cout, "CreateRenderer"); return 3; }

	gameLoop(renderer);

	engineShutdown(window, renderer);
		
	return 0;
}