#include "Hero.h"
#include "Drawer.h"
#include "Item.h"

namespace SampleAbilities {
    // order: name, hint, team, multitarget, damage, heal, healStatus, burn, stun
    static Ability voidAbility = Ability("void", "void", Drawer::getSprite("SampleAbility"), false, false, 0, 0, 0, 0, 0);
    static Ability basicAttack = Ability("Basic Attack", "Deal damage to one enemy", Drawer::getSprite("abil_bonk"), false, false, 1, 0, 0, 0, 0);

    static Ability shieldBash = Ability("Shield Bash", "Stun one enemy for 2 moves", Drawer::getSprite("abil_bonk"), false, false, 0.5, 0, 0, 0, 2);
    static Ability roar = Ability("Roar", "Heal one ally", Drawer::getSprite("abil_heak"), true, false, 0, 1, 0, 0, 0);
    static Ability fireStorm = Ability("Fire Storm", "Set all enemies on fire for 2 moves", Drawer::getSprite("abil_fire"), false, true, 0, 0, 0, 2, 0);
    static Ability splash = Ability("Splash", "Deal damage to all enemies", Drawer::getSprite("abil_magic"), false, true, 0.5, 0, 0, 0, 0);
    static Ability fireArrow = Ability("Fire Arrow", "Deal damage to one enemy and put him on fire for 2 moves", Drawer::getSprite("abil_fire"), false, false, 0.5, 0, 0, 2, 0);
    static Ability heavyArrow = Ability("Heavy Arrow", "Deal damage to one enemy and stun him for 1 move", Drawer::getSprite("abil_poison"), false, false, 0.7, 0, 0, 0, 1);
    static Ability fireShow = Ability("Fire Show", "Stun an enemy and set him on fire", Drawer::getSprite("abil_fire"), false, false, 0, 0, 0, 1, 1);
    static Ability sneakAttack = Ability("Sneak Attack", "Deal damage to one enemy and stun him for 1 move", Drawer::getSprite("abil_bullet"), false, false, 0.7, 0, 0, 0, 1);
    static Ability callOfNature = Ability("Call of Nature", "Remove all status effects from your allies", Drawer::getSprite("abil_heal"), true, true, 0, 0, 1, 0, 0);
    static Ability inspiration = Ability("Inspiration", "Heal all your allies for a small amount", Drawer::getSprite("abil_poison"), true, true, 0, 0.4, 0, 0, 0);

    static Ability rage = Ability("Rage", "Clear all status effects", Drawer::getSprite("SampleAbility"), true, false, 0, 0, 1, 0, 0);
    static Ability swipe = Ability("Swipe", "Deal damage to all enemies", Drawer::getSprite("SampleAbility"), false, true, 0.8, 0, 0, 0, 0);
    static Ability scare = Ability("Scare", "Deal damage to one enemy and stun him for 1 move", Drawer::getSprite("SampleAbility"), false, false, 0.7, 0, 0, 0, 1);
    static Ability vaporise = Ability("Vaporise", "Heal all allies for a small amount", Drawer::getSprite("SampleAbility"), true, true, 0, 0.25, 0, 0, 0);
    static Ability blah = Ability("Blah", "Set all enemies on fire for 2 turns", Drawer::getSprite("SampleAbility"), false, true, 0.3, 0, 0, 2, 0);
    static Ability bleh = Ability("Bleh", "Stun an enemy for 2 turns", Drawer::getSprite("SampleAbility"), false, false, 0.3, 0, 0, 0, 2);
    static Ability ribbit = Ability("Ribbit", "Stun an enemy and set him on fire", Drawer::getSprite("SampleAbility"), false, false, 0.4, 0, 0, 1, 1);
    static Ability hop = Ability("Hop", "Deal damage to all enemies", Drawer::getSprite("SampleAbility"), false, false, 0.7, 0, 0, 0, 0);

    static Ability healPotion = Ability("Heal Potion", "Heal everybody", Drawer::getSprite("SampleAbility"), true, true, 0, 1, 0, 0, 0);
    static Ability bomb = Ability("Bomb", "Deal damage to everybody", Drawer::getSprite("SampleAbility"), false, true, 0.4, 0, 0, 0, 0);
    static Ability fireBomb = Ability("Fire Bomb", "Put everyone on fire for 2 moves", Drawer::getSprite("SampleAbility"), false, true, 0, 0, 0, 2, 0);
    static Ability stunBomb = Ability("Stun Bomb", "Stun everybody for 2 moves", Drawer::getSprite("SampleAbility"), false, true, 0, 0, 0, 0, 2);
}

namespace SampleHeroes {
    static Hero voidHero = Hero("void", 0, 0, 0, 0, 0, std::vector<std::vector<unsigned>>(14, std::vector<unsigned>(14,0)), std::vector({SampleAbilities::basicAttack, SampleAbilities::basicAttack, SampleAbilities::basicAttack}));

    static Hero warrior = Hero("Warrior", 20, 20, 5, 3, 5, Drawer::getSprite("Warrior"), std::vector({SampleAbilities::basicAttack, SampleAbilities::shieldBash, SampleAbilities::roar}));
    static Hero mage = Hero("Mage", 15, 15, 7, 5, 3, Drawer::getSprite("Mage"), std::vector({SampleAbilities::basicAttack, SampleAbilities::fireStorm, SampleAbilities::splash}));
    static Hero archer = Hero("Archer", 18, 18, 6, 4, 4, Drawer::getSprite("Archer"), std::vector({SampleAbilities::basicAttack, SampleAbilities::fireArrow, SampleAbilities::heavyArrow}));
    static Hero thief = Hero("Thief", 12, 12, 7, 5, 5, Drawer::getSprite("thief"), std::vector({SampleAbilities::basicAttack, SampleAbilities::sneakAttack, SampleAbilities::fireShow}));
    static Hero elf = Hero("Elf", 14, 14, 3, 6, 6, Drawer::getSprite("elf"), std::vector({SampleAbilities::basicAttack, SampleAbilities::inspiration, SampleAbilities::callOfNature}));

