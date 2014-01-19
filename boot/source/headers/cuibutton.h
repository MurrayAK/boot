#ifndef CUIBUTTON_H
#define CUIBUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>

class CUIButton
{

private:
	int bX;
	int bY;
	int bW;
	int bH;
	SDL_Renderer *bRenderer;

public:
	CUIButton(SDL_Renderer *renderer, int w, int h, int x, int y);
	~CUIButton();

	int Draw();

protected:
	
};

#endif