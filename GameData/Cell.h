#pragma once

#include "NewEventListenerInfo.h"
#include <string>
#include <vector>
#include <memory>

class Cell {
public:
    Cell();
    Cell(const std::shared_ptr<NewEventListenerInfo> &event, const std::string &room_type, const std::string &event_type);
    Cell(const Cell &cell);
    Cell& operator=(const Cell &cell);

    void update(const Cell &delta);

    NewEventListenerInfo get_event() const;
    std::shared_ptr<NewEventListenerInfo> get_event_ptr() const;
    void set_event(const NewEventListenerInfo &new_event_type);

    std::string get_room_type() const;
    std::shared_ptr<std::string> get_room_type_ptr() const;
    void set_room_type(const std::string &new_room_type);

    std::string get_event_type() const;
    std::shared_ptr<std::string> get_event_type_ptr() const;
    void set_event_type(const std::string &new_event_type);
private:
    std::shared_ptr<NewEventListenerInfo> event; // "void" or any other type
    std::shared_ptr<std::string> roomType; // "room", "corridor", "void", "roomborder"
    std::shared_ptr<std::string> eventType; // "void" or any other type
};