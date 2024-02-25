#include "Display.h"
#include <ncurses.h>
#include <iostream>
#include <map>
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
            clrtoeol(); //Clear line before printing
        }
    }
    if(endl) {
        ++pos[win].first;
        pos[win].second = 1;
        if(pos[win].first == constants::LinesInEventWindow - 1) {
            pos[win].first = 1;
            clrtoeol(); //Clear line before printing
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
        init_pair(WindowEvent::EventType::INFO, COLOR_BLUE, COLOR_BLACK);
        init_pair(WindowEvent::EventType::ACTION, COLOR_RED, COLOR_BLACK);
        init_pair(WindowEvent::EventType::REPLY, COLOR_YELLOW, COLOR_BLACK);
        init_pair(BIND, COLOR_GREEN, COLOR_BLACK);
        // Get screen size in rows and columns
        int row, col;
        getmaxyx(stdscr, row, col);
        if(row <= constants::LinesInScreen || col <= constants::ColumnsInScreen) {
            //TODO resize screen
            std::cerr << "DISPLAY IS TOO SMALL\n";
            std::cout << "DISPLAY IS TOO SMALL\n";
            endwin();
            exit(0);
        }

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
        mywprintw(eventWindow, "[INFO]", COLOR_PAIR(WindowEvent::INFO), false);
        mywprintw(eventWindow, event.WindowEventString, 0, true);
    }
    else if(event.type == WindowEvent::ACTION) {
        mywprintw(eventWindow, "[ACTION]", COLOR_PAIR(WindowEvent::ACTION), false);
        mywprintw(eventWindow, event.WindowEventString, 0, true);
    }
    else if(event.type == WindowEvent::REPLY) {
        mywprintw(eventWindow, "[REPLY]", COLOR_PAIR(WindowEvent::REPLY), false);
        mywprintw(eventWindow, event.Author, COLOR_PAIR(WindowEvent::REPLY), false);
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

void Display::AddBinds(const std::vector<std::pair<std::string, std::string>> &binds) {
    for(auto &bind : binds) {
        mywprintw(bindsWindow, bind.first + ": ", COLOR_PAIR(BIND), false);
        mywprintw(bindsWindow, bind.second, 0, true);
    }
}
