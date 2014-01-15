// *****************************************************************************************
// ** box2d test demo
// ** main.cpp
// *****************************************************************************************

#include <string>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <Box2D/Box2D.h>

typedef std::vector<int> vectorint;
typedef std::vector< std::vector<int> > vectorvec;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

int main(int argc, char** argv)
{
    //Start up SDL and make sure it went ok
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    //Setup our window and renderer
    SDL_Window *window = SDL_CreateWindow("boot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) { logSDLError(std::cout, "CreateWindow"); return 2; }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) { logSDLError(std::cout, "CreateRenderer"); return 3; }
        
    SDL_Event e; //Our event structure
    bool quit = false; //For tracking if we want to quit

	//Game loop
    while (!quit)
    {
		//Event processing loop
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) quit = true;
        }

        //Rendering
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); //Set screen back to black
        SDL_RenderPresent(renderer); //Update the screen
    }

    //Destroy the various items
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	
    SDL_Quit();
        
    return 0;
}