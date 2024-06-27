
#include <Arduino.h>
#include <Wire.h>
#include "render.h"
#include "state.h"

SH1106Wire OLED = SH1106Wire(OLED_ADDR, OLED_SDA_PIN, OLED_SCL_PIN);

void init_display() {
    Serial.print("Initializing display... ");
    OLED.init();
    OLED.flipScreenVertically();
    OLED.setFont(ArialMT_Plain_10);
    OLED.setTextAlignment(TEXT_ALIGN_LEFT);
    OLED.displayOn();
    OLED.clear();
    OLED.display();
    Serial.println("done!");
}


static void render_paddle(Paddle* paddle) {
    OLED.fillRect(
        (int16_t) paddle->posX, (int16_t) paddle->posY,
        GAME_PADDLE_WIDTH, GAME_PADDLE_HEIGHT
    );
}

static void render_ball(Ball* ball) {
    OLED.fillRect(
        (int16_t) ball->posX, (int16_t) ball->posY, 
        GAME_BALL_SIZE, GAME_BALL_SIZE
    );
}

static void render_score(unsigned int score) {
    // u32 can only hold 10 digits max, so 128 bytes is enough :)
    char score_buffer[128];
    OLED.drawStringf(5, 5, score_buffer, "%u", score);
}

void render_state() {
    OLED.clear();
    render_paddle(&STATE.paddle);
    render_ball(&STATE.ball);
    render_score(STATE.score);
    OLED.display();
}