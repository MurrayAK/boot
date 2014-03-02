#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <vector>
#include <SDL_ttf.h>

#include "polygon.h"

class UIButton: public Polygon
{

private:

public:
	std::vector< std::vector<int> > actorVertices;

	struct State {
		bool Pressed;
		bool Hover;
	} State;

	UIButton();
	~UIButton();
	
	int Draw_Pressed();
	int Draw_Hover();

protected:
	
};

#endif