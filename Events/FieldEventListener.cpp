#include "FieldEventListener.h"
#include "Display.h"
#include "bitmap_image.hpp"
#include "Drawer.h"
#include "InventoryEventListenerInfo.h"

FieldEventListener::FieldEventListener(const int newId, const int parent, const GameData *newData, Binder *binder) : EventListener(newId, parent, newData, binder){
    data.set_is_game_over(parentData->get_is_game_over());
    data.set_field(parentData->get_field());
    data.set_heroes(parentData->get_heroes());
    data.set_inventory(parentData->get_inventory());
    Display display;
    display.SendEvent(WindowEvent(WindowEvent::INFO, "You are on the floor number " + std::to_string(data.get_field_ptr()->get_depth())));
    init();
    redraw();
}

void FieldEventListener::init() {
    bind('w', &FieldEventListener::move, this, "move up", 1);
    bind('a', &FieldEventListener::move, this, "move left", 2);
    bind('s', &FieldEventListener::move, this, "move right", 3);
    bind('d', &FieldEventListener::move, this, "move down", 4);
    bind('i', &FieldEventListener::openInventory, this, "open inventory");
    bind(27, &FieldEventListener::finish, this, "exit to main menu");
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
            //display.SendEvent(WindowEvent(WindowEvent::DEBUG, "Moved to " + std::to_string(data.get_field_ptr()->get_current().first) + " " + std::to_string(data.get_field_ptr()->get_current().second)));
            std::pair<int, int> newCurrent = data.get_field_ptr()->get_current();
            std::shared_ptr<NewEventListenerInfo> info = (*data.get_field_ptr()->get_cells_ptr())[newCurrent.first][newCurrent.second].get_event_ptr();
            std::vector<std::vector<Cell>> cells = data.get_field_ptr()->get_cells();
            cells[newCurrent.first][newCurrent.second].set_event(NewEventListenerInfo());
            cells[newCurrent.first][newCurrent.second].set_event_type("void");
            data.get_field_ptr()->set_cells(cells);
            redraw();
            return Message(GameData(), info, false, id);
    } else {
        display.SendEvent(WindowEvent(WindowEvent::ACTION, "Invalid move"));
        return Message();
    }
}

Message FieldEventListener::finish() {
    return Message(GameData(), std::make_shared<NewEventListenerInfo>(), true, id);
}

Message FieldEventListener::gameOverChecker() {
    if (data.get_is_game_over()) {
        Display display;
        display.SendEvent(WindowEvent(WindowEvent::INFO, "Game over"));
        return Message(data, std::make_shared<NewEventListenerInfo>(), true, id);
    }
    return Message(GameData(), std::make_shared<NewEventListenerInfo>(), false, id);
}

void FieldEventListener::redraw() {
    Display display;
    display.ClearGraphixWindow();

    std::shared_ptr<Field> field = data.get_field_ptr();
    std::pair<int, int> dimensions = field->get_dimensions();
    std::shared_ptr<std::vector<std::vector<Cell>>> cells = field->get_cells_ptr();
    for (int i=0; i<dimensions.first; ++i) {
        for (int j=0; j<dimensions.second; ++j) {
            if ((*cells)[i][j].get_room_type()=="roomborder" || (*cells)[i][j].get_room_type()=="void") {
                continue;
            }

            if ((*cells)[i][j].get_room_type()=="room") {
                if ((*cells)[i][j].get_event_type() == "void")
                    display.DrawSprite(Drawer::getSprite("EmptyRoom"), (i - 1)*2, j - 1);
                else if ((*cells)[i][j].get_event_type() == "battle")
                    display.DrawSprite(Drawer::getSprite("BattleRoom"), (i - 1)*2, j - 1);
                else if ((*cells)[i][j].get_event_type() == "boss battle")
                    display.DrawSprite(Drawer::getSprite("BossRoom"), (i - 1)*2, j - 1);
                else if ((*cells)[i][j].get_event_type() == "altar")
                    display.DrawSprite(Drawer::getSprite("AltarRoom"), (i - 1)*2, j - 1);
            }
            else if ((*cells)[i][j].get_room_type()=="corridor") {
                if ((*cells)[i][j].get_event_type() == "void")
                    display.DrawSprite(Drawer::getSprite("EmptyCorridor"), i*2, j);
                else if ((*cells)[i][j].get_event_type() == "battle")
                    display.DrawSprite(Drawer::getSprite("BattleCorridor"), i*2, j);
                else if ((*cells)[i][j].get_event_type() == "trap")
                    display.DrawSprite(Drawer::getSprite("TrapCorridor"), i*2, j);
                else if ((*cells)[i][j].get_event_type() == "npc")
                    display.DrawSprite(Drawer::getSprite("NpcCorridor"), i*2, j);
                else if ((*cells)[i][j].get_event_type() == "revive")
                    display.DrawSprite(Drawer::getSprite("ReviveCorridor"), i*2, j);
                else if ((*cells)[i][j].get_event_type() == "chest")
                    display.DrawSprite(Drawer::getSprite("ChestCorridor"), i*2, j);
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

Message FieldEventListener::openInventory() {
    return Message(data, std::make_shared<InventoryEventListenerInfo>(id, true), false, id);
}