#pragma once

#include <string>
#include <utility>

class Field;
class Cell;

class Drawer {
public:
    //basic drawing functiosns

    virtual void change_current(const Field& field, const std::pair<int, int>& old_current, const std::pair<int, int>& new_current) {}
    virtual void change_cell_event(const Cell& cell, const std::string& old_event, const std::string& new_event) {}
};