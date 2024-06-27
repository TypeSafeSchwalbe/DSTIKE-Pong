
#pragma once

#include <SH1106Wire.h>

// Display type: SH1106 1.3" OLED display
// Resolution: 128 x 64 Pixel
// Pin definitions for I2C connected OLED display
#define OLED_SDA_PIN    D1  // pin 5
#define OLED_SCL_PIN    D2  // pin 4
#define OLED_ADDR       60  // 0x3C
#define OLED_WIDTH      128
#define OLED_CENTER_W   64
#define OLED_HEIGHT     64
#define OLED_CENTER_H   32

extern SH1106Wire OLED;

void init_display();
void render_state();
