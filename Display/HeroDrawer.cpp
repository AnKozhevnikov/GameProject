#include "HeroDrawer.h"
#include "Display.h"
#include "BattleViewManager.h"
#include "BattleViewConstants.h"
#include "stdexcept"
#include <vector>
#include <chrono>
#include "Drawer.h"

HeroDrawer::HeroDrawer(PHero phero, int x_, int y_) {
    x = x_;
    y = y_;
    Display display;
    is_running = std::array<bool, VisualEffect::LAST> {false};
    start = timevec(VisualEffect::LAST);
    std::shared_ptr<std::vector<std::vector<unsigned int>>> sprite = phero->get_sprite_ptr();
    my_sprite = *sprite;
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

void HeroDrawer::ApplyEffect(VisualEffect effect, bool state) {
    Display display;
    ColorManager manager;
    short clr;
    switch(effect) {
        case VisualEffect::BURN:
            this->ApplyBurn(state);
            break;
        case VisualEffect::STUN:
            this->ApplyStun(state);
            break;
        case VisualEffect::HEAL:
            this->ApplyHeal(state);
            break;
        case VisualEffect::DEAD:
            this->ApplyDead(state);
            break;
        case VisualEffect::DAMAGE:
            this->ApplyDamage(state);
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

using std::chrono::milliseconds;
using namespace std::chrono_literals;

bool HeroDrawer::ApplyHeal(bool state) {
    Display display;
    ColorManager manager;
    if(state || is_running[VisualEffect::HEAL]) {
        if (!is_running[VisualEffect::HEAL]) {
            is_running[VisualEffect::HEAL] = true;
            start[VisualEffect::HEAL] = std::chrono::system_clock::now();
        }
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<milliseconds>(now - start[VisualEffect::HEAL]).count();

        if(elapsed > 1200) {
            display.DrawSprite(my_sprite, x, y);
            is_running[VisualEffect::HEAL] = false;
            return false;
        } else if(elapsed > 900) {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("heal3", '+'), x, y);
        } else if(elapsed > 600) {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("heal2", '+'), x, y);
        } else if(elapsed > 300) {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("heal1", '+'), x, y);
        }
        return true;
    }
    return is_running[VisualEffect::HEAL];
}

bool HeroDrawer::ApplyDamage(bool state) {
    Display display;
    ColorManager manager;
    if(state || is_running[VisualEffect::DAMAGE]) {
        if (!is_running[VisualEffect::DAMAGE]) {
            is_running[VisualEffect::DAMAGE] = true;
            start[VisualEffect::DAMAGE] = std::chrono::system_clock::now();
        }
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<milliseconds>(now - start[VisualEffect::DAMAGE]).count();

        if(elapsed > 1200) {
            display.DrawSprite(my_sprite, x, y);
            is_running[VisualEffect::DAMAGE] = false;
            return false;
        } else if(elapsed > 900) {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("damage3", '#'), x, y);
        } else if(elapsed > 600) {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("damage2", '#'), x, y);
        } else if(elapsed > 300) {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("damage1", '#'), x, y);
        }
        return true;
    }
    return is_running[VisualEffect::DAMAGE];
}

void HeroDrawer::ApplyBurn(int state) {
    ColorManager manager;
    Display display;
    if(state == 1 && !is_running[VisualEffect::BURN]) {
        is_running[VisualEffect::BURN] = true;
        start[VisualEffect::BURN] = std::chrono::system_clock::now();
    }
    if(state == 0) {
        is_running[VisualEffect::BURN] = false;
        display.DrawSprite(my_sprite, x, y);
    }
    if(is_running[VisualEffect::BURN]) {
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<milliseconds>(now - start[VisualEffect::BURN]).count();
        elapsed %= 900;
        if(elapsed > 600) {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("fire3"), x, y);
        } else if(elapsed > 300) {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("fire2"), x, y);
        }
        else{
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("fire1"), x, y);
        }
    }
}

void HeroDrawer::ApplyDead(int state) {
    ColorManager manager;
    Display display;
    if(state == 1 && !is_running[VisualEffect::DEAD]) {
        is_running[VisualEffect::DEAD] = true;
        start[VisualEffect::DEAD] = std::chrono::system_clock::now();
    }
    if(state == 0) {
        is_running[VisualEffect::DEAD] = false;
        display.DrawSprite(my_sprite, x, y);
    }
    if(is_running[VisualEffect::DEAD]) {
        std::vector<std::vector<unsigned>> EmptyWindow(BattleViewConstants::HeroHeight, std::vector<unsigned> (BattleViewConstants::HeroLength, ' ' | manager.CreateColorPair(-1, -1)));
        display.DrawSprite(EmptyWindow, x, y);
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<milliseconds>(now - start[VisualEffect::DEAD]).count();
        elapsed %= 900;
        if(elapsed > 600) {
            display.DrawSprite(Drawer::getSprite("dead3"), x, y);
        } else if(elapsed > 300) {
            display.DrawSprite(Drawer::getSprite("dead2"), x, y);
        }
        else{
            display.DrawSprite(Drawer::getSprite("dead1"), x, y);
        }
    }
}

void HeroDrawer::ApplyStun(int state) {
    ColorManager manager;
    Display display;
    if(state == 1 && !is_running[VisualEffect::STUN]) {
        is_running[VisualEffect::STUN] = true;
        start[VisualEffect::STUN] = std::chrono::system_clock::now();
    }
    if(state == 0) {
        is_running[VisualEffect::STUN] = false;
        display.DrawSprite(my_sprite, x, y);
    }
    if(is_running[VisualEffect::STUN]) {
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<milliseconds>(now - start[VisualEffect::STUN]).count();
        elapsed %= 1500;
        if(elapsed > 1350) {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("stun10", '*'), x, y);
        } else if(elapsed > 1200) {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("stun9", '*'), x, y);
        }
        else if (elapsed > 1050){
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("stun8", '*'), x, y);
        }
        else if (elapsed > 900){
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("stun7", '*'), x, y);
        }
        else if (elapsed > 750){
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("stun6", '*'), x, y);
        }
        else if (elapsed > 600){
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("stun5", '*'), x, y);
        }
        else if (elapsed > 450){
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("stun4", '*'), x, y);
        }
        else if (elapsed > 300){
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("stun3", '*'), x, y);
        }
        else if (elapsed > 150){
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("stun2", '*'), x, y);
        }
        else {
            display.DrawSprite(my_sprite, x, y);
            display.DrawSprite(Drawer::getSprite("stun1", '*'), x, y);
        }
    }
}

bool HeroDrawer::UpdateAnimations() {
    Display display;
    ColorManager manager;
    std::vector<std::vector<unsigned>> EmptyWindow(BattleViewConstants::HeroHeight, std::vector<unsigned> (BattleViewConstants::HeroLength, ' ' | manager.CreateColorPair(-1, -1)));
    display.DrawSprite(EmptyWindow, x, y);
    display.DrawSprite(my_sprite, x, y);
    this->ApplyBurn(-1);
    this->ApplyStun(-1);
    int result = this->ApplyHeal(false) + this->ApplyDamage(false);
    this->ApplyDead(-1);

    return result == 0;
}
