#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <cmath>
#include <random>
#include <tuple>
#include <algorithm>

#include "Hero.h"
#include "BattleSamples.h"
#include "Ability.h"
#include "GameData.h"

using namespace SampleSides;
using namespace std;

namespace Randomizer {
static int getRandom(int max) {
    static random_device rd;
    static mt19937 gen(rd());

    uniform_int_distribution<> dist(0, max - 1);

    return dist(gen);
}

template<typename T>
static vector<T> randomShuffle(vector<T> vec) {
    static random_device rd;
    static mt19937 gen(rd());

    shuffle(vec.begin(), vec.end(), gen);

    return vec;
}

namespace StatsGenerator {
    int calculateHealth(shared_ptr<int> baseHealth, int depth, int maxTeamHealth, bool side, int difficulty, bool& isBoss) {
        const double alpha = side ? 1.0 : 1.2;
        const double beta = side ? 1.5 : 2.0;
        int health = (*baseHealth * pow(depth, alpha) + maxTeamHealth / beta) * (difficulty + isBoss + 1);
        isBoss = false;
        return health;
    }

    int calculateDamage(shared_ptr<int> baseDamage, int depth, int maxTeamDamage, bool side, int difficulty, bool& isBoss) {
        const double gamma = side ? 12.0 : 10.0;
        const double delta = side ? 1.5 : 1.0;
        const double epsilon = side ? 6.0 : 4.0;
        int damage = (*baseDamage * log(depth + delta) / log(gamma) + maxTeamDamage / epsilon) * (difficulty + isBoss +1);
        isBoss = false;
        return damage;
    }
};

vector<Hero> getRandomSquad(const int depth, const int maxTeamHealth, const int maxTeamDamage, int sz, const bool side, const int difficulty=0) {
    using namespace StatsGenerator;

    vector<Hero> charactersPattern = side ? good : (difficulty == 2 ? randomShuffle(bossTeams)[0] : evil[difficulty]);
    vector<Hero> Squad;

    bool isBoss = difficulty == 2;

    while (--sz) {
        Hero newHero = randomShuffle(charactersPattern)[0];
        newHero.set_maxHp(calculateHealth(newHero.get_hp_ptr(), depth, maxTeamHealth, side, difficulty, isBoss));
        newHero.set_dmg(calculateDamage(newHero.get_dmg_ptr(), depth, maxTeamHealth, side, difficulty, isBoss));
        newHero.set_hp(newHero.get_maxHp());
        newHero.set_attention(getRandom(10) + 1);
        newHero.set_initiative(getRandom(10) + 1);
        
        Squad.push_back(newHero);
    }

    return Squad;
}
}