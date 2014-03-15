#ifndef RENDER_STARTUP_H
#define RENDER_STARTUP_H

#include "main.h"

/** Creates the Startup Screen */
void StartupScreen_Init();

/** Draws the current state of the Startup Screen */
void StartupScreen_Draw();

/**
* Handles all Mouse Events that occur on a Button within the Main Menu
* @param mx The current X position of the Mouse cursor
* @param my The current Y position of the Mouse cursor
* @param event The current Mouse Event that occured, suchas Click, Move, etc.
*/
void StartupScreen_ButtonEventHandler_Mouse( const int &mx, 
									         const int &my, 
									         const MouseEvent &event );

#endif