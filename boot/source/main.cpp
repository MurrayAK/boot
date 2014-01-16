// *****************************************************************************************
// ** main.cpp
// *****************************************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <headers/log.h>
#include <headers/render.h>

typedef std::vector<int> vectorint;
typedef std::vector< std::vector<int> > vectorvec;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_FPS = 60;
const int SCREEN_BPP = 32;

int engineInit() 
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

int main(int argc, char** argv)
{
    engineInit();

    //Setup our window and renderer
    SDL_Window *window = SDL_CreateWindow("boot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) { logSDLError(std::cout, "CreateWindow"); return 2; }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) { logSDLError(std::cout, "CreateRenderer"); return 3; }
        
    SDL_Event e; //Our event structure
    bool quit = false; //For tracking if we want to quit
    vectorvec drawPoints; //Draw matrix
    vectorint newvec(2); //for a new vector
    vectorint mouseVec(2); //Current x,y of mouse pointer
	
    while (!quit)
    {
		//Read any events that occured
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) quit = true;

            //Keyboard events
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }

            //Mouse button events
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                switch (e.button.button) {
                    case SDL_BUTTON_LEFT:
                        newvec[0] = e.button.x;
                        newvec[1] = e.button.y;
                        drawPoints.push_back(newvec);
                        break;
                    case SDL_BUTTON_RIGHT:
                        drawPoints.clear();
                        break;
                    default:
                            break;
                }
            }

            //Mouse motion events
            if (e.type == SDL_MOUSEMOTION) {
                mouseVec[0] = e.motion.x;
                mouseVec[1] = e.motion.y;
            }
        }

        //Rendering
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                
        //Draw Points
        std::vector< std::vector<int> >::iterator r;
        std::vector<int>::iterator c;
        std::vector<int> vector(2);
        for (r = drawPoints.begin(); r != drawPoints.end(); r++) 
		{
            vector.clear();

            for (c = r->begin(); c != r->end(); c++) vector.push_back(*c);
            
			SDL_RenderDrawPoint(renderer, vector[0], vector[1]);
        }

        //Draw mouse target visualizer
        SDL_SetRenderDrawColor(renderer, 108, 158, 249, 255);
        SDL_RenderDrawLine(renderer, mouseVec[0], 0, mouseVec[0], SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, mouseVec[1], SCREEN_WIDTH, mouseVec[1]);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); //Set screen back to black
        SDL_RenderPresent(renderer); //Update the screen
    }

    //Destroy the various items
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
        
    return 0;
}