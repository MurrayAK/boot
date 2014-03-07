#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError( std::ostream &os, 
				  const std::string &msg );

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture( const std::string &file, 
						  SDL_Renderer *renderer );

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param dst The destination rectangle to render the texture too
* @param clip The sub-section of the texture to draw (clipping rect)
*                default of nullptr draws the entire texture
*/
void renderTexture( SDL_Texture *tex, 
				    SDL_Renderer *renderer, 
				    SDL_Rect dst,
 				    SDL_Rect *clip );

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
void renderTexture( SDL_Texture *tex, 
				    SDL_Renderer *renderer, 
				    int x, int y,
				    SDL_Rect *clip );

/**
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param fontSize The size we want the font to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*/
SDL_Texture* renderText( const std::string &message, 
						 const std::string &fontFile,
						 SDL_Color color, int fontSize, 
						 SDL_Renderer *renderer );
#endif