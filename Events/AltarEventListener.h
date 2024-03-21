#pragma once

#include "EventListener.h"

class AltarEventListener : public EventListener {
public:
    AltarEventListener(const int newId, const int parent, const GameData *data, Binder *binder);
private:
    void init();
    void redraw();
    Message destroy();
    Message use();
    Message exit();
    Message update();

    std::vector<std::shared_ptr<HeroManager>> heroes;

    std::string altarStatus;
};