#pragma once

#include "GameData.h"
#include "EventListener.h"
#include "Message.h"
#include "Binder.h"
#include "KeyboardListener.h"
#include "Display.h"

#include <vector>

class Game {
public:
    enum Status {
        RUNNING,
        FAILURE
    };

    Game(const Display *display);

    const GameData& get_data() const;
    const Status get_status() const;

    void run();
private:
    const Display *display;
    GameData data;
    Status status;
    int lastId;

    Binder binder;
    std::map<int, std::unique_ptr<EventListener>> eventListeners;

    void handle_message(const Message &message);
    void kill(int id);
    void addEventListener(std::shared_ptr<NewEventListenerInfo> info);
};