#include <ui/uibutton.h>

UIButton::UIButton( SDL_Renderer *renderer, int x, int y, int w, int h ) 
{
	bRenderer = renderer;
	bX = x;
	bY = y;
	bW = w;
	bH = h;
}

UIButton::~UIButton() {
	
}

int UIButton::Draw() 
{
	SDL_Rect button = {bW, bH, bX, bY};
	Uint8 oldR, oldG, oldB, oldA;

	SDL_GetRenderDrawColor(bRenderer, &oldR, &oldG, &oldB, &oldA);
	SDL_SetRenderDrawColor(bRenderer, bColorFill.r, bColorFill.g, bColorFill.b, bColorFill.a);

	SDL_RenderDrawRect(bRenderer, &button);
	SDL_RenderFillRect(bRenderer, &button);

	SDL_SetRenderDrawColor(bRenderer, oldR, oldG, oldB, oldA);

	return 0;
}


