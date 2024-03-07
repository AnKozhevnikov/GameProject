#include "Manager.h"
#include "Display.h"

Manager::Manager() : display(), game(&display) {
}

void Manager::start_game() {
    game.run();
}