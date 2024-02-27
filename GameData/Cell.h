#pragma once

#include <string>
#include <vector>

class Cell {
public:
    Cell();
    Cell(const std::string& event_type, const std::string& room_type);
    Cell& operator=(const Cell &cell);

    const std::string& get_event_type() const;
    const std::string& get_room_type() const;

    void set_event_type(const std::string& new_event_type);
private:
    std::string event_type; // "void" or any other type
    std::string room_type; // "room center", "room border", "hallway", "void"
};