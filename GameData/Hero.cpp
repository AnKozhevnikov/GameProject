#include "Hero.h"

Hero::Hero(std::string name, int maxHp, int hp, int dmg, int initiative, int attention, std::vector<std::vector<unsigned>> sprite, std::vector<Ability> abilities) {
    this->name = std::make_shared<std::string>(name);
    this->maxHp = std::make_shared<int>(maxHp);
    this->hp = std::make_shared<int>(hp);
    this->dmg = std::make_shared<int>(dmg);
    this->initiative = std::make_shared<int>(initiative);
    this->attention = std::make_shared<int>(attention);
    this->sprite = std::make_shared<std::vector<std::vector<unsigned>>>(sprite);
    this->abilities = std::make_shared<std::vector<Ability>>(abilities);
}

Hero::Hero(const Hero &other) {
    name = std::make_shared<std::string>(*other.name);
    maxHp = std::make_shared<int>(*other.maxHp);
    hp = std::make_shared<int>(*other.hp);
    dmg = std::make_shared<int>(*other.dmg);
    initiative = std::make_shared<int>(*other.initiative);
    attention = std::make_shared<int>(*other.attention);
    sprite = std::make_shared<std::vector<std::vector<unsigned>>>(*other.sprite);
    abilities = std::make_shared<std::vector<Ability>>(*other.abilities);
}

Hero& Hero::operator=(const Hero &other) {
    if (other.name != nullptr) name = std::make_shared<std::string>(*other.name);
    else name = nullptr;

    if (other.maxHp != nullptr) maxHp = std::make_shared<int>(*other.maxHp);
    else maxHp = nullptr;

    if (other.hp != nullptr) hp = std::make_shared<int>(*other.hp);
    else hp = nullptr;

    if (other.dmg != nullptr) dmg = std::make_shared<int>(*other.dmg);
    else dmg = nullptr;

    if (other.initiative != nullptr) initiative = std::make_shared<int>(*other.initiative);
    else initiative = nullptr;

    if (other.attention != nullptr) attention = std::make_shared<int>(*other.attention);
    else attention = nullptr;

    if (other.sprite != nullptr) sprite = std::make_shared<std::vector<std::vector<unsigned>>>(*other.sprite);
    else sprite = nullptr;

    if (other.abilities != nullptr) abilities = std::make_shared<std::vector<Ability>>(*other.abilities);
    else abilities = nullptr;
    
    return *this;
}

std::string Hero::get_name() const {
    return *name;
}

std::shared_ptr<std::string> Hero::get_name_ptr() const {
    return name;
}

void Hero::set_name(std::string new_name) {
    name = std::make_shared<std::string>(new_name);
}

int Hero::get_maxHp() const {
    return *maxHp;
}

std::shared_ptr<int> Hero::get_maxHp_ptr() const {
    return maxHp;
}

void Hero::set_maxHp(int new_maxHp) {
    maxHp = std::make_shared<int>(new_maxHp);
}

int Hero::get_hp() const {
    return *hp;
}

std::shared_ptr<int> Hero::get_hp_ptr() const {
    return hp;
}

void Hero::set_hp(int new_hp) {
    hp = std::make_shared<int>(new_hp);
}

int Hero::get_dmg() const {
    return *dmg;
}

std::shared_ptr<int> Hero::get_dmg_ptr() const {
    return dmg;
}

void Hero::set_dmg(int new_dmg) {
    dmg = std::make_shared<int>(new_dmg);
}

int Hero::get_initiative() const {
    return *initiative;
}

std::shared_ptr<int> Hero::get_initiative_ptr() const {
    return initiative;
}

void Hero::set_initiative(int new_initiative) {
    initiative = std::make_shared<int>(new_initiative);
}

int Hero::get_attention() const {
    return *attention;
}

std::shared_ptr<int> Hero::get_attention_ptr() const {
    return attention;
}

void Hero::set_attention(int new_attention) {
    attention = std::make_shared<int>(new_attention);
}

std::vector<std::vector<unsigned>> Hero::get_sprite() const {
    return *sprite;
}

std::shared_ptr<std::vector<std::vector<unsigned>>> Hero::get_sprite_ptr() const {
    return sprite;
}

void Hero::set_sprite(const std::vector<std::vector<unsigned>> &new_sprite) {
    sprite = std::make_shared<std::vector<std::vector<unsigned>>>(new_sprite);
}

std::vector<Ability> Hero::get_abilities() const {
    return *abilities;
}

std::shared_ptr<std::vector<Ability>> Hero::get_abilities_ptr() const {
    return abilities;
}

void Hero::set_abilities(const std::vector<Ability> &new_abilities) {
    abilities = std::make_shared<std::vector<Ability>>(new_abilities);
}

void Hero::update(const Hero &delta) {
    if (delta.name != nullptr) {
        name = std::make_shared<std::string>(*delta.name);
    }
    if (delta.maxHp != nullptr) {
        maxHp = std::make_shared<int>(*delta.maxHp);
    }
    if (delta.hp != nullptr) {
        hp = std::make_shared<int>(*delta.hp);
    }
    if (delta.dmg != nullptr) {
        dmg = std::make_shared<int>(*delta.dmg);
    }
    if (delta.initiative != nullptr) {
        initiative = std::make_shared<int>(*delta.initiative);
    }
    if (delta.attention != nullptr) {
        attention = std::make_shared<int>(*delta.attention);
    }
    if (delta.sprite != nullptr) {
        sprite = std::make_shared<std::vector<std::vector<unsigned>>>(*delta.sprite);
    }
    if (delta.abilities != nullptr) {
        abilities = std::make_shared<std::vector<Ability>>(*delta.abilities);
    }
}