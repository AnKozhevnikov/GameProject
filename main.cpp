#include <iostream>
#include "Display.h"
#include "constants.h"
#include "Keyboard.h"
//#include <ncurses.h>
#include <curses.h>
#include <string>
#include <thread>
using std::vector;

int main() {
    Display display;
    Keyboard::getKeyPressed(display);
    WindowEvent event(WindowEvent::INFO, "ABA");
    display.SendEvent(event);
    WindowEvent event2(WindowEvent::INFO, std::to_string(5));
    display.SendEvent(event2);
    WindowEvent event3(WindowEvent::INFO, "CABA");
    display.SendEvent(event3);

    while(true) {
        int key = Keyboard::getKeyPressed(display);
        if(key == -1) continue;
        if(key == 27) { //esc
            break;
        }
        WindowEvent event5(WindowEvent::INFO, std::to_string(key));
        display.SendEvent(event5);
    }

    std::cin.get();
    return 0;
}