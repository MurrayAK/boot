#include "main_menu.h"

/** ------------------------------------------------------------------------------------- */

void StartupScreen_Init()
{
	MainMenu_Init();
}

void StartupScreen_Draw()
{
	MainMenu_Draw();
}

void StartupScreen_ButtonEventHandler_Mouse( const int &mx, 
									         const int &my, 
									         const MouseEvent &event )
{
	MainMenu_ButtonEventHandler_Mouse(mx, my, event);
}