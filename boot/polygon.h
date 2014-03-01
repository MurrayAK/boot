#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <SDL.h>

class Polygon
{

private:

public:
	typedef std::vector< std::vector<int> > DrawPoints;

	int x, y, w, h;
	DrawPoints vertices;
	SDL_Renderer *renderer;
	SDL_Color colorBorder, colorFill;
	
	Polygon();
	Polygon(DrawPoints vertices);
	~Polygon();

	int Draw();

protected:
	
};

#endif