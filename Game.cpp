#include <memory>
#include "Game.h"
#include "FieldEvent.h"
#include "EmptyEvent.h"

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

std::string Game::on_event(const std::string& eventID) {
    //TODO: implement
    if (eventID == "FieldEvent") {
        FieldEvent fieldEvent(data);
        std::pair<int, int> newCurrent = *(std::static_pointer_cast<std::pair<int, int>>(fieldEvent.run_event()));
        const_cast<Field&>(data.get_field()).set_current(newCurrent, drawer);
    } else if (eventID == "EmptyEvent") {
        EmptyEvent emptyEvent(data);
        emptyEvent.run_event();
    }
    return "EmptyEvent";
}