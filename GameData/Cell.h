#pragma once

#include "NewEventListenerInfo.h"
#include <string>
#include <vector>
#include <memory>

class Cell {
public:
    Cell();
    Cell(const NewEventListenerInfo &event, const std::string &room_type);
    Cell(const Cell &cell);
    Cell& operator=(const Cell &cell);

    void update(const Cell &delta);

    NewEventListenerInfo get_event() const;
    std::shared_ptr<NewEventListenerInfo> get_event_ptr() const;
    void set_event(const NewEventListenerInfo &new_event_type);

    std::string get_room_type() const;
    std::shared_ptr<std::string> get_room_type_ptr() const;
    void set_room_type(const std::string &new_room_type);
private:
    std::shared_ptr<NewEventListenerInfo> event; // "void" or any other type
    std::shared_ptr<std::string> roomType; // "room", "hallway", "void"
};