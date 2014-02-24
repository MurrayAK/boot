#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>

class UIButton
{

private:
	SDL_Renderer *renderer;

public:
	int x, y, w, h;
	SDL_Color bColorFill;
	short state; //0 for standy, 1 for hover, 2 toggle

	UIButton( SDL_Renderer *renderer, int x, int y, int w, int h,short state );
	~UIButton();

	int Draw();

protected:
	
};

#endif