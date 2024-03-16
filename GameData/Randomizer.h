#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <random>
#include <tuple>
#include <algorithm>

using Coordinates = std::pair<int, int>;

namespace Randomizer {
static int getRandom(int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(0, max - 1);

    return dist(gen);
}

static void randomShuffle(std::vector<Coordinates>& vec) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    shuffle(vec.begin(), vec.end(), gen);
}
}