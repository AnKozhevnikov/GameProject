#include <memory>
#include "Game.h"
#include "KeyboardListener.h"
#include "FieldEventListener.h"

Game::Game(const Display *newDisplay) {
    display = newDisplay;
    data = GameData();
    binder = Binder();
    status = RUNNING;
    std::unique_ptr<EventListener> fieldEventListener = std::make_unique<FieldEventListener>(1, 0, &data, &binder);
    eventListeners[1] = std::move(fieldEventListener);
}

const GameData& Game::get_data() const {
    return data;
}

const Game::Status Game::get_status() const {
    return status;
}

void Game::run() {
    while (status == RUNNING) {
        char pressed = KeyboardListener::getKeyPressed(*display);
        Message message = binder.getFunc(pressed)();
        handle_message(message);
        const std::set<BindedData>& noCharachter = binder.getNoCharachter();
        for (auto it = noCharachter.begin(); it != noCharachter.end(); it++) {
            Message message = it->func();
            handle_message(message);
        }
    }
}

void Game::handle_message(const Message &message) {
    if (message.empty) {
        return;
    }
    if (eventListeners[message.listenerId]->parent == 0) {
        data.update(message.delta);
    } else {
        eventListeners[eventListeners[message.listenerId]->parent]->update(message.delta);
    }
    if (message.kill) {
        if (eventListeners[message.listenerId]->parent != 0) {
            eventListeners[eventListeners[message.listenerId]->parent]->unfreeze();
        }
        kill(message.listenerId);
    }
    if (message.newEventListenerInfo.eventType != "void") {
        addEventListener(message.newEventListenerInfo);
    }
}

void Game::kill(int id) {
    std::map<BindedData, int> binded = eventListeners[id]->getBinded();
    for (auto it = binded.begin(); it != binded.end(); it++) {
        binder.stop(it->first);
    }
    eventListeners.erase(id);
    display->ClearGraphixWindow();
}

void Game::addEventListener(NewEventListenerInfo info) {
    //TODO: implement
}