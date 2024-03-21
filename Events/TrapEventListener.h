#pragma once

#include "EventListener.h"

class TrapEventListener : public EventListener {
public:
    TrapEventListener(const int newId, const int parent, const GameData *data, Binder *binder);
private:
    Message init();
    std::vector<std::shared_ptr<HeroManager>> we;
    //void draw();
    Message exit();
    Message update();
};