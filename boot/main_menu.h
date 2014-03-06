#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>

#include "render.h"
#include "ui_button.h"

enum MouseEvent { MOUSE_CLICK_LEFT, MOUSE_MOTION };

int MainMenu_Init();
int MainMenu_Draw();

int MainMenu_ButtonEventHandler_Mouse( int mx, int my, 
									   MouseEvent event );

#endif