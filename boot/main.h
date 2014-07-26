#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;

enum MouseEvent {
	MOUSE_CLICK_LEFT,
	MOUSE_CLICK_MIDDLE,
	MOUSE_CLICK_RIGHT,
	MOUSE_MOTION
};

#endif