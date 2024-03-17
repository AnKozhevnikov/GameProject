#include "AbilityDrawer.h"
#include "Display.h"
#include "Ability.h"
#include "BattleViewManager.h"
#include "BattleViewConstants.h"

using std::vector;

AbilityDrawer::AbilityDrawer(const Ability &ability_, int x_, int y_) {
    x = x_;
    y = y_;
    ability = ability_;
    Display display;
    display.DrawSprite(ability.get_sprite(), x + 1, y + 1);
    display.DrawText(ability.get_hint(), x + BattleViewConstants::AbilityIconLength + 1, y + 1, BattleViewConstants::AbilityTextLength);
}

AbilityDrawer::~AbilityDrawer() {
    Display display;
    display.DrawSprite(std::vector<std::vector<unsigned>> (BattleViewConstants::AbilityHeight,
            std::vector<unsigned> (BattleViewConstants::AbilityLength, ' ')), x, y);
}

Ability AbilityDrawer::GetAbility() const {
    return ability;
}

void AbilityDrawer::SelectAbility(bool state) { //True for select, false for unselect
    Display display;
    ColorManager manager;
    vector<vector<unsigned>> box(BattleViewConstants::AbilityIconHeight, vector<unsigned> (BattleViewConstants::AbilityIconLength, 0));
    unsigned boxChar;
    if(state) {
        boxChar = '#' | A_BLINK | manager.CreateColorPair(COLOR_RED, -1);
    }
    else{
        boxChar = ' ' | manager.CreateColorPair(-1, -1);
    }
    for(auto &el : box) {
        el[0] = boxChar;
        el[BattleViewConstants::AbilityIconLength - 1] = boxChar;
    }
    for(int i = 0; i < BattleViewConstants::AbilityIconLength; ++i) {
        box[0][i] = boxChar;
        box[BattleViewConstants::AbilityIconHeight - 1][i] = boxChar;
    }
    display.DrawSprite(box, x, y);
}