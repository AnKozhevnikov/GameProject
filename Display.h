#ifndef DISPLAY_DISPLAY_H
#define DISPLAY_DISPLAY_H
#include "constants.h"
#include <string>
#include <utility>
#include <ncurses.h>
#include <vector>
#include <map>


struct WindowEvent{
    enum EventType{
        NONE, //Send without any color and [announcment] IDK when should you use, but you can debug with it)
        INFO, //Important info, Blue color
        ACTION, //Very important actions (e.x. in figth), Red color
        REPLY, //For something that someone says, Orange color
        ALWAYS_LAST //Only for Service Purpose, keep it always last :)
    } type;
    std::string WindowEventString;
    std::string Author; //For REPLY only
    explicit WindowEvent(EventType type, std::string WindowEventString, std::string Author = "") :
    type(type), WindowEventString(std::move(WindowEventString)), Author(std::move(Author)) {}
};

constexpr int BIND = WindowEvent::EventType::ALWAYS_LAST + 1;

class Display {
private:
    WINDOW* bindsWindow, *graphixWindow, *eventWindow;
    inline static int initialised_cnt = 0;
    void mywprintw(WINDOW* win, const std::string &s, unsigned attr, bool endl);
public:
    Display();
    ~Display();
    void SendEvent(const WindowEvent &event);
    void AddBinds(const std::vector<std::pair<std::string, std::string>> &binds);
};

class BindsRegistrator {

};

#endif //DISPLAY_DISPLAY_H
