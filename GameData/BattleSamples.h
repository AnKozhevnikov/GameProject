#include "Hero.h"
#include "Drawer.h"

namespace SampleAbilities {
    // order: name, hint, team, multitarget, damage, heal, healStatus, burn, stun
    static Ability basicAttack = Ability("Basic Attack", "Deal damage to one enemy", Drawer::getSprite("SampleAbility"), false, false, 1, 0, 0, 0, 0);
    static Ability shieldBash = Ability("Shield Bash", "Stun one enemy for 2 moves", Drawer::getSprite("SampleAbility"), false, false, 0.5, 0, 0, 0, 2);
    static Ability roar = Ability("Roar", "Heal one ally", Drawer::getSprite("SampleAbility"), true, false, 0, 1, 0, 0, 0);
    static Ability fireStorm = Ability("Fire Storm", "Deal damage to all enemies", Drawer::getSprite("SampleAbility"), false, true, 0.3, 0, 0, 0, 0);
    static Ability heal = Ability("Heal", "Heal all status effects", Drawer::getSprite("SampleAbility"), true, false, 0, 0, 1, 0, 0);
    static Ability fireArrow = Ability("Fire Arrow", "Deal damage to one enemy and put him on fire for 2 moves", Drawer::getSprite("SampleAbility"), false, false, 0.5, 0, 0, 2, 0);
    static Ability heavyArrow = Ability("Heavy Arrow", "Deal damage to one enemy and stun him for 1 move", Drawer::getSprite("SampleAbility"), false, false, 0.7, 0, 0, 0, 1);
}

namespace SampleHeroes {
    static Hero voidHero = Hero("void", 0, 0, 0, 0, 0, std::vector<std::vector<unsigned>>(14, std::vector<unsigned>(14,0)), std::vector({SampleAbilities::basicAttack, SampleAbilities::basicAttack, SampleAbilities::basicAttack}));
    static Hero warrior = Hero("Warrior", 20, 20, 5, 3, 5, Drawer::getSprite("Warrior"), std::vector({SampleAbilities::basicAttack, SampleAbilities::shieldBash, SampleAbilities::roar}));
    static Hero mage = Hero("Mage", 15, 15, 7, 5, 3, Drawer::getSprite("Mage"), std::vector({SampleAbilities::basicAttack, SampleAbilities::fireStorm, SampleAbilities::heal}));
    static Hero archer = Hero("Archer", 18, 18, 6, 4, 4, Drawer::getSprite("Archer"), std::vector({SampleAbilities::basicAttack, SampleAbilities::fireArrow, SampleAbilities::heavyArrow}));
}