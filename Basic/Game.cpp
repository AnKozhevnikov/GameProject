#include <memory>
#include "Game.h"
#include "KeyboardListener.h"
#include "FieldEventListener.h"
#include "FieldEventListenerInfo.h"

Game::Game(const Display *newDisplay) {
    display = newDisplay;
    data = GameData();
    binder = Binder();
    status = RUNNING;
    lastId = 0;
    addEventListener(FieldEventListenerInfo(0, false));
}

const GameData& Game::get_data() const {
    return data;
}

const Game::Status Game::get_status() const {
    return status;
}

void Game::run() {
    while (!data.get_is_game_over()) {
        char pressed = KeyboardListener::getKeyPressed(*display);
        Message message = binder.getFunc(pressed)();
        handle_message(message);
        const std::set<BindedData> noCharachter = binder.getNoCharachter();
        for (auto it : noCharachter) {
            Message message = it.func();
            handle_message(message);
        }
    }
    display->SendEvent(WindowEvent(WindowEvent::INFO, "Game over"));
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
    display->ClearGraphixWindow();
    if (eventListeners[id]->parent != 0) eventListeners[eventListeners[id]->parent]->unfreeze();
    std::map<BindedData, int> binded = eventListeners[id]->getBinded();
    for (auto it = binded.begin(); it != binded.end(); it++) {
        binder.stop(it->first);
    }
    eventListeners.erase(id);
    std::set<int> toErase;
    for (auto it=eventListeners.begin(); it!=eventListeners.end(); it++) {
        if (it->second->parent == id) {
            toErase.insert(it->first);
        }
    }

    for (auto it=toErase.begin(); it!=toErase.end(); it++) {
        kill(*it);
    }
}

void Game::addEventListener(NewEventListenerInfo info) {
    if (info.freeze) {
        eventListeners[info.parent]->freeze();
    }

    if (info.eventType == "field") {
        std::unique_ptr<EventListener> fieldEventListener = std::make_unique<FieldEventListener>(++lastId, info.parent, &data, &binder);
        eventListeners[lastId] = std::move(fieldEventListener);
    }

    if (info.eventType == "void") {
        return;
    }
}
