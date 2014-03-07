#ifndef MAIN_H
#define MAIN_H

#include "setmap.h"
#include "render.h"
#include "main_menu.h"

SettingsMap Settings;

int main( int argc, 
		  char** argv );

int gameLoop();

int renderGameState();

int processEvents( SDL_Event *eventsptr, 
				   bool *quitptr );
int engineInit();
int engineShutdown();

#endif