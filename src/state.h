
#pragma once

#define BUTTON_UP_PIN     12
#define BUTTON_DOWN_PIN   13
#define BUTTON_PUSH_PIN   14

#define GAME_FPS               30
#define GAME_FRAME_DELTA_MS    (1000 / GAME_FPS)
#define GAME_BALL_SPEED_INCR   2.5
#define GAME_BALL_SIZE         2
#define GAME_PADDLE_WIDTH      2
#define GAME_PADDLE_HEIGHT     (OLED_HEIGHT / 4)
#define GAME_PADDLE_SPEED      30.0

typedef struct {
    bool up;
    bool down;
} Controls;

typedef struct {
    float posX;
    float posY;
    float velX;
    float velY;
    float speed;
} Ball;

typedef struct {
    float posX;
    float posY;
} Paddle;

typedef struct {
    Ball ball;
    Paddle paddle;
    unsigned int score;
} Gamestate;

extern Controls CONTROLS;
extern Gamestate STATE;

void init_controls();
void reset_state();
void update_state();