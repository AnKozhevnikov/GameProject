#ifndef DISPLAY_KEYBOARD_H
#define DISPLAY_KEYBOARD_H
#include "Display.h"
#include <ncurses.h>
#include <iostream>

namespace Keyboard {
    //Returns -1 if no key was pressed
    int getKeyPressed(Display &x);
};


#endif //DISPLAY_KEYBOARD_H
