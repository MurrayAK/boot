#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

#include <polygon.h>

class Rectangle : public Polygon
{

private:

public:
	SDL_Renderer *renderer;
	SDL_Color bColorFill;
	std::vector< std::vector<int> > actorVertices;
	bool pushed;
	bool hover;

	Rectangle();
	~Rectangle();

	int Draw();

protected:
	
};

#endif