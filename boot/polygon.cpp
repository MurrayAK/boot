#include "polygon.h"

Polygon::Polygon() {}

Polygon::Polygon(DrawPoints vertices)
{
	this->vertices = vertices;
}

Polygon::~Polygon() {}

int Polygon::Draw() 
{	
	Uint8 oldR, oldG, oldB, oldA;
	
	// Store current draw color
	SDL_GetRenderDrawColor(this->renderer, &oldR, &oldG, &oldB, &oldA);
	
	// Draw polygon
	SDL_SetRenderDrawColor(this->renderer, colorBorder.r, colorBorder.g, colorBorder.b, colorBorder.a);
	
	std::vector<int> svtx(2), dvtx(2);

	dvtx = this->vertices.back();
	dvtx[0] = std::abs( dvtx[0] );
	dvtx[1] = std::abs( dvtx[1] );

	DrawPoints::iterator i;
	for (i = this->vertices.begin(); i != this->vertices.end(); i++)
	{
		svtx = *i;
		
		svtx[0] = std::abs( svtx[0] );
		svtx[1] = std::abs( svtx[1] );

		SDL_RenderDrawLine(this->renderer, svtx[0], svtx[1], dvtx[0], dvtx[1]);

		dvtx[0] = svtx[0];
		dvtx[1] = svtx[1];
	}

	// Reset draw color to previous one before button draw
	SDL_SetRenderDrawColor(this->renderer, oldR, oldG, oldB, oldA);

	return 0;
}

