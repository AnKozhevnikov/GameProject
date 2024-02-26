#include <memory>
#include "Game.h"
#include "FieldEvent.h"
#include "FieldEventDrawer.h"

Game::Game() {
    data = GameData();
    status = RUNNING;
}

const GameData& Game::get_data() const {
    return data;
}

const Game::Status Game::get_status() const {
    return status;
}

std::string Game::on_event(const std::string& eventID, char button) {
    //TODO: implement
    if (eventID == "FieldEvent") {
        FieldEventDrawer drawer;
        FieldEvent fieldEvent(data, button);
        std::pair<int, int> newCurrent = *(std::static_pointer_cast<std::pair<int, int>>(fieldEvent.run_event()));
        drawer.change_current(data.get_field(), data.get_field().get_current(), newCurrent);
        const_cast<Field&>(data.get_field()).set_current(newCurrent);
    }
    return "";
}