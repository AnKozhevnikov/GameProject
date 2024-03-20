#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <random>
#include <tuple>
#include <algorithm>

using namespace std;

struct Coordinate;

namespace Randomizer {
int getRandom(int max) {
    static random_device rd;
    static mt19937 gen(rd());

    uniform_int_distribution<> dist(0, max - 1);

    return dist(gen);
}

vector<Coordinate> randomShuffle(vector<Coordinate> vec) {
    static random_device rd;
    static mt19937 gen(rd());

    shuffle(vec.begin(), vec.end(), gen);

    return vec;
}
}