#include <memory>
#include "Game.h"

Game::Game() {
    data = GameData();
    binder = Binder();
    status = RUNNING;
}

const GameData& Game::get_data() const {
    return data;
}

const Game::Status Game::get_status() const {
    return status;
}

void Game::run() {
    while (status == RUNNING) {
        char pressed = KeyboardListener::get_pressed();
        Message message = binder.getFunc(pressed)();
        if (eventListeners[message.listenerId].parent == 0) {
            data.update(message.delta);
        } else {
            eventListeners[eventListeners[message.listenerId].parent].update(message.delta);
        }
        if (message.kill) {
            if (eventListeners[message.listenerId].parent != 0) {
                eventListeners[eventListeners[message.listenerId].parent].unfreeze();
            }
            kill(message.listenerId);
        }
        if (message.newEventListenerInfo.eventType != "void") {
            addEventListener(message.newEventListenerInfo);
        }
    }
}

void Game::kill(int id) {
    eventListeners.erase(id);
}

void Game::addEventListener(NewEventListenerInfo info) {
    //TODO: implement
}