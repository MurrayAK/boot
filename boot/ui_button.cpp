#include "ui_button.h"

UIButton::UIButton() {}

UIButton::~UIButton() {}

int UIButton::Draw()
{
	SDL_Rect button = { this->x, this->y,
						this->w, this->h };

	SDL_Rect shadow = { this->x + 3, this->y + 3,
						this->w, this->h };

	Uint8 oldR, oldG, oldB, oldA;

	// Store current draw color
	SDL_GetRenderDrawColor(this->renderer, &oldR, &oldG, &oldB, &oldA);

	// Draw shadow
	bColorFill.r = 77;
	bColorFill.g = 77;
	bColorFill.b = 77;

	SDL_SetRenderDrawColor(this->renderer, bColorFill.r, bColorFill.g, bColorFill.b, bColorFill.a);

	SDL_RenderDrawRect(this->renderer, &shadow);
	SDL_RenderFillRect(this->renderer, &shadow);

	// Draw button
	if (this->hover == false)
	{
		if (this->pushed == false)
		{
			bColorFill.r = 84;
			bColorFill.g = 129;
			bColorFill.b = 245;
		}
		else
		{
			bColorFill.r = 66;
			bColorFill.g = 105;
			bColorFill.b = 193;
		}
	}
	else
	{
		bColorFill.r = 153;
		bColorFill.g = 153;
		bColorFill.b = 244;
	}

	SDL_SetRenderDrawColor(this->renderer, bColorFill.r, bColorFill.g, bColorFill.b, bColorFill.a);

	SDL_RenderDrawRect(this->renderer, &button);
	SDL_RenderFillRect(this->renderer, &button);

	// Reset draw color to previous one before button draw
	SDL_SetRenderDrawColor(this->renderer, oldR, oldG, oldB, oldA);

	return 0;
}


