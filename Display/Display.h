#pragma once

#include "constants.h"
#include <string>
#include <utility>
#include <ncurses.h>
#include <vector>
#include <map>

class ColorManager {
    inline static short ColorPairNum = 1;
public:
    short init_color(short foreground, short background);
};

struct WindowEvent{
    enum EventType{
        NONE, //Send without any color and [announcment] IDK when should you use, but you can debug with it)
        INFO, //Important info, Blue color
        ACTION, //Very important actions (e.x. in figth), Red color
        REPLY //For something that someone says, Orange color
    } type;
    std::string WindowEventString;
    std::string Author; //For REPLY only
    explicit WindowEvent(EventType type, std::string WindowEventString, std::string Author = "") :
    type(type), WindowEventString(std::move(WindowEventString)), Author(std::move(Author)) {}
};

class Display {
private:
    inline static WINDOW* bindsWindow, *graphixWindow, *eventWindow;
    inline static int initialised_cnt = 0;
    void mywprintw(WINDOW* win, const std::string &s, unsigned attr, bool endl);
public:
    Display();
    ~Display();
    void SendEvent(const WindowEvent &event);
    void DrawSprite(const std::vector<std::vector<unsigned>> &sprite, int x, int y);
    WINDOW* getMainWindow() const;
};
