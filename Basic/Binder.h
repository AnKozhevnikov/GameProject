#pragma once

#include "Message.h"
#include <functional>

class Binder {
public:
    const std::function<Message()> getFunc(char c);
private:
    Message empty() {
        return Message();
    }
};