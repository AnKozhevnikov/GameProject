#include "Drawer.h"

void Drawer::readSprite(std::string name) {
    bitmap_image sprite("../Sprites/" + name + ".bmp");
    int n = sprite.height();
    int m = sprite.width();
    Display display;
    static ColorManager manager;
    Drawer::sprites[name].resize(n, std::vector<unsigned int>(m, 0));
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            unsigned char red, green, blue;
            sprite.get_pixel(j, i, red, green, blue);
            Drawer::sprites[name][i][j] = manager.CreateColorPair(-1, ColorManager::getColor(red, green, blue)) | ' ';
        }
    }
}

std::vector<std::vector<unsigned int>> Drawer::getSprite(std::string name) {
    if (Drawer::sprites.find(name) == Drawer::sprites.end()) {
        readSprite(name);
    }
    return sprites[name];
}