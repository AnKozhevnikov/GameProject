#ifndef DISPLAY_KEYBOARD_H
#define DISPLAY_KEYBOARD_H
#include "Display.h"
#include <ncurses.h>
#include <iostream>
#include <string>

namespace KeyboardListener {
    //Returns -1 if no key was pressed
    int getKeyPressed(const Display &x);
    std::string getKeyName(int key);
};


#endif //DISPLAY_KEYBOARD_H