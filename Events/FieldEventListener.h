#pragma once

#include "EventListener.h"

class FieldEventListener : public EventListener {
public:
    FieldEventListener(const int newId, const int parent, const GameData *data, Binder *binder);
private:
    void init();
    void redraw();
    Message move(int direction);
    Message finish();
    Message gameOverChecker();
    Message openInventory();
};