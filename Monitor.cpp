#include "Monitor.h"
#include "FieldEventDrawer.h"

Monitor::Monitor() : current_event("FieldEvent"), game() {
    FieldEventDrawer drawer;
    drawer.draw_field(game.get_data().get_field());
}

void Monitor::run() {
    while (game.get_status() == Game::RUNNING) {
        char last_pressed = get_last_pressed();
        if (current_event == "FieldEvent") {
            if (last_pressed == '\0') continue;
            current_event = game.on_event("FieldEvent", last_pressed);
        }
    }
}

char Monitor::get_last_pressed() {
    //TODO: implement
    return '\0';
}