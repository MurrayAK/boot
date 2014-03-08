#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "polygon.h"

#include <vector>

class UIButton: public Polygon
{

private:

public:
	std::vector< std::vector<int> > actorVertices;

	struct State {
		bool Pushed;
		bool Hover;
	} State;

	UIButton();
	~UIButton();
	
	int Draw();
	int Draw_Pushed();
	int Draw_Hover();

protected:
	
};

#endif