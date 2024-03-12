#include <iostream>
#include "Manager.h"
#include "Drawer.h"

int main() {
    Drawer::readAll();
    Manager manager;
    manager.start_game();

    return 0;
}