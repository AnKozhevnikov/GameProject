#include "Drawer.h"

void Drawer::readSprite(std::string name, int c) {
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
            if (red != 0 || green != 29 || blue != 255)
                if (c==-1) {
                    Drawer::sprites[name][i][j] = manager.CreateColorPair(-1, ColorManager::getColor(red, green, blue)) | ' ';
                }
                else {
                    Drawer::sprites[name][i][j] = manager.CreateColorPair(ColorManager::getColor(red, green, blue), -1) | c;
                }
            else Drawer::sprites[name][i][j] = 0;
        }
    }
}

std::vector<std::vector<unsigned int>> Drawer::getSprite(std::string name, int c) {
    if (Drawer::sprites.find(name) == Drawer::sprites.end()) {
        readSprite(name, c);
    }
    return sprites[name];
}
