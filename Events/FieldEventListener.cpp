#include "FieldEventListener.h"
#include "Display.h"
#include "bitmap_image.hpp"
#include "Drawer.h"

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
    bind('q', &FieldEventListener::quit, this, "quit");
}

Message FieldEventListener::move(int direction) {
    std::pair<int, int> delta;
    std::pair<int, int> oldCurrent = data.get_field_ptr()->get_current();
    if (direction == 1) {
        delta=std::make_pair(0, -1);
    } else if (direction == 2) {
        delta=std::make_pair(-1, 0);
    } else if (direction == 3) {
        delta=std::make_pair(0, 1);
    } else if (direction == 4) {
        delta=std::make_pair(1, 0);
    }
    if (0 <= oldCurrent.first+delta.first && oldCurrent.first+delta.first < data.get_field_ptr()->get_dimensions().first &&
        0 <= oldCurrent.second+delta.second && oldCurrent.second+delta.second < data.get_field_ptr()->get_dimensions().second &&
        (*data.get_field_ptr()->get_cells_ptr())[oldCurrent.first+delta.first][oldCurrent.second+delta.second].get_room_type()=="roomborder") {
        delta.first*=2;
        delta.second*=2;
    }
    Display display;
    if (0 <= oldCurrent.first+delta.first && oldCurrent.first+delta.first < data.get_field_ptr()->get_dimensions().first &&
        0 <= oldCurrent.second+delta.second && oldCurrent.second+delta.second < data.get_field_ptr()->get_dimensions().second &&
        (*data.get_field_ptr()->get_cells_ptr())[oldCurrent.first+delta.first][oldCurrent.second+delta.second].get_room_type()!="void") {
            data.get_field_ptr()->set_current(std::make_pair(oldCurrent.first+delta.first, oldCurrent.second+delta.second));
            display.SendEvent(WindowEvent(WindowEvent::INFO, "Moved to " + std::to_string(data.get_field_ptr()->get_current().first) + " " + std::to_string(data.get_field_ptr()->get_current().second)));
            redraw();
            std::pair<int, int> newCurrent = data.get_field_ptr()->get_current();
            NewEventListenerInfo info = (*data.get_field_ptr()->get_cells_ptr())[newCurrent.first][newCurrent.second].get_event();
            return Message(GameData(), info, false, id);
    } else {
        display.SendEvent(WindowEvent(WindowEvent::INFO, "Invalid move"));
        return Message(GameData(), NewEventListenerInfo(), false, id);
    }
}

Message FieldEventListener::quit() {
    return Message(GameData(), NewEventListenerInfo(), true, id);
}

void FieldEventListener::redraw() {
    Display display;

    std::shared_ptr<Field> field = data.get_field_ptr();
    std::pair<int, int> dimensions = field->get_dimensions();
    std::shared_ptr<std::vector<std::vector<Cell>>> cells = field->get_cells_ptr();
    for (int i=0; i<dimensions.first; ++i) {
        for (int j=0; j<dimensions.second; ++j) {
            if ((*cells)[i][j].get_room_type()=="corridor") {
                display.DrawSprite(Drawer::sprites["EmptyCorridor"], i*2, j);
            }
            else if ((*cells)[i][j].get_room_type()=="room") {
                display.DrawSprite(Drawer::sprites["EmptyRoom"], (i - 1)*2, j - 1);
            }
        }
    }

    std::pair<int, int> current = field->get_current();
    if ((*cells)[current.first][current.second].get_room_type()=="corridor") {
        display.DrawSprite(Drawer::sprites["CurrentCorridor"], current.first*2, current.second);
    }
    else if ((*cells)[current.first][current.second].get_room_type()=="room") {
        display.DrawSprite(Drawer::sprites["CurrentRoom"], (current.first - 1)*2, current.second - 1);
    }
}