#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <SDL.h>

class Polygon
{

private:

public:
	int x, y, w, h;
	SDL_Renderer *renderer;
	SDL_Color bColorFill;
	std::vector< std::vector<int> > vtcs;

	int SetWH( int w, int h );

	Polygon();
	~Polygon();

	int Draw();

protected:
	
};

#endif