#include "ui_button.h"

#include <SDL_ttf.h>

// TODO: COLORS FOR STATES

UIButton::UIButton() {}

UIButton::~UIButton() {}

int UIButton::Draw()
{
	SDL_Color Line;

	Line.r = 255;
	Line.g = 255;
	Line.b = 255;
	Line.a = 255;

	_Draw( Line );

	return 0;
}

int UIButton::Draw_Pushed()
{
	SDL_Color Line;

	Line.r = 0;
	Line.g = 255;
	Line.b = 0;
	Line.a = 255;

	_Draw( Line );

	return 0;
}

int UIButton::Draw_Hover()
{
	SDL_Color Line;

	Line.r = 0;
	Line.g = 0;
	Line.b = 255;
	Line.a = 255;

	_Draw( Line );

	return 0;
}