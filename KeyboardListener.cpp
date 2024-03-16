#include "KeyboardListener.h"
#include <ncurses.h>
#include <map>
#include <string>
//Returns -1 if no key was pressed
int Keyboard::getKeyPressed(const Display &x) {
    return wgetch(x.getMainWindow());
}

std::map<int, std::string> keyNames = {{8, "Backspace"},
                                       {9, "Tab"},
                                       {10, "Enter"},
                                       {27, "ESC"},
                                       {32, "Space"},
                                       {33, "!"},
                                       {35, "#"},
                                       {36, "$"},
                                       {37, "%"},
                                       {38, "&"},
                                       {39, "'"},
                                       {40, "("},
                                       {41, ")"},
                                       {42, "*"},
                                       {43, "+"},
                                       {44, ","},
                                       {45, "-"},
                                       {46, "."},
                                       {47, "/"},
                                       {48, "0"},
                                       {49, "1"},
                                       {50, "2"},
                                       {51, "3"},
                                       {52, "4"},
                                       {53, "5"},
                                       {54, "6"},
                                       {55, "7"},
                                       {56, "8"},
                                       {57, "9"},
                                       {58, ":"},
                                       {59, ";"},
                                       {60, "<"},
                                       {61, "="},
                                       {62, ">"},
                                       {63, "?"},
                                       {64, "@"},
                                       {91, "["},
                                       {93, "]"},
                                       {94, "^"},
                                       {95, "_"},
                                       {96, "`"},
                                       {97, "a"},
                                       {98, "b"},
                                       {99, "c"},
                                       {100, "d"},
                                       {101, "e"},
                                       {102, "f"},
                                       {103, "g"},
                                       {104, "h"},
                                       {105, "i"},
                                       {106, "j"},
                                       {107, "k"},
                                       {108, "l"},
                                       {109, "m"},
                                       {110, "n"},
                                       {111, "o"},
                                       {112, "p"},
                                       {113, "q"},
                                       {114, "r"},
                                       {115, "s"},
                                       {116, "t"},
                                       {117, "u"},
                                       {118, "v"},
                                       {119, "w"},
                                       {120, "x"},
                                       {121, "y"},
                                       {122, "z"},
                                       {123, "{"},
                                       {124, "|"},
                                       {126, "~"},
                                       {127, "DEL"},
                                       {258, "Arrow-down"},
                                       {259, "Arrow-up"},
                                       {260, "Arrow-left"},
                                       {261, "Arrow-right"}};


std::string Keyboard::getKeyName(int key) {
    if(keyNames.count(key) == 0) {
        throw std::runtime_error("No such key " + std::to_string(key));
    }
    return keyNames[key];
}


