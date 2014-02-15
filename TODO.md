===========================================================================================	
Project 'boot' UNNAMED GAME
  
ENGINE > SETTINGS SYSTEM

  A good, fast, robust settings system is paramount to a good working engine
===========================================================================================

    CLASS   SettingsMap [ SettingsMap.h, SettingsMap.cpp ]

   to do:   SAVEINI() We need to be able to save data to ini files, not just read them in.
                      functionality needs to be decided upon and coded in.

optimize:   Reading and setting values could possibly be faster, if implemented
            in an alternate way, what is faster Tokenizing or Regex?

  future:   Add XML support, load/save.



===========================================================================================	
  ENGINE > UI DRAWING SYSTEM

  Write a UI system that we can use to draw windows, buttons, checkboxes, sliders, etc
  and save/load them whenever we need them.
===========================================================================================

    CLASS   SettingsMap [ SettingsMap.h, SettingsMap.cpp ]

   to do:   SAVEINI() We need to be able to save data to ini files, not just read them in.
                      functionality needs to be decided upon and coded in.

optimize:   Reading and setting values could possibly be faster, if implemented
            in an alternate way, what is faster Tokenizing or Regex?

  future:   Add XML support, load/save.



SEPERATE PROJECTS FOR TOOLS PROGRAMMING
- UI DRAWING/CREATOR TOOL
- ENVIRONMENT DRAWING/PAINTING TOOL