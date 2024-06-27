
#include "state.h"
#include "render.h"
#include <cmath>

Controls CONTROLS;
Gamestate STATE;

void init_controls() {
    pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
    pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
    CONTROLS = (Controls) {
        .up = false,
        .down = false
    };
}

void reset_state() {
    STATE = (Gamestate) {
        .ball = (Ball) {
            .posX = 0.0, .posY = 0.0,
            .velX = 1.0, .velY = 1.0,
            .speed = 25.0
        },
        .paddle = (Paddle) {
            .posX = 3.0,
            .posY = (OLED_HEIGHT - GAME_PADDLE_HEIGHT) / 2.0
        },
        .score = 0
    };
}


static bool paddle_collision(Ball* ball, Paddle* paddle) {
    return paddle->posX <= ball->posX + GAME_BALL_SIZE
        && ball->posX   <= paddle->posX + GAME_PADDLE_WIDTH
        && paddle->posY <= ball->posY + GAME_BALL_SIZE
        && ball->posY   <= paddle->posY + GAME_PADDLE_HEIGHT;
}



static void update_controls() {
    CONTROLS.up   = digitalRead(BUTTON_UP_PIN);
    CONTROLS.down = digitalRead(BUTTON_DOWN_PIN);
}

static void move_ball(Ball* ball) {
    float velL = sqrtf(powf(ball->velX, 2.0) + powf(ball->velY, 2.0));
    float velM = ball->speed / velL / GAME_FPS;
    ball->posX += ball->velX * velM;
    ball->posY += ball->velY * velM;
}

static void reflect_ball(Ball* ball, Paddle* paddle, unsigned int* score) {
    if(paddle_collision(ball, paddle)) {
        float rel_pos = ball->posY - GAME_BALL_SIZE - paddle->posY;
        float angle_deg = ((rel_pos * 2.0 / GAME_PADDLE_HEIGHT) - 1.0) * 60.0;
        float angle_rad = angle_deg * 6.28 / 360;
        ball->velX = cosf(angle_rad);
        ball->velY = sinf(angle_rad);
        ball->speed += GAME_BALL_SPEED_INCR;
        *score += 1;
    }
    if(ball->posX + GAME_BALL_SIZE >= OLED_WIDTH) {
        ball->velX *= -1.0;
    }
    if(ball->posY <= 0 || ball->posY + GAME_BALL_SIZE >= OLED_HEIGHT) {
        ball->velY *= -1.0;
    }
}

static bool end_game(Ball* ball) {
    bool ended = ball->posX <= 0.0;
    if(ended) {
        reset_state();
    }
    return ended;
}

static void move_paddle(Paddle* paddle, Controls* controls) {
    if(controls->down) {
        paddle->posY = fmax(paddle->posY - GAME_PADDLE_SPEED / GAME_FPS, 0.0);
    }
    if(controls->up) {
        paddle->posY = fmin(
            paddle->posY + GAME_PADDLE_SPEED / GAME_FPS, 
            (float) OLED_HEIGHT - GAME_PADDLE_HEIGHT
        );
    }
}

void update_state() {
    update_controls();
    move_ball(&STATE.ball);
    reflect_ball(&STATE.ball, &STATE.paddle, &STATE.score);
    if(end_game(&STATE.ball)) { return; }
    move_paddle(&STATE.paddle, &CONTROLS);
}