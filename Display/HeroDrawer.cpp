#include "HeroDrawer.h"
#include "Display.h"
#include "BattleViewManager.h"
#include "BattleViewConstants.h"
#include "stdexcept"
#include <vector>

HeroDrawer::HeroDrawer(PHero phero, int x_, int y_) {
    x = x_;
    y = y_;
    Display display;

    std::shared_ptr<std::vector<std::vector<unsigned int>>> sprite = phero->get_sprite_ptr();
    if(sprite->size() != BattleViewConstants::HeroHeight) throw std::runtime_error("Invalid sprite height");
    for(const auto &line : *sprite) {
        if(line.size() > BattleViewConstants::HeroLength)
            throw std::runtime_error("Invalid sprite length");
    }
    display.DrawSprite(*sprite, x, y);

    //TODO Apply Effects
}

void HeroDrawer::SetChoice(bool state, short clr) const {
    Display display;
    ColorManager manager;
    if(state) {
        display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (BattleViewConstants::HeroLength, '=' | manager.CreateColorPair(clr, -1) | A_BLINK)), x, y + BattleViewConstants::HeroHeight + 1);
    }
    else{
        display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (BattleViewConstants::HeroLength, ' ' | manager.CreateColorPair(-1, -1))), x, y + BattleViewConstants::HeroHeight + 1);
    }
}

void HeroDrawer::SetHp(int cur_hp, int max_hp) {
    Display display;
    std::string hp = std::to_string(cur_hp) + "/" + std::to_string(max_hp) + " HP";
    display.DrawText(std::string(BattleViewConstants::HeroLength, ' '), x, y + BattleViewConstants::HeroHeight + 2); //Clear old hp
    display.DrawText(hp, x, y + BattleViewConstants::HeroHeight + 2); //Draw new hp
}

void HeroDrawer::SetDmg(int value) {
    Display display;
    std::string dmg = std::to_string(value) + " DMG";
    display.DrawText(std::string(BattleViewConstants::HeroLength / 2, ' '), x, y + BattleViewConstants::HeroHeight + 3); //Clear old dmg
    display.DrawText(dmg, x, y + BattleViewConstants::HeroHeight + 3); //Draw new dmg
}

void HeroDrawer::SetAttention(int value) {
    Display display;
    std::string attention = std::to_string(value) + " ATT";
    display.DrawText(std::string(BattleViewConstants::HeroLength / 2, ' '), x + BattleViewConstants::HeroLength / 2, y + BattleViewConstants::HeroHeight + 3); //Clear old attention
    display.DrawText(attention, x + BattleViewConstants::HeroLength / 2, y + BattleViewConstants::HeroHeight + 3); //Draw new attention
}

void HeroDrawer::SetName(const std::string &name) {
    Display display;
    display.DrawText(std::string(BattleViewConstants::HeroLength, ' '), x, y - 1); //Clear old name
    display.DrawText(name, x, y - 1); //Draw new name
}

void HeroDrawer::SetInitiative(int value) {
    Display display;
    std::string initiative = std::to_string(value) + " INIT";
    display.DrawText(std::string(BattleViewConstants::HeroLength, ' '), x, y + BattleViewConstants::HeroHeight + 4); //Clear old initiative
    display.DrawText(initiative, x, y + BattleViewConstants::HeroHeight + 4); //Draw new initiative
}

HeroDrawer::~HeroDrawer() {
    Display display;
    display.DrawSprite(std::vector<std::vector<unsigned>> (BattleViewConstants::HeroHeight + 5,
                std::vector<unsigned> (BattleViewConstants::HeroLength, ' ')), x, y-1);
}

void HeroDrawer::ApplyEffect(VisualEffect effect, bool state) const {
    Display display;
    ColorManager manager;
    short clr;
    switch(effect) {
        //Placeholders for now, will change later
        case VisualEffect::BURN:
            display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (' ' | manager.CreateColorPair(COLOR_RED, -1))), x, y + BattleViewConstants::HeroHeight + 5);
            break;
        case VisualEffect::STUN:
            display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (' ' | manager.CreateColorPair(COLOR_YELLOW, -1))), x, y + BattleViewConstants::HeroHeight + 5);
            break;
        case VisualEffect::HEAL:
            display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (' ' | manager.CreateColorPair(COLOR_GREEN, -1))), x, y + BattleViewConstants::HeroHeight + 5);
            break;
        case VisualEffect::DEAD:
            display.DrawSprite(std::vector<std::vector<unsigned>> (1, std::vector<unsigned> (' ' | manager.CreateColorPair(COLOR_BLACK, COLOR_RED))), x, y + BattleViewConstants::HeroHeight + 5);
            break;
        case VisualEffect::SELECT_AS_SOURCE:
            clr = ColorManager::getColor(255, 255, 0);
            SetChoice(state, clr);
            break;
        case VisualEffect::SELECT_AS_TARGET:
            clr = COLOR_RED;
            SetChoice(state, clr);
            break;
    }
}