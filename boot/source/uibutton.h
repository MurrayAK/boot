#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>

class UIButton
{

private:
	SDL_Renderer *bRenderer;
	int bX, bY, bW, bH;

public:
	SDL_Color bColorFill;

	UIButton( SDL_Renderer *renderer, int x, int y, int w, int h );
	~UIButton();

	int Draw();

protected:
	
};

#endif