#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <SDL_ttf.h>

#include "polygon.h"

class UIButton: public Polygon
{

private:

public:
	std::vector< std::vector<int> > actorVertices;
	bool pushed;
	bool hover;

	UIButton();
	~UIButton();

protected:
	
};

#endif