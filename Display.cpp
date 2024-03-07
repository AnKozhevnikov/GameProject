#include "Display.h"
#include <ncurses.h>
#include <iostream>
#include <map>
#include "Keyboard.h"

int Display::initialised_cnt = 0;
std::vector<int> Display::BindsKeyList(constants::LinesInBindsWindow);
int Display::lastBindLineIdx = 0;
std::map<WINDOW*, std::pair<int, int>> Display::pos;
WINDOW *Display::bindsWindow, *Display::graphixWindow, *Display::eventWindow;

namespace ColorPairs{
    unsigned NONE, //Send without any color
    INFO_COLOR, //Blue on black
    ACTION_COLOR, //Red on black
    REPLY_COLOR, //Orange on black
    BIND_COLOR; //Green on black
};

//Do not pass strings with '\n';
//Attr = 0 is default
void Display::mywprintw(WINDOW* win, const std::string &s, unsigned attr = 0, bool endl = true) const{
    if(pos[win].first == 0) {
        pos[win].first = 1;
    }
    if(pos[win].second == 0) {
        pos[win].second = 1;
    }
    wclrtoeol(win); //Clear line before printing
    for(auto el : s) {
        //Note that in ncurses first coord is Y
        mvwaddch(win, pos[win].first, pos[win].second, el | attr);
        ++pos[win].second;
        if(pos[win].second == constants::ColumnsInEventWindow - 1) {
            pos[win].second = 1;
            ++pos[win].first;
        }
        if(pos[win].first == constants::LinesInEventWindow - 1) {
            pos[win].first = 1;
        }
    }
    if(endl) {
        ++pos[win].first;
        pos[win].second = 1;
        if(pos[win].first == constants::LinesInEventWindow - 1) {
            pos[win].first = 1;
        }
    }
}

Display::Display() {
    if(Display::initialised_cnt == 0) {
        WINDOW* mainwindow = initscr();
        if ( mainwindow == nullptr ) {
            fputs("Could not initialize screen.", stderr);
            throw std::runtime_error("Could Not Initialise Screen");
        }
        if(!can_change_color()) {
            fputs("Colors are not available on screen", stderr);
            throw std::runtime_error("Colors are not available on screen");
        }
        start_color();
        use_default_colors();
        //Initialise color pairs
        ColorManager x;
        ColorPairs::INFO_COLOR = x.CreateColorPair(COLOR_BLUE, -1); //-1 is default color
        ColorPairs::ACTION_COLOR = x.CreateColorPair(COLOR_RED, -1);
        ColorPairs::REPLY_COLOR = x.CreateColorPair(COLOR_YELLOW, -1);
        ColorPairs::BIND_COLOR = x.CreateColorPair(COLOR_GREEN, -1);
        // Get screen size in rows and columns
        int row, col;
        getmaxyx(stdscr, row, col);
        if(row <= constants::LinesInScreen || col <= constants::ColumnsInScreen) {
            std::cerr << "DISPLAY IS TOO SMALL\n";
            std::cout << "DISPLAY IS TOO SMALL\n";
            std::cout << row << " " << col << std::endl;
            endwin();
            exit(0);
        }
        noecho(); //Blocking writing caracters to screen
        keypad(stdscr, true); //Allowing to use arrows
        nodelay(stdscr, TRUE); //Non-blocking getch
        eventWindow = subwin(stdscr, constants::LinesInEventWindow, constants::ColumnsInEventWindow, constants::LinesInBindsWindow, constants::ColumnsInGraphixWindow);
        graphixWindow = subwin(stdscr, constants::LinesInGraphixWindow, constants::ColumnsInGraphixWindow, 0, 0);
        bindsWindow = subwin(stdscr, constants::LinesInBindsWindow, constants::ColumnsInBindsWindow, 0, constants::ColumnsInGraphixWindow);
        scrollok(eventWindow, true);
        if(eventWindow == nullptr || graphixWindow == nullptr || bindsWindow == nullptr) {
            throw std::runtime_error("Could't initialise some subwindows, idk");
        }
        box(eventWindow, 0, 0);
        box(graphixWindow, 0, 0);
        box(bindsWindow, 0, 0);
    }
    ++Display::initialised_cnt;
}

