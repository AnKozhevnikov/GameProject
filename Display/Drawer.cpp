#include "Drawer.h"

std::map<std::string, std::vector<std::vector<unsigned int>>> Drawer::sprites;

void Drawer::readSprite(std::string name) {
    bitmap_image sprite("../Sprites/" + name + ".bmp");
    int n = sprite.height();
    int m = sprite.width();
    static ColorManager manager;
    sprites[name].resize(n, std::vector<unsigned int>(m, 0));
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            unsigned char red, green, blue;
            sprite.get_pixel(j, i, red, green, blue);
            sprites[name][i][j] = manager.CreateColorPair(-1, ColorManager::getColor(red, green, blue)) | ' ';
        }
    }
}

void Drawer::readAll() {
    Display display;
    readSprite("EmptyCorridor");
    readSprite("EmptyRoom");
    readSprite("CurrentRoom");
    readSprite("CurrentCorridor");
}