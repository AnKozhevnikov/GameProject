#include "FieldEventListener.h"
#include "Display.h"
#include "bitmap_image.hpp"
#include "Drawer.h"

FieldEventListener::FieldEventListener(const int newId, const int parent, const GameData *newData, Binder *binder) : EventListener(newId, parent, newData, binder){
    data.set_field(parentData->get_field());
    data.set_heroes(parentData->get_heroes());
    data.set_inventory(parentData->get_inventory());
    Display display;
    display.SendEvent(WindowEvent(WindowEvent::INFO, "You are on the floor number " + std::to_string(data.get_field_ptr()->get_depth())));
    init();
    redraw();
}

void FieldEventListener::init() {
    Display display;
    //display.SendEvent(WindowEvent(WindowEvent::INFO, std::to_string((unsigned long long)(void*)&FieldEventListener::finish)));
    //display.SendEvent(WindowEvent(WindowEvent::INFO, std::to_string((unsigned long long)(void*)&FieldEventListener::gameOverChecker)));
    bind('w', &FieldEventListener::move, this, "move up", 1);
    bind('a', &FieldEventListener::move, this, "move left", 2);
    bind('s', &FieldEventListener::move, this, "move right", 3);
    bind('d', &FieldEventListener::move, this, "move down", 4);
    bind('f', &FieldEventListener::finish, this, "finish");
    bind(-1, &FieldEventListener::gameOverChecker, this, "game over checker");
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
            display.SendEvent(WindowEvent(WindowEvent::DEBUG, "Moved to " + std::to_string(data.get_field_ptr()->get_current().first) + " " + std::to_string(data.get_field_ptr()->get_current().second)));
            redraw();
            std::pair<int, int> newCurrent = data.get_field_ptr()->get_current();
            NewEventListenerInfo info = (*data.get_field_ptr()->get_cells_ptr())[newCurrent.first][newCurrent.second].get_event();
            return Message(GameData(), info, false, id);
    } else {
        display.SendEvent(WindowEvent(WindowEvent::ACTION, "Invalid move"));
        return Message(GameData(), NewEventListenerInfo(), false, id);
    }
}

Message FieldEventListener::finish() {
    data.set_is_game_over(true);
    return Message(GameData(), NewEventListenerInfo(), false, id);
}

Message FieldEventListener::gameOverChecker() {
    if (data.get_is_game_over()) {
        return Message(data, NewEventListenerInfo(), true, id);
    }
    return Message(GameData(), NewEventListenerInfo(), false, id);
}

void FieldEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();

    std::shared_ptr<Field> field = data.get_field_ptr();
    std::pair<int, int> dimensions = field->get_dimensions();
    std::shared_ptr<std::vector<std::vector<Cell>>> cells = field->get_cells_ptr();
    for (int i=0; i<dimensions.first; ++i) {
        for (int j=0; j<dimensions.second; ++j) {
            if ((*cells)[i][j].get_room_type()=="corridor") {
                display.DrawSprite(Drawer::getSprite("EmptyCorridor"), i*2, j);
            }
            else if ((*cells)[i][j].get_room_type()=="room") {
                display.DrawSprite(Drawer::getSprite("EmptyRoom"), (i - 1)*2, j - 1);
            }
        }
    }

    std::pair<int, int> current = field->get_current();
    if ((*cells)[current.first][current.second].get_room_type()=="corridor") {
        display.DrawSprite(Drawer::getSprite("CurrentCorridor"), current.first*2, current.second);
    }
    else if ((*cells)[current.first][current.second].get_room_type()=="room") {
        display.DrawSprite(Drawer::getSprite("CurrentRoom"), (current.first - 1)*2, current.second - 1);
    }
}