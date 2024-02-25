#include <iostream>
#include "Display.h"
#include "constants.h"
#include <ncurses.h>
#include <string>



int main() {
    Display display;
    WindowEvent event(WindowEvent::INFO, "TEST INFOOOOOOOOOOOOOOOOO ");
    display.SendEvent(event);
    WindowEvent event2(WindowEvent::ACTION, "Test ACTION event longlonglonglongnlgonglnogol");
    display.SendEvent(event2);
    //getch();
    WindowEvent event3(WindowEvent::REPLY, "Test REPLY event", "b4cksl4sh:");
    display.SendEvent(event3);
    display.SendEvent(event3);
//    display.SendEvent(event3);
//    display.SendEvent(event3);
//    display.SendEvent(event3);

    getch();
    return 0;
}
