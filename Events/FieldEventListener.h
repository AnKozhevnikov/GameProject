#pragma once

#include "EventListener.h"

class FieldEventListener : public EventListener {
public:
    FieldEventListener(const int newId, const int parent, const GameData *data, Binder *binder);
private:
    void init();
    void redraw();
    void draw_cell(int x, int y, std::string state);
    Message move(int direction);
};