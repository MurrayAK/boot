// *****************************************************************************************
// ** main.cpp
// *****************************************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <headers/debug.h>
#include <headers/render.h>

typedef std::vector<int> vectorint;
typedef std::vector< std::vector<int> > vectorvec;

const char* APP_NAME = "codename \"boot\"";
const char* APP_VERS = "0.0.0 dev";
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_FPS = 60;
const int SCREEN_BPP = 32;

int drawMouseClickPoints(SDL_Renderer *renderer, vectorvec pointMatrix)
{
	Uint8 oldR, oldG, oldB, oldA;
	SDL_GetRenderDrawColor(renderer, &oldR, &oldG, &oldB, &oldA);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	std::vector< std::vector<int> >::iterator r;
	std::vector<int>::iterator c;
	std::vector<int> vector(2);

	for (r = pointMatrix.begin(); r != pointMatrix.end(); r++) 
	{
		vector.clear();

		for (c = r->begin(); c != r->end(); c++) vector.push_back(*c);
			
		SDL_RenderDrawPoint(renderer, vector[0], vector[1]);
	}

	SDL_SetRenderDrawColor(renderer, oldR, oldG, oldB, oldA);

	return 0;
}

int drawMouseAxisGuide(SDL_Renderer *renderer, int x, int y)
{
	Uint8 oldR, oldG, oldB, oldA;
	SDL_GetRenderDrawColor(renderer, &oldR, &oldG, &oldB, &oldA);

	SDL_SetRenderDrawColor(renderer, 108, 158, 249, 255);
	
	SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
	SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);

	SDL_SetRenderDrawColor(renderer, oldR, oldG, oldB, oldA);

	return 0;
}

int engineStart() 
{
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	//Start up SDL-IMAGE and make sure it went ok
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError(std::cout, "IMG_Init");
		return 1;
	}

	//Start up SDL-TTF and make sure it went ok
	if (TTF_Init() != 0) {
		logSDLError(std::cout, "TTF_Init");
		return 1;
	}

	return 0;
}

int engineStop(SDL_Window *window, SDL_Renderer *renderer)
{
	//Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Engine shutdown
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

int gameLoop(SDL_Renderer *renderer)
{
	bool quit = false;
	SDL_Event events;
	vectorvec pointMatrix; //Matrix for remember click point locations
	vectorint newvec(2); //New click point vector

	while (!quit)
	{
		while (SDL_PollEvent(&events))
		{
			if (events.type == SDL_QUIT) quit = true;

			//Keyboard events
			if (events.type == SDL_KEYDOWN) {
				switch (events.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = true;
						break;
					default:
						break;
				}
			}

			//Mouse button events
			if (events.type == SDL_MOUSEBUTTONDOWN) {
				switch (events.button.button) {
					case SDL_BUTTON_LEFT:
						newvec[0] = events.button.x;
						newvec[1] = events.button.y;
						pointMatrix.push_back(newvec);
						break;
					case SDL_BUTTON_RIGHT:
						pointMatrix.clear();
						break;
					default:
							break;
				}
			}
		}

		//Rendering
		SDL_RenderClear(renderer); //Clear screen
		 
		drawMouseClickPoints(renderer, pointMatrix);
		drawMouseAxisGuide(renderer, events.motion.x, events.motion.y);

		SDL_RenderPresent(renderer); //Update the screen
	}

	return 0;
}

int main(int argc, char** argv)
{
	engineStart();

	SDL_Window *window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) { logSDLError(std::cout, "CreateWindow"); return 2; }

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) { logSDLError(std::cout, "CreateRenderer"); return 3; }

	gameLoop(renderer);

	engineStop(window, renderer);
		
	return 0;
}