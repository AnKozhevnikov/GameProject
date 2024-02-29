#pragma once

#include <string>
#include <vector>
#include <memory>

class Cell {
public:
    Cell();
    Cell(const std::string &event_type, const std::string &room_type);
    Cell(const Cell &cell);
    Cell& operator=(const Cell &cell);

    void update(const Cell &delta);

    std::string get_event_type() const;
    std::weak_ptr<std::string> get_event_type_ptr() const;
    void set_event_type(const std::string &new_event_type);

    std::string get_room_type() const;
    std::weak_ptr<std::string> get_room_type_ptr() const;
    void set_room_type(const std::string &new_room_type);
private:
    std::shared_ptr<std::string> eventType; // "void" or any other type
    std::shared_ptr<std::string> roomType; // "room center", "room border", "hallway", "void"
};