#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <iostream>
#include <string>
#include <map>

#include "render.h"
#include "ui_button.h"

enum MouseEvent { MOUSE_CLICK_LEFT, MOUSE_MOTION };

int MainMenu_ButtonEvent(int mx, int my, MouseEvent event);
int MainMenu_Draw();
int MainMenu_Init(int x, int y);

#endif