#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "polygon.h"

#include <vector>

class UIButton: public Polygon
{

private:

public:
	std::vector< std::vector<int> > actorVtcs;

	struct State {
		bool Pushed;
		bool Hover;
	} State;

	struct Colors {
		SDL_Color Normal;
		SDL_Color Pushed;
		SDL_Color Hover;
	} Colors;

	UIButton();
	~UIButton();
	
	int Draw();
	int Draw_Pushed();
	int Draw_Hover();

protected:
	
};

#endif