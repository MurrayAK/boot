// *****************************************************************************************
// ** box2d test demo
// ** main.cpp
// *****************************************************************************************

#include <string>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

typedef std::vector<int> vectorint;
typedef std::vector< std::vector<int> > vectorvec;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_FPS = 60;
const int SCREEN_BPP = 32;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr) logSDLError(std::cout, "LoadTexture");
    return texture;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param dst The destination rectangle to render the texture too
* @param clip The sub-section of the texture to draw (clipping rect)
*                default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
    SDL_Rect *clip = nullptr)
{
    SDL_RenderCopy(ren, tex, clip, &dst);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height and taking a clip of the texture if desired
* If a clip is passed, the clip's width and height will be used instead of
*        the texture's
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param x The x coordinate to draw too
* @param y The y coordinate to draw too
* @param clip The sub-section of the texture to draw (clipping rect)
*                default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
    SDL_Rect *clip = nullptr)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

    renderTexture(tex, ren, dst, clip);
}

/**
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param fontSize The size we want the font to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*/
SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
    SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
    //Open the font
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr){
        logSDLError(std::cout, "TTF_OpenFont");
        return nullptr;
    }        
    //We need to first render to a surface as that's what TTF_RenderText
    //returns, then load that surface into a texture
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    if (surf == nullptr) {
        TTF_CloseFont(font);
        logSDLError(std::cout, "TTF_RenderText");
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == nullptr) {
        logSDLError(std::cout, "CreateTexture");
    }
    //Clean up the surface and font
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

int engineInit() {
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