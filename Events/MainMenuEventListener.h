#pragma once

#include "EventListener.h"

class MainMenuEventListener : public EventListener
{
public:
    MainMenuEventListener(const int newId, const int parent, const GameData *data, Binder *binder);
private:
    void redraw();
    Message startGame();
    Message exit();
    Message playbattleSample();
    Message openInventory();
    Message NpcEncounter();
    Message revive();
};
