#include "Monitor.h"

Monitor::Monitor() : game() {
}

void Monitor::start_game() {
    game.run();
}