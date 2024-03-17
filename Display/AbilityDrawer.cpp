#include "AbilityDrawer.h"
#include "Display.h"
#include "Ability.h"
#include "BattleViewManager.h"

namespace {
    const int AbilityLength = 35;
    const int AbilityHeight = 6;
}

using std::vector;

AbilityDrawer::AbilityDrawer(const Ability &ability_, int x_, int y_) {
    x = x_;
    y = y_;
    ability = ability_;
    Display display;
    display.DrawSprite(ability.get_sprite(), x, y);
    display.DrawText(ability.get_hint(), x + BattleViewManager::AbilityBoxLength + 1, y);
}

AbilityDrawer::~AbilityDrawer() {
    Display display;
    display.DrawSprite(std::vector<std::vector<unsigned>> (AbilityHeight, std::vector<unsigned> (AbilityLength, ' ')), x, y);
}

Ability AbilityDrawer::GetAbility() const {
    return ability;
}

void AbilityDrawer::SelectAbility(bool state) { //True for select, false for unselect
    Display display;
    ColorManager manager;
    vector<vector<unsigned>> box(AbilityHeight, vector<unsigned> (AbilityLength, 0));
    unsigned boxChar;
    if(state) {
        boxChar = ' ' | A_BLINK | manager.CreateColorPair(COLOR_RED, COLOR_RED);
    }
    else{
        boxChar = ' ' | manager.CreateColorPair(-1, -1);
    }
    for(auto &el : box) {
        el[0] = boxChar;
        el[AbilityLength - 1] = boxChar;
    }
    for(int i = 0; i < AbilityLength; ++i) {
        box[0][i] = boxChar;
        box[AbilityHeight - 1][i] = boxChar;
    }
    display.DrawSprite(box, x, y);
}