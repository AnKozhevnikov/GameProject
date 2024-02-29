#include "Keyboard.h"
#include <ncurses.h>

//Returns -1 if no key was pressed
int Keyboard::getKeyPressed(Display &x) {
    return wgetch(x.getMainWindow());
}


