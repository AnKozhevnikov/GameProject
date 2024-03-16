#pragma once
#include <map>
#include <vector>
#include <string>
#include "bitmap_image.hpp"
#include "Display.h"

class Drawer {
public:
    static inline std::map<std::string, std::vector<std::vector<unsigned int>>> sprites;

    static void readSprite(std::string name);
    static std::vector<std::vector<unsigned int>> getSprite(std::string name);
};