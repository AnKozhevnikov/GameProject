#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <random>
#include <tuple>
#include <algorithm>

#include "Hero.h"
#include "BattleSamples.h"

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

std::vector<Hero> getRandomSquad(int difficulty, int sz, bool side) {

}
}