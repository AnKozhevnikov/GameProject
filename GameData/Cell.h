#pragma once

#include <string>
#include <vector>
#include "Drawer.h"

class Cell {
public:
    Cell();
    Cell& operator=(const Cell &cell);

    const std::string& get_event_type() const;
    const std::string& get_room_type() const;

    void set_event_type(const std::string& new_event_type, Drawer& drawer);
private:
    std::string event_type; // "void" or any other type
    std::string room_type; // "room center", "room border", "hallway", "void"
};