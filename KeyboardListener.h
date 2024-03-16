#ifndef DISPLAY_KEYBOARDLISTENER_H
#define DISPLAY_KEYBOARDLISTENER_H
#include "Display.h"
#include <ncurses.h>
#include <iostream>
#include <string>

namespace Keyboard {
    //Returns -1 if no key was pressed
    int getKeyPressed(const Display &x);
    std::string getKeyName(int key);
};


#endif //DISPLAY_KEYBOARDLISTENER_H
