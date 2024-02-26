#pragma once

#include <string>
#include <utility>

class GameData;
class Field;
class Cell;

class Drawer {
public:
    //basic drawing functions

    void initialize(const GameData& data) {}
    void change_current(const Field& field, const std::pair<int, int>& old_current, const std::pair<int, int>& new_current) {}
    void change_cell_event(const Cell& cell, const std::string& old_event, const std::string& new_event) {}
};