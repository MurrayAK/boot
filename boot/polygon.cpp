#include "polygon.h"

Polygon::Polygon() {}

Polygon::~Polygon() {}

int Polygon::SetWH( int w, int h )
{
	this->w = w;
	this->h = h;

	return 0;
}

int Polygon::Draw() 
{
	SDL_Rect button = { this->x, this->y, 
						this->w, this->h };
	
	Uint8 oldR, oldG, oldB, oldA;
	
	// Store current draw color
	SDL_GetRenderDrawColor(this->renderer, &oldR, &oldG, &oldB, &oldA);
	
	// Draw button
	bColorFill.r = 0;
	bColorFill.g = 255;
	bColorFill.b = 0;

	SDL_SetRenderDrawColor(this->renderer, bColorFill.r, bColorFill.g, bColorFill.b, bColorFill.a);

	std::vector<int> vtx(2);

	std::vector< std::vector<int> >::iterator i;
	for (i = this->vtcs.begin(); i != this->vtcs.end(); i++)
	{
		vtx = *i;

		SDL_RenderDrawLines(this->renderer, );
	}

	//SDL_RenderDrawRect(this->renderer, &button);
	//SDL_RenderFillRect(this->renderer, &button);

	// Reset draw color to previous one before button draw
	SDL_SetRenderDrawColor(this->renderer, oldR, oldG, oldB, oldA);

	return 0;
}

