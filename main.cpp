#include <iostream>
#include "Display.h"
#include "constants.h"
#include "Keyboard.h"
#include "bitmap_image.hpp"
//#include <ncurses.h>
#include <curses.h>
#include <string>
#include <thread>
#include <map>
using std::vector;



int main() {
    Display display;
    WindowEvent event(WindowEvent::INFO, "ABAB");
    display.SendEvent(event);
    Bind bind(97, true, "ABACABA");
    display.SendBind(bind);
    std::cin.get();
    ColorManager manager;
    bitmap_image image("bmp_24.bmp");
    vector<vector<unsigned>> sprite(50, vector<unsigned>(100));
    for (std::size_t y = 0; y < 50; ++y)
    {
        for (std::size_t x = 0; x < 100; ++x)
        {
            rgb_t colour;

            image.get_pixel(x, y, colour);

            unsigned clr = manager.CreateColorPair(-1, ColorManager::getColor(colour.red, colour.green, colour.blue));

            sprite[y][x] = ' ' | clr;

        }
    }
    display.DrawSprite(sprite, 0, 0);
    while(true) {
        int key = Keyboard::getKeyPressed(display);
        if(key == -1) continue;
        if(key == 32) {
            break;
        }
        if(key == 97) {
            Bind bind2(97, false);
            display.SendBind(bind2);
        }
        else{
            WindowEvent event2(WindowEvent::INFO, std::to_string(key));
            display.SendEvent(event2);
            Bind bind2(key, true);
            display.SendBind(bind2);
        }
    }
    std::cin.get();
    return 0;
}