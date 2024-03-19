#include "Hero.h"
#include "Drawer.h"

namespace SampleAbilities {
    // order: name, hint, team, multitarget, damage, heal, healStatus, burn, stun
    static Ability voidAbility = Ability("void", "void", Drawer::getSprite("SampleAbility"), false, false, 0, 0, 0, 0, 0);
    static Ability basicAttack = Ability("Basic Attack", "Deal damage to one enemy", Drawer::getSprite("SampleAbility"), false, false, 1, 0, 0, 0, 0);
    static Ability shieldBash = Ability("Shield Bash", "Stun one enemy for 2 moves", Drawer::getSprite("SampleAbility"), false, false, 0.5, 0, 0, 0, 2);
    static Ability roar = Ability("Roar", "Heal one ally", Drawer::getSprite("SampleAbility"), true, false, 0, 1, 0, 0, 0);
    static Ability fireStorm = Ability("Fire Storm", "Deal damage to all enemies", Drawer::getSprite("SampleAbility"), false, true, 0.3, 0, 0, 0, 0);
    static Ability heal = Ability("Heal", "Heal all status effects", Drawer::getSprite("SampleAbility"), true, false, 0, 0, 1, 0, 0);
    static Ability fireArrow = Ability("Fire Arrow", "Deal damage to one enemy and put him on fire for 2 moves", Drawer::getSprite("SampleAbility"), false, false, 0.5, 0, 0, 2, 0);
    static Ability heavyArrow = Ability("Heavy Arrow", "Deal damage to one enemy and stun him for 1 move", Drawer::getSprite("SampleAbility"), false, false, 0.7, 0, 0, 0, 1);

    static Ability healPotion = Ability("Heal Potion", "Heal everybody", Drawer::getSprite("SampleAbility"), true, true, 0, 1, 0, 0, 0);
    static Ability bomb = Ability("Bomb", "Deal damage to everybody", Drawer::getSprite("SampleAbility"), false, true, 0.4, 0, 0, 0, 0);
    static Ability fireBomb = Ability("Fire Bomb", "Put everyone on fire for 2 moves", Drawer::getSprite("SampleAbility"), false, true, 0, 0, 0, 2, 0);
    static Ability stunBomb = Ability("Stun Bomb", "Stun everybody for 2 moves", Drawer::getSprite("SampleAbility"), false, true, 0, 0, 0, 0, 2);
}

namespace SampleHeroes {
    static Hero voidHero = Hero("void", 0, 0, 0, 0, 0, std::vector<std::vector<unsigned>>(14, std::vector<unsigned>(14,0)), std::vector({SampleAbilities::basicAttack, SampleAbilities::basicAttack, SampleAbilities::basicAttack}));
    static Hero warrior = Hero("Warrior", 20, 20, 5, 3, 5, Drawer::getSprite("Warrior"), std::vector({SampleAbilities::basicAttack, SampleAbilities::shieldBash, SampleAbilities::roar}));
    static Hero mage = Hero("Mage", 15, 15, 7, 5, 3, Drawer::getSprite("Mage"), std::vector({SampleAbilities::basicAttack, SampleAbilities::fireStorm, SampleAbilities::heal}));
    static Hero archer = Hero("Archer", 18, 18, 6, 4, 4, Drawer::getSprite("Archer"), std::vector({SampleAbilities::basicAttack, SampleAbilities::fireArrow, SampleAbilities::heavyArrow}));
}

namespace SampleItems {
    static Item gold = Item("Gold", 100, Drawer::getSprite("SampleItem"), "Gold is used to buy items and abilities", SampleAbilities::voidAbility);
    static Item healthPotions = Item("Health Potions", 10, Drawer::getSprite("potion"), "Health Potions are used to heal your heroes", SampleAbilities::healPotion);
    static Item bombs = Item("Bombs", 10, Drawer::getSprite("bomb"), "Bombs are used to deal damage to enemies", SampleAbilities::bomb);
    static Item fireBombs = Item("Fire Bombs", 10, Drawer::getSprite("molotov"), "Fire Bombs are used to put enemies on fire", SampleAbilities::fireBomb);
    static Item stunBombs = Item("Stun Bombs", 10, Drawer::getSprite("flash"), "Stun Bombs are used to stun enemies", SampleAbilities::stunBomb);
}