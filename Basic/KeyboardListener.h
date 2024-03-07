#pragma once

#include "Display.h"
#include <ncurses.h>

namespace KeyboardListener {
    //Returns -1 if no key was pressed
    int getKeyPressed(const Display &x);
}