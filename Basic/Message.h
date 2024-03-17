#pragma once

#include "GameData.h"
#include "NewEventListenerInfo.h"
#include <string>

class Message {
public:
    Message();
    Message(GameData delta, NewEventListenerInfo newEventListenerInfo, bool kill, int listenerId);
    GameData delta;
    std::shared_ptr<NewEventListenerInfo> newEventListenerInfo;
    bool kill;
    int listenerId;
    bool empty;
};