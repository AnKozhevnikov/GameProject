#include "Cell.h"

Cell::Cell() {
    event_type="";
    room_type="";
}

Cell::Cell(const std::string& event_type, const std::string& room_type) {
    this->event_type=event_type;
    this->room_type=room_type;
}

Cell& Cell::operator=(const Cell &cell) {
    event_type=cell.event_type;
    room_type=cell.room_type;
    return *this;
}

const std::string& Cell::get_event_type() const {
    return event_type;
}

const std::string& Cell::get_room_type() const {
    return room_type;
}

void Cell::set_event_type(const std::string& new_event_type) {
    event_type=new_event_type;
}