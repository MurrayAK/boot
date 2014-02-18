#include "uibutton.h"

UIButton::UIButton( SDL_Renderer *renderer, int x, int y, int w, int h ) 
{
	this->renderer = renderer;
	this->x = x; this->y = y;
	this->w = w; this->h = h;
}

UIButton::~UIButton() {  }

int UIButton::Draw() 
{
	SDL_Rect button = {this->x, this->y, this->w, this->h};
	Uint8 oldR, oldG, oldB, oldA;
	
	SDL_GetRenderDrawColor(this->renderer, &oldR, &oldG, &oldB, &oldA);
	SDL_SetRenderDrawColor(this->renderer, bColorFill.r, bColorFill.g, bColorFill.b, bColorFill.a);

	SDL_RenderDrawRect(this->renderer, &button);
	SDL_RenderFillRect(this->renderer, &button);

	SDL_SetRenderDrawColor(this->renderer, oldR, oldG, oldB, oldA);

	return 0;
}


