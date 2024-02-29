#pragma once

#include "GameData.h"
#include "NewEventListenerInfo.h"
#include <string>

class Message {
public:
    Message();
    GameData delta;
    NewEventListenerInfo newEventListenerInfo;
    bool kill;
    int listenerId;
};