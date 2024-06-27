
#include <Arduino.h>
#include "state.h"
#include "render.h"

void setup() {
    Serial.begin(115200);
    Serial.flush();
    init_display();
    init_controls();
    reset_state();
    Serial.println("Initialization complete!");
}

void loop() {
    update_state();
    render_state();
    delay(GAME_FRAME_DELTA_MS);
}