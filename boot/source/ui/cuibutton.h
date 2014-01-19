#ifndef CUIBUTTON_H
#define CUIBUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>

class CUIButton
{

private:
	SDL_Renderer *bRenderer;
	int bX, bY, bW, bH;

public:
	SDL_Color bColorFill;

	CUIButton( SDL_Renderer *renderer, int x, int y, int w, int h );
	~CUIButton();

	int Draw();

protected:
	
};

#endif