#include "uibutton.h"

UIButton::UIButton() {}
UIButton::~UIButton() {}

int UIButton::Draw() 
{
	SDL_Rect button = {this->x, this->y, this->w, this->h};
	Uint8 oldR, oldG, oldB, oldA;
	
	if (this->state==0){
		SDL_GetRenderDrawColor(this->renderer, &oldR, &oldG, &oldB, &oldA);
		SDL_SetRenderDrawColor(this->renderer, bColorFill.r, bColorFill.g, bColorFill.b, bColorFill.a);
	}
	if (this->state!=0){
		oldR=223;
		oldG=45;
		oldB=98;
		oldA=3;
		bColorFill.r=oldR;
		bColorFill.g=oldG;
		bColorFill.b=oldB;
		bColorFill.a=oldA;
		SDL_GetRenderDrawColor(this->renderer, &oldR, &oldG, &oldB, &oldA);
		SDL_SetRenderDrawColor(this->renderer, bColorFill.r, bColorFill.g, bColorFill.b, bColorFill.a);
	}
	SDL_RenderDrawRect(this->renderer, &button);
	SDL_RenderFillRect(this->renderer, &button);

	SDL_SetRenderDrawColor(this->renderer, oldR, oldG, oldB, oldA);

	return 0;
}


