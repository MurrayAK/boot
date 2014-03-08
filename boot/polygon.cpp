#include "polygon.h"

Polygon::Polygon() 
{
	Colors.Line.r = 255;
	Colors.Line.g = 255; 
	Colors.Line.b = 255;
	Colors.Line.a = 255;
}

Polygon::~Polygon() {}

void Polygon::Draw() { _Draw(); }

int Polygon::_Draw()
{
	Uint8 oldR, oldG, oldB, oldA;

	// Store current draw color
	SDL_GetRenderDrawColor( this->renderer, 
		                    &oldR, &oldG, &oldB, &oldA );

	// Draw polygon
	SDL_SetRenderDrawColor( this->renderer, 
							Colors.Line.r, 
							Colors.Line.g, 
							Colors.Line.b, 
							Colors.Line.a );
	
	std::vector< std::vector<int> >::iterator i;
	std::vector<int> svtx(2), dvtx(2);

	dvtx = vertices.back();
	dvtx[0] = std::abs( dvtx[0] );
	dvtx[1] = std::abs( dvtx[1] );

	for (i = vertices.begin(); i != vertices.end(); i++)
	{
		svtx = *i;

		svtx[0] = std::abs( svtx[0] );
		svtx[1] = std::abs( svtx[1] );
		
		SDL_RenderDrawLine( renderer, 
						    svtx[0], svtx[1], 
							dvtx[0], dvtx[1] );

		dvtx[0] = svtx[0];
		dvtx[1] = svtx[1];
	}
	
	// Reset draw color to previous one before button draw
	SDL_SetRenderDrawColor( this->renderer, oldR, oldG, oldB, oldA );

	return 0;
}

int Polygon::_Draw( SDL_Color &Line )
{
	Colors.Line = Line;

	_Draw();

	return 0;
}
