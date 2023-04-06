#ifndef PIUIO_PICO_PIUIO_CONFIG_H
#define PIUIO_PICO_PIUIO_CONFIG_H
#include "piuio_ws2812_helpers.h"

// Uncomment these defines to enable WS2812 LED support.
#define ENABLE_WS2812_SUPPORT
#define WS2812_IS_RGBW false
#define WS2812_PIN 21

// Modify these to edit the colors of the cabinet lamps.
static uint32_t ws2812_color[5] = {
        urgb_u32(0, 255, 0),    // Lower left / Green
        urgb_u32(255, 0, 0),    // Upper left / Red
        urgb_u32(0, 0, 255),    // Bass / neon / Blue
        urgb_u32(255, 255, 0)   // Center Panel / Yellow
};

// Modify these arrays to edit the pin out.
// Map these according to your button pins.
static const uint8_t pinSwitch[12] = {
        19,     // P1 DL
        24,     // P1 UL
        23,     // P1 CN
        22,     // P1 UR
        18,     // P1 DR
        2,      // P2 DL
        4,      // P2 UL
        3,      // P2 CN
        0,      // P2 UR
        1,      // P2 DR
        12,    // Service
        13     // Test
};

#endif //PIUIO_PICO_PIUIO_CONFIG_H
