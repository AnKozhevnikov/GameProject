#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Ability.h"

class Hero {
public:
    Hero() = default;
    Hero(std::string name, int maxHp, int hp, int dmg, int initiative, int attention, std::vector<std::vector<unsigned>> sprite, std::vector<Ability> abilities);
    Hero(const Hero &other);
    Hero& operator=(const Hero &other);

    void update(const Hero &delta);

    std::string get_name() const;
    std::shared_ptr<std::string> get_name_ptr() const;
    void set_name(std::string new_name);

    int get_maxHp() const;
    std::shared_ptr<int> get_maxHp_ptr() const;
    void set_maxHp(int new_maxHp);

    int get_hp() const;
    std::shared_ptr<int> get_hp_ptr() const;
    void set_hp(int new_hp);

    int get_dmg() const;
    std::shared_ptr<int> get_dmg_ptr() const;
    void set_dmg(int new_dmg);

    int get_initiative() const;
    std::shared_ptr<int> get_initiative_ptr() const;
    void set_initiative(int new_initiative);

    int get_attention() const;
    std::shared_ptr<int> get_attention_ptr() const;
    void set_attention(int new_attention);

    std::vector<std::vector<unsigned>> get_sprite() const;
    std::shared_ptr<std::vector<std::vector<unsigned>>> get_sprite_ptr() const;
    void set_sprite(const std::vector<std::vector<unsigned>> &new_sprite);

    std::vector<Ability> get_abilities() const;
    std::shared_ptr<std::vector<Ability>> get_abilities_ptr() const;
    void set_abilities(const std::vector<Ability> &new_abilities);
private:
    std::shared_ptr<std::string> name;
    std::shared_ptr<int> maxHp;
    std::shared_ptr<int> hp;
    std::shared_ptr<int> dmg;
    std::shared_ptr<int> initiative;
    std::shared_ptr<int> attention;
    std::shared_ptr<std::vector<std::vector<unsigned>>> sprite;
    std::shared_ptr<std::vector<Ability>> abilities;
};