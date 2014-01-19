#include <headers/cuibutton.h>

CUIButton::CUIButton(SDL_Renderer *renderer, int w, int h, int x, int y) {

	bRenderer = renderer;
	bX = x;
	bY = y;
	bW = w;
	bH = h;
}

CUIButton::~CUIButton() {
	
}

int CUIButton::Draw() {

	SDL_Rect button = {bW, bH, bX, bY};
	
	SDL_SetRenderDrawColor(bRenderer, 255, 255, 255, 255);

	SDL_RenderDrawRect(bRenderer, &button);
	SDL_RenderFillRect(bRenderer, &button);

	SDL_SetRenderDrawColor(bRenderer, 0, 0, 0, 255);

	return 0;
}