    static Hero warriorEvil = Hero("Evil Warrior", 20, 20, 5, 3, 5, Drawer::getSprite("evil_warrior"), std::vector({SampleAbilities::basicAttack, SampleAbilities::shieldBash, SampleAbilities::roar}));
    static Hero mageEvil = Hero("Evil Mage", 15, 15, 7, 5, 3, Drawer::getSprite("evil_mage"), std::vector({SampleAbilities::basicAttack, SampleAbilities::fireStorm, SampleAbilities::splash}));
    static Hero archerEvil = Hero("Evil Archer", 18, 18, 6, 4, 4, Drawer::getSprite("evil_archer"), std::vector({SampleAbilities::basicAttack, SampleAbilities::fireArrow, SampleAbilities::heavyArrow}));
    static Hero thiefEvil = Hero("Evil Thief", 12, 12, 7, 5, 5, Drawer::getSprite("thief_evil"), std::vector({SampleAbilities::basicAttack, SampleAbilities::sneakAttack, SampleAbilities::fireShow}));
    static Hero elfEvil = Hero("Evil Elf", 14, 14, 3, 6, 6, Drawer::getSprite("elf_evil"), std::vector({SampleAbilities::basicAttack, SampleAbilities::inspiration, SampleAbilities::callOfNature}));

    static Hero megaWarrior = Hero("Mega Warrior", 50, 50, 9, 9, 9, Drawer::getSprite("mega_warrior"), std::vector({SampleAbilities::basicAttack, SampleAbilities::swipe, SampleAbilities::rage}));
    static Hero farmer = Hero("Farmer", 10, 10, 4, 1, 1, Drawer::getSprite("farmer"), std::vector({SampleAbilities::basicAttack, SampleAbilities::basicAttack, SampleAbilities::basicAttack}));

    static Hero ghost = Hero("Ghost", 40, 40, 8, 10, 10, Drawer::getSprite("ghost"), std::vector({SampleAbilities::basicAttack, SampleAbilities::scare, SampleAbilities::vaporise}));
    static Hero mini_ghost = Hero("Mini Ghost", 8, 8, 4, 5, 5, Drawer::getSprite("mini_ghost"), std::vector({SampleAbilities::basicAttack, SampleAbilities::basicAttack, SampleAbilities::basicAttack}));

    static Hero sheep = Hero("Sheep", 35, 35, 8, 1, 1, Drawer::getSprite("boss_sheep"), std::vector({SampleAbilities::basicAttack, SampleAbilities::blah, SampleAbilities::bleh}));
    static Hero mini_sheep = Hero("Mini Sheep", 7, 7, 3, 1, 1, Drawer::getSprite("sheep_assist"), std::vector({SampleAbilities::basicAttack, SampleAbilities::basicAttack, SampleAbilities::basicAttack}));

    static Hero frog = Hero("Frog", 30, 30, 7, 3, 3, Drawer::getSprite("frog"), std::vector({SampleAbilities::basicAttack, SampleAbilities::ribbit, SampleAbilities::hop}));
    static Hero fly = Hero("Fly", 6, 6, 3, 1, 1, Drawer::getSprite("fli_assist"), std::vector({SampleAbilities::basicAttack, SampleAbilities::basicAttack, SampleAbilities::basicAttack}));
}

namespace SampleItems {
    static Item gold = Item("Gold", 100, Drawer::getSprite("coin"), "Gold is used to buy items and abilities", SampleAbilities::voidAbility);
    static Item healthPotions = Item("Health Potions", 10, Drawer::getSprite("potion"), "Health Potions are used to heal your heroes", SampleAbilities::healPotion);
    static Item bombs = Item("Bombs", 10, Drawer::getSprite("bomb"), "Bombs are used to deal damage to enemies", SampleAbilities::bomb);
    static Item fireBombs = Item("Fire Bombs", 10, Drawer::getSprite("molotov"), "Fire Bombs are used to put enemies on fire", SampleAbilities::fireBomb);
    static Item stunBombs = Item("Stun Bombs", 10, Drawer::getSprite("flash"), "Stun Bombs are used to stun enemies", SampleAbilities::stunBomb);
}

namespace SampleSides {
    static std::vector<Hero> good = std::vector<Hero>({
        SampleHeroes::warrior, 
        SampleHeroes::mage, 
        SampleHeroes::archer,
        SampleHeroes::thief,
        SampleHeroes::elf});

    static std::vector<Hero> bad = std::vector<Hero>({
        SampleHeroes::warriorEvil,
        SampleHeroes::mageEvil,
        SampleHeroes::archerEvil,
        SampleHeroes::thiefEvil,
        SampleHeroes::elfEvil});

    static std::vector<std::vector<Hero>> bossTeams = std::vector<std::vector<Hero>>({
        std::vector<Hero>({SampleHeroes::megaWarrior, SampleHeroes::farmer}),
        std::vector<Hero>({SampleHeroes::ghost, SampleHeroes::mini_ghost}),
        std::vector<Hero>({SampleHeroes::sheep, SampleHeroes::mini_sheep}),
        std::vector<Hero>({SampleHeroes::frog, SampleHeroes::fly})
    });
}