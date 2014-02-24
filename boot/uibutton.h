#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

class UIButton
{

private:

public:
	int x, y, w, h;
	SDL_Renderer *renderer;
	SDL_Color bColorFill;
	short state;
	std::vector< std::vector<int> > actorVertices;

	UIButton();
	~UIButton();

	int Draw();

protected:
	
};

#endif