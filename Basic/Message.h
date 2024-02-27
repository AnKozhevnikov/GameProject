#pragma once

#include "Delta.h"
#include <string>

class Message {
public:
    Message();
    Delta delta;
    std::string newEventListener;
    bool kill;
    int listenerId;
};