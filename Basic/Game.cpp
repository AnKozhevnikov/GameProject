#include <memory>
#include "Game.h"
#include "BattleSamples.h"
#include "KeyboardListener.h"
#include "FieldEventListener.h"
#include "FieldEventListenerInfo.h"
#include "BattleEventListener.h"
#include "BattleEventListenerInfo.h"
#include "MainMenuEventListener.h"
#include "MainMenuEventListenerInfo.h"
#include "InventoryEventListener.h"
#include "InventoryEventListenerInfo.h"
#include "BattleInventoryEventListener.h"
#include "BattleInventoryEventListenerInfo.h"
#include "NpcEncounterEventListener.h"
#include "NpcEventListenerInfo.h"
#include "AltarEventListener.h"
#include "AltarEventListenerInfo.h"
#include "ReviveEventListener.h"
#include "ReviveEventListenerInfo.h"
#include "TrapEventListener.h"
#include "TrapEventListenerInfo.h"
#include "ChestEventListener.h"
#include "ChestEventListenerInfo.h"

Game::Game(const Display *newDisplay) {
    display = newDisplay;
    binder = Binder();
    data = GameData(true);
    status = RUNNING;
    lastId = 0;
    addEventListener(std::make_shared<MainMenuEventListenerInfo>(0, false));
}

const GameData& Game::get_data() const {
    return data;
}

const Game::Status Game::get_status() const {
    return status;
}

void Game::run() {
    while (status == RUNNING) {
        if (data.get_is_game_over()) {
            status = FINISHED;
            break;
        }

        char pressed = KeyboardListener::getKeyPressed(*display);
        Message message = binder.getFunc(pressed)();
        handle_message(message);
        const std::set<BindedData> noCharachter = binder.getNoCharachter();
        for (auto it : noCharachter) {
            if (binder.exists(it)) {
                Message message = it.func();
                handle_message(message);
            }
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
        int parent = eventListeners[message.listenerId]->parent;
        kill(message.listenerId);
        if (parent != 0) eventListeners[parent]->unfreeze();
    }
    if (message.newEventListenerInfo->eventType != "void") {
        addEventListener(message.newEventListenerInfo);
    }
}

void Game::kill(int id) {
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

    display->ClearGraphixWindow();
}

void Game::addEventListener(std::shared_ptr<NewEventListenerInfo> info) {
    if (info->freeze) {
        eventListeners[info->parent]->freeze();
        display->ClearGraphixWindow();
    }

    if (info->eventType == "void") {
        return;
    }

    if (info->eventType == "MainMenu") {
        std::unique_ptr<EventListener> mainMenuEventListener = std::make_unique<MainMenuEventListener>(++lastId, info->parent, info->parent==0 ? &data : eventListeners[info->parent]->get_data_ptr(), &binder);
        eventListeners[lastId] = std::move(mainMenuEventListener);
    }

    if (info->eventType == "field") {
        std::unique_ptr<EventListener> fieldEventListener = std::make_unique<FieldEventListener>(++lastId, info->parent, info->parent==0 ? &data : eventListeners[info->parent]->get_data_ptr(), &binder);
        eventListeners[lastId] = std::move(fieldEventListener);
    }

    if (info->eventType == "battle") {
        std::shared_ptr<BattleEventListenerInfo> battleInfo = std::dynamic_pointer_cast<BattleEventListenerInfo>(info);
        std::unique_ptr<EventListener> battleEventListener = std::make_unique<BattleEventListener>(++lastId, info->parent, info->parent==0 ? &data : eventListeners[info->parent]->get_data_ptr(), &binder, battleInfo->enemies);
        eventListeners[lastId] = std::move(battleEventListener);
    }

    if (info->eventType == "inventory") {
        std::unique_ptr<EventListener> inventoryEventListener = std::make_unique<InventoryEventListener>(++lastId, info->parent, info->parent==0 ? &data : eventListeners[info->parent]->get_data_ptr(), &binder);
        eventListeners[lastId] = std::move(inventoryEventListener);
    }

    if (info->eventType == "battle inventory") {
        std::unique_ptr<EventListener> battleInventoryEventListener = std::make_unique<BattleInventoryEventListener>(++lastId, info->parent, info->parent==0 ? &data : eventListeners[info->parent]->get_data_ptr(), &binder);
        eventListeners[lastId] = std::move(battleInventoryEventListener);
    }

    if (info->eventType == "npc") {
        std::shared_ptr<NpcEventListenerInfo> npcInfo = std::dynamic_pointer_cast<NpcEventListenerInfo>(info);
        std::unique_ptr<EventListener> npcEncounterEventListener = std::make_unique<NpcEncounterEventListener>(++lastId, info->parent, info->parent==0 ? &data : eventListeners[info->parent]->get_data_ptr(), &binder, npcInfo->hero, npcInfo->price);
        eventListeners[lastId] = std::move(npcEncounterEventListener);
    }

    if (info->eventType == "altar") {
        std::unique_ptr<EventListener> altarEventListener = std::make_unique<AltarEventListener>(++lastId, info->parent, info->parent==0 ? &data : eventListeners[info->parent]->get_data_ptr(), &binder);
        eventListeners[lastId] = std::move(altarEventListener);
    }

    if (info->eventType == "revive") {
        std::shared_ptr<ReviveEventListenerInfo> reviveInfo = std::dynamic_pointer_cast<ReviveEventListenerInfo>(info);
        std::unique_ptr<EventListener> npcEncounterEventListener = std::make_unique<ReviveEventListener>(++lastId, info->parent, info->parent==0 ? &data : eventListeners[info->parent]->get_data_ptr(), &binder, reviveInfo->price);
        eventListeners[lastId] = std::move(npcEncounterEventListener);
    }

    if (info->eventType == "trap") {
        std::unique_ptr<EventListener> trapEventListener = std::make_unique<TrapEventListener>(++lastId, info->parent, info->parent==0 ? &data : eventListeners[info->parent]->get_data_ptr(), &binder);
        eventListeners[lastId] = std::move(trapEventListener);
    }

    if (info->eventType == "chest") {
        std::unique_ptr<EventListener> chestEventListener = std::make_unique<ChestEventListener>(++lastId, info->parent, info->parent==0 ? &data : eventListeners[info->parent]->get_data_ptr(), &binder);
        eventListeners[lastId] = std::move(chestEventListener);
    }
}
