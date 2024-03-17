#include "NewEventListenerInfo.h"

#include <vector>
#include "Hero.h"

class BattleEventListenerInfo : public NewEventListenerInfo
{
public:
    BattleEventListenerInfo() : NewEventListenerInfo() {};
    BattleEventListenerInfo(int parent, bool freeze, std::vector<Hero> enemies) : NewEventListenerInfo(parent, freeze) {
        eventType = "battle";
        this->enemies = enemies;
    };
    ~BattleEventListenerInfo() {};

    std::vector<Hero> enemies;
};