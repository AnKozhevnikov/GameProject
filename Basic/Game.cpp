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
        data.update(message.delta);
        if (message.kill) {
            kill(message.listenerId);
        }
        if (message.newEventListener != "void") {
            addEventListener(message.newEventListener);
        }
    }
}

void Game::kill(int id) {
    for (int i = 0; i < eventListeners.size(); i++) {
        if (eventListeners[i].getId() == id) {
            eventListeners.erase(eventListeners.begin() + i);
            return;
        }
    }
}

void Game::addEventListener(const std::string& newEventListener) {
    //TODO: implement
}