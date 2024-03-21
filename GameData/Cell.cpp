#include "Cell.h"

Cell::Cell() {
    event = std::make_shared<NewEventListenerInfo>();
    roomType = std::make_shared<std::string>("void");
    eventType = std::make_shared<std::string>("void");
}

Cell::Cell(const std::shared_ptr<NewEventListenerInfo> &newEvent, const std::string &newRoomType, const std::string &newEventType) {
    event = newEvent;
    roomType = std::make_shared<std::string>(newRoomType);
    eventType = std::make_shared<std::string>(newEventType);
}

Cell::Cell(const Cell &cell) {
    event = std::make_shared<NewEventListenerInfo>(*cell.event);
    roomType = std::make_shared<std::string>(*cell.roomType);
    eventType = std::make_shared<std::string>(*cell.eventType);
}

Cell& Cell::operator=(const Cell &cell) {
    if (cell.event != nullptr) event = std::make_shared<NewEventListenerInfo>(*cell.event);
    else event = nullptr;

    if (cell.roomType != nullptr) roomType = std::make_shared<std::string>(*cell.roomType);
    else roomType = nullptr;

    if (cell.eventType != nullptr) eventType = std::make_shared<std::string>(*cell.eventType);
    else eventType = nullptr;
    
    return *this;
}

void Cell::update(const Cell &delta) {
    if (delta.event != nullptr) {
        if (event == nullptr) event = std::make_shared<NewEventListenerInfo>();
        event = std::make_shared<NewEventListenerInfo>(*delta.event);
    }
    if (delta.roomType != nullptr) {
        if (roomType == nullptr) roomType = std::make_shared<std::string>();
        roomType = std::make_shared<std::string>(*delta.roomType);
    }
    if (delta.eventType != nullptr) {
        if (eventType == nullptr) eventType = std::make_shared<std::string>();
        eventType = std::make_shared<std::string>(*delta.eventType);
    }
}

void Cell::set_event(const std::shared_ptr<NewEventListenerInfo> &newEventType) {
    event = newEventType;
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

void Cell::set_event_type(const std::string& newEventType) {
    eventType = std::make_shared<std::string>(newEventType);
}

std::string Cell::get_event_type() const {
    return *eventType;
}

std::shared_ptr<std::string> Cell::get_event_type_ptr() const {
    return eventType;
}