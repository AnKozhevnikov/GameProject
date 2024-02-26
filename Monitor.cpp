#include "Monitor.h"

Monitor::Monitor() : current_event("FieldEvent"), game() {}

void Monitor::run() {
    while (game.get_status() == Game::RUNNING) {
        if (current_event == "FieldEvent") {
            current_event = game.on_event("FieldEvent");
        } else if (current_event == "EmptyEvent") {
            current_event = game.on_event("EmptyEvent");
        }
    }
}