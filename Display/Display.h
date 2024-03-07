#ifndef DISPLAY_DISPLAY_H
#define DISPLAY_DISPLAY_H
#include "constants.h"
#include <string>
#include <utility>
#include <ncurses.h>
#include <vector>
#include <map>
#include "Cell.h"

//Must be created ONLY after Display is created
class ColorManager {
    inline static short ColorPairNum = 8; //colors 0-7 are reserved by ncurces
    inline static std::map<std::pair<short, short>, unsigned> colorPairs;
public:
    unsigned CreateColorPair(short foreground, short background);
    static short getColor(int R, int G, int B);
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

struct Bind{
    std::string hint;
    int key;
    bool BindOrUnbind; //True for bind, false for unbind
    explicit Bind(int key, bool BindOrUnbind, std::string hint = "") : hint(std::move(hint)), key(key), BindOrUnbind(BindOrUnbind) {}
};

class Display {
private:
    static WINDOW* bindsWindow, *graphixWindow, *eventWindow;
    static int initialised_cnt;
    static std::map<WINDOW*, std::pair<int, int>> pos;
    static std::vector<int> BindsKeyList;
    void mywprintw(WINDOW* win, const std::string &s, unsigned attr, bool endl) const;
public:
    static int lastBindLineIdx;
    Display();
    ~Display();
    void SendEvent(const WindowEvent &event) const;
    void SendBind(const Bind &bind) const;
    void DrawSprite(const std::vector<std::vector<unsigned>> &sprite, int x, int y) const;
    [[nodiscard]] WINDOW* getMainWindow() const;
    void ClearGraphixWindow() const;
    //void DrawField(const std::vector<std::vector<Cell>> &field) const;
};

#endif //DISPLAY_DISPLAY_H