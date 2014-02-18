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

	UIButton( SDL_Renderer *renderer, int x, int y, int w, int h );
	~UIButton();

	int Draw();

protected:
	
};

#endif