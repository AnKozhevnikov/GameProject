#include "FieldEventListener.h"
#include "Display.h"

FieldEventListener::FieldEventListener(const int newId, const int parent, const GameData *newData, Binder *binder) : EventListener(newId, parent, newData, binder){
    data.set_field(parentData->get_field());
    init();
    redraw();
}

void FieldEventListener::init() {
    bind('w', &FieldEventListener::move, this, "move up", 1);
    bind('a', &FieldEventListener::move, this, "move left", 2);
    bind('s', &FieldEventListener::move, this, "move right", 3);
    bind('d', &FieldEventListener::move, this, "move down", 4);
}

Message FieldEventListener::move(int direction) {
    std::pair<int, int> oldCurrent = data.get_field_ptr()->get_current();
    if (direction == 1) {
        data.get_field_ptr()->set_current(std::make_pair(oldCurrent.first, oldCurrent.second - 1));
    } else if (direction == 2) {
        data.get_field_ptr()->set_current(std::make_pair(oldCurrent.first - 1, oldCurrent.second));
    } else if (direction == 3) {
        data.get_field_ptr()->set_current(std::make_pair(oldCurrent.first, oldCurrent.second + 1));
    } else if (direction == 4) {
        data.get_field_ptr()->set_current(std::make_pair(oldCurrent.first + 1, oldCurrent.second));
    }
    Display display;
    display.SendEvent(WindowEvent(WindowEvent::INFO, "Moved to " + std::to_string(data.get_field_ptr()->get_current().first) + " " + std::to_string(data.get_field_ptr()->get_current().second)));
    return Message(data, NewEventListenerInfo(), false, id);
}

void FieldEventListener::redraw() {
    
}