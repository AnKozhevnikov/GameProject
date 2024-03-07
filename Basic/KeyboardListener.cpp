#include "KeyboardListener.h"
#include <ncurses.h>

//Returns -1 if no key was pressed
int KeyboardListener::getKeyPressed(const Display &x) {
    return wgetch(x.getMainWindow());
}
