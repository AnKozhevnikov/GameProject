#include "Display.h"
#include <ncurses.h>
#include <iostream>
#include <map>

namespace ColorPairs{
    int NONE, //Send without any color
    INFO_COLOR, //Blue on black
    ACTION_COLOR, //Red on black
    REPLY_COLOR, //Orange on black
    BIND_COLOR; //Green on black
};

//Do not pass strings with '\n';
//Attr = 0 is default
void Display::mywprintw(WINDOW* win, const std::string &s, unsigned attr = 0, bool endl = true) {
    static std::map<WINDOW*, std::pair<int, int>> pos;
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
    if(!Display::initialised_cnt) {
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
        //Initialise color pairs
        ColorManager x;
        ColorPairs::INFO_COLOR = x.init_color(COLOR_BLUE, COLOR_BLACK);
        ColorPairs::ACTION_COLOR = x.init_color(COLOR_RED, COLOR_BLACK);
        ColorPairs::REPLY_COLOR = x.init_color(COLOR_YELLOW, COLOR_BLACK);
        ColorPairs::BIND_COLOR = x.init_color(COLOR_GREEN, COLOR_BLACK);
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
        eventWindow = subwin(stdscr, constants::LinesInEventWindow, constants::ColumnsInEventWindow, constants::LinesInGraphixWindow, 0);
        graphixWindow = subwin(stdscr, constants::LinesInGraphixWindow, constants::ColumnsInGraphixWindow, 0, 0);
        bindsWindow = subwin(stdscr, constants::LinesInBindsWindow, constants::ColumnsInBindsWindow, 0, constants::ColumnsInGraphixWindow);
        scrollok(eventWindow, true);
        if(eventWindow == nullptr || graphixWindow == nullptr || bindsWindow == nullptr) {
            throw std::runtime_error("Could't initialise some subwindows, idk");
        }
        box(eventWindow, 0, 0);
        box(graphixWindow, 0, 0);
        box(bindsWindow, 0, 0);
        ++Display::initialised_cnt;
    }
}

void Display::SendEvent(const WindowEvent &event) {
    if(event.type == WindowEvent::INFO) {
        mywprintw(eventWindow, "[INFO]", COLOR_PAIR(ColorPairs::INFO_COLOR), false);
        mywprintw(eventWindow, event.WindowEventString, 0, true);
    }
    else if(event.type == WindowEvent::ACTION) {
        mywprintw(eventWindow, "[ACTION]", COLOR_PAIR(ColorPairs::ACTION_COLOR), false);
        mywprintw(eventWindow, event.WindowEventString, 0, true);
    }
    else if(event.type == WindowEvent::REPLY) {
        mywprintw(eventWindow, "[REPLY]", COLOR_PAIR(ColorPairs::REPLY_COLOR), false);
        mywprintw(eventWindow, event.Author, COLOR_PAIR(ColorPairs::REPLY_COLOR), false);
        mywprintw(eventWindow, event.WindowEventString, 0, true);
    }
    wrefresh(eventWindow);
}

Display::~Display() {
    --initialised_cnt;
    if(!initialised_cnt) {
        delwin(eventWindow);
        delwin(graphixWindow);
        delwin(bindsWindow);
        endwin();
    }
}

WINDOW* Display::getMainWindow() const {
    return stdscr;
}

void Display::DrawSprite(const std::vector<std::vector<unsigned>> &sprite, int x, int y) {
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

short ColorManager::init_color(short foreground, short background) {
    init_pair(ColorPairNum, foreground, background);
    return ColorPairNum++;
}
