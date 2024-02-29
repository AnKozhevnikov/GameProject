#pragma once

#include "GameData.h"
#include "EventListener.h"
#include "Binder.h"
#include "KeyboardListener.h"
#include "Message.h"

#include <vector>

class Game {
public:
    enum Status {
        RUNNING,
        FAILURE
    };

    Game();

    const GameData& get_data() const;
    const Status get_status() const;

    void run();
private:
    GameData data;
    Status status;

    Binder binder;
    KeyboardListener listener;
    std::map<int, EventListener> eventListeners;

    void kill(int id);
    void addEventListener(NewEventListenerInfo info);
};