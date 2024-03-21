#pragma once

#include "EventListener.h"

class ChestEventListener : public EventListener {
public:
    ChestEventListener(const int newId, const int parent, const GameData *data, Binder *binder);
private:
    void init();
    void redraw();
    Message open(int value);
    Message exit();

    std::vector<std::shared_ptr<HeroManager>> heroes;

    std::string chestStatus;
};