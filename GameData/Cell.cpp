#include "Cell.h"

Cell::Cell() {
    event = nullptr;
    roomType = nullptr;
}

Cell::Cell(const NewEventListenerInfo &newEvent, const std::string &newRoomType) {
    event = std::make_shared<NewEventListenerInfo>(newEvent);
    roomType = std::make_shared<std::string>(newRoomType);
}

Cell::Cell(const Cell &cell) {
    event = std::make_shared<NewEventListenerInfo>(*cell.event);
    roomType = std::make_shared<std::string>(*cell.roomType);
}

Cell& Cell::operator=(const Cell &cell) {
    if (cell.event != nullptr) event = std::make_shared<NewEventListenerInfo>(*cell.event);
    else event = nullptr;

    if (cell.roomType != nullptr) roomType = std::make_shared<std::string>(*cell.roomType);
    else roomType = nullptr;
    
    return *this;
}

void Cell::update(const Cell &delta) {
    if (delta.event != nullptr) {
        event = std::make_shared<NewEventListenerInfo>(*delta.event);
    }
    if (delta.roomType != nullptr) {
        roomType = std::make_shared<std::string>(*delta.roomType);
    }
}

void Cell::set_event(const NewEventListenerInfo& newEventType) {
    event = std::make_shared<NewEventListenerInfo>(newEventType);
}

NewEventListenerInfo Cell::get_event() const {
    return *event;
}

std::shared_ptr<NewEventListenerInfo> Cell::get_event_ptr() const {
    return event;
}

void Cell::set_room_type(const std::string& newRoomType) {
    roomType = std::make_shared<std::string>(newRoomType);
}

std::string Cell::get_room_type() const {
    return *roomType;
}

std::shared_ptr<std::string> Cell::get_room_type_ptr() const {
    return roomType;
}