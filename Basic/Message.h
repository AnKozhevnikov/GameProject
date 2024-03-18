#pragma once

#include "GameData.h"
#include "NewEventListenerInfo.h"
#include <string>
#include <memory>

class Message {
public:
    Message();
    Message(GameData delta, std::shared_ptr<NewEventListenerInfo> newEventListenerInfo, bool kill, int listenerId);
    GameData delta;
    std::shared_ptr<NewEventListenerInfo> newEventListenerInfo;
    bool kill;
    int listenerId;
    bool empty;
};