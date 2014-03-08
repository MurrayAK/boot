#include "ui_button.h"

#include <SDL_ttf.h>

UIButton::UIButton() {}

UIButton::~UIButton() {}

int UIButton::Draw()
{
	SDL_Color &Line = Colors.Normal;

	_Draw( Line );

	return 0;
}

int UIButton::Draw_Pushed()
{
	SDL_Color &Line = Colors.Pushed;
	
	_Draw( Line );

	return 0;
}

int UIButton::Draw_Hover()
{
	SDL_Color &Line = Colors.Hover;

	_Draw( Line );

	return 0;
}