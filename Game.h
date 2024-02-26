#pragma once

#include "GameData.h"

class Game {
public:
    enum Status {
        RUNNING,
        FAILURE
    } status;

    Game();

    const GameData& get_data() const;
    const Status get_status() const;
    std::string on_event(const std::string& eventID);
private:
    GameData data;
    Drawer drawer;
};