void Display::SendEvent(const WindowEvent &event) const{
    if(event.type == WindowEvent::INFO) {
        mywprintw(eventWindow, "[INFO]", ColorPairs::INFO_COLOR, false);
        mywprintw(eventWindow, event.WindowEventString, 0, true);
    }
    else if(event.type == WindowEvent::ACTION) {
        mywprintw(eventWindow, "[ACTION]", ColorPairs::ACTION_COLOR, false);
        mywprintw(eventWindow, event.WindowEventString, 0, true);
    }
    else if(event.type == WindowEvent::REPLY) {
        mywprintw(eventWindow, "[REPLY]", ColorPairs::REPLY_COLOR, false);
        mywprintw(eventWindow, event.Author, ColorPairs::REPLY_COLOR, false);
        mywprintw(eventWindow, event.WindowEventString, 0, true);
    }
    wrefresh(eventWindow);
}

Display::~Display() {
    --initialised_cnt;
    if(initialised_cnt == 0) {
        delwin(eventWindow);
        delwin(graphixWindow);
        delwin(bindsWindow);
        endwin();
    }
}

WINDOW* Display::getMainWindow() const{
    return stdscr;
}

void Display::DrawSprite(const std::vector<std::vector<unsigned>> &sprite, int x, int y) const {
    for(int i = 0; i < sprite.size(); ++i) {
        for(int j = 0; j < sprite[i].size(); ++j) {
            if(i >= constants::LinesInGraphixWindow || j >= constants::ColumnsInGraphixWindow) {
                wprintw(graphixWindow, "Sprite doesn't fit in window");
                throw std::runtime_error("Sprite doesn't fit in window");
            }
            if(sprite[i][j] != 0)
                mvwaddch(graphixWindow, i + y, j + x, sprite[i][j]);
        }
    }
    wrefresh(graphixWindow);
}

void Display::ClearGraphixWindow() const {
    werase(graphixWindow);
    box(graphixWindow, 0, 0);
    wrefresh(graphixWindow);
}

void Display::SendBind(const Bind &bind) const {
    if(bind.BindOrUnbind) { //Needs to bind
        for(auto &key: BindsKeyList) {
            if(key == bind.key) {
                throw std::runtime_error("Can't bind on " +
                                            Keyboard::getKeyName(key) +
                                            " because this key is used for another bind. Your hint: "
                                            + bind.hint);
            }
        }
        lastBindLineIdx += 1;
        lastBindLineIdx %= constants::LinesInBindsWindow;
        move(lastBindLineIdx, 0);
        wclrtoeol(bindsWindow);
        BindsKeyList[lastBindLineIdx] = bind.key;

        mywprintw(bindsWindow, Keyboard::getKeyName(bind.key) + " : ", ColorPairs::BIND_COLOR, false);
        mywprintw(bindsWindow, bind.hint, 0, true);
        wrefresh(bindsWindow);
    }
    else { //Need to unbind
        for(int i = 0; i < constants::LinesInBindsWindow; ++i) {
            if(BindsKeyList[i] == bind.key) {
                BindsKeyList[i] = 0;
                move(i, 0);
                wclrtoeol(bindsWindow);
                wrefresh(bindsWindow);
                return;
            }
        }
        //If we are here we didn't find anything
        throw std::runtime_error("Can't unbind something that wasn't binded. Key : " + std::to_string(bind.key));
    }
}


unsigned ColorManager::CreateColorPair(short foreground, short background) {
    if(colorPairs.count({foreground, background})) {
        return colorPairs[{foreground, background}];
    }
    init_pair(ColorPairNum, foreground, background);
    colorPairs[{foreground, background}] = COLOR_PAIR(ColorPairNum);
    return COLOR_PAIR(ColorPairNum++);
}

#include "xtermColors.h"
//https://algolist.ru/graphics/find_col.php
short ColorManager::getColor(int R, int G, int B) {
    short ans_color = 0;
    int diff = INT32_MAX;
    for(short i = 0; i < 256; ++i) {
        int cur = (R - xtermColors[i].R) * (R - xtermColors[i].R) * 30 +
                  (G - xtermColors[i].G) * (G - xtermColors[i].G) * 59 +
                  (B - xtermColors[i].B) * (B - xtermColors[i].B) * 11;
        if(cur < diff) {
            diff = cur;
            ans_color = i;
        }
    }
    return ans_color;
}
