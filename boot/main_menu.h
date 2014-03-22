#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "main.h"

/** ------------------------------------------------------------------------------------- */

/** Creates the Main Menu and associated Objects, such as Buttons */
void MainMenu_Init();

/** Draws the current state of the Main Menu */
void MainMenu_Draw();

/**
* Handles all Mouse Events that occur on a Button within the Main Menu
* @param mx The current X position of the Mouse cursor
* @param my The current Y position of the Mouse cursor
* @param event The current Mouse Event that occured, suchas Click, Move, etc.
*/
void MainMenu_ButtonEventHandler_Mouse( const int &mx, 
									    const int &my, 
									    const MouseEvent &event );


#endif