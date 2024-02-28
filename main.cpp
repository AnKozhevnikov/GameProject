#include <iostream>
#include "Display.h"
#include "constants.h"
#include "Keyboard.h"
//#include <ncurses.h>
#include <curses.h>
#include <string>

using std::vector;

int main() {
    Display display;
    ColorManager manager;
    const short green = manager.init_color(COLOR_GREEN, COLOR_RED);
    const unsigned green_line = COLOR_PAIR(green) | A_BLINK | A_ALTCHARSET;
    vector<vector<unsigned>> line = {{178u | green_line, 178u | green_line, 'C' | green_line, 'D' | green_line, 'E' | green_line}};
    display.DrawSprite(line, 10, 10);
    WindowEvent event(WindowEvent::INFO, "Hello, World!");
    display.SendEvent(event);
    getch();
    return 0;
}
