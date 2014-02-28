#ifndef UI_ACTOR_CLICK_H
#define UI_ACTOR_CLICK_H

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
	std::vector< std::vector<int> > actorVertices;
	bool pushed;
	bool hover;

	UIButton();
	~UIButton();

	int Draw();

protected:
	
};

#endif