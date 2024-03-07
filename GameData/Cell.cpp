#include "Cell.h"

Cell::Cell() {
    eventType = nullptr;
    roomType = nullptr;
}

Cell::Cell(const std::string &newEventType, const std::string &newRoomType) {
    eventType = std::make_shared<std::string>(newEventType);
    roomType = std::make_shared<std::string>(newRoomType);
}

Cell::Cell(const Cell &cell) {
    eventType = std::make_shared<std::string>(*cell.eventType);
    roomType = std::make_shared<std::string>(*cell.roomType);
}

Cell& Cell::operator=(const Cell &cell) {
    if (cell.eventType != nullptr) eventType = std::make_shared<std::string>(*cell.eventType);
    else eventType = nullptr;

    if (cell.roomType != nullptr) roomType = std::make_shared<std::string>(*cell.roomType);
    else roomType = nullptr;
    
    return *this;
}

void Cell::update(const Cell &delta) {
    if (delta.eventType != nullptr) {
        eventType = std::make_shared<std::string>(*delta.eventType);
    }
    if (delta.roomType != nullptr) {
        roomType = std::make_shared<std::string>(*delta.roomType);
    }
}

std::string Cell::get_event_type() const {
    return *eventType;
}

std::shared_ptr<std::string> Cell::get_event_type_ptr() const {
    return eventType;
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

void Cell::set_event_type(const std::string& newEventType) {
    eventType = std::make_shared<std::string>(newEventType);
}