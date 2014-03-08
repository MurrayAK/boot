#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <SDL.h>

class Polygon
{

private:

public:
	SDL_Renderer *renderer;
	int x, y, w, h;
	std::vector< std::vector<int> > vertices;

	struct Colors {
		SDL_Color Line;
		SDL_Color Fill;
	} Colors;

	Polygon();
	~Polygon();
	
	int Draw();

protected:
	int _Draw();
	int _Draw( SDL_Color Line );

};

#endif