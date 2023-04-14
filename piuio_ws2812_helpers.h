#ifndef PIUIO_PICO_PIUIO_WS2812_HELPERS_H
#define PIUIO_PICO_PIUIO_WS2812_HELPERS_H

#include <stdint.h>
#include "hardware/pio.h"

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

#define urgb_u32(r, g, b) ((uint32_t) (r) << 8) |   \
                          ((uint32_t) (g) << 16) |  \
                          (uint32_t) (b)

// Borrowed from https://github.com/speedypotato/Pico-Game-Controller
static inline uint32_t color_wheel(uint16_t wheel_pos) {
  wheel_pos %= 768;
  if (wheel_pos < 256) {
    return urgb_u32(wheel_pos, 255 - wheel_pos, 0);
  } else if (wheel_pos < 512) {
    wheel_pos -= 256;
    return urgb_u32(255 - wheel_pos, 0, wheel_pos);
  } else {
    wheel_pos -= 512;
    return urgb_u32(0, wheel_pos, 255 - wheel_pos);
  }
}

#endif //PIUIO_PICO_PIUIO_WS2812_HELPERS_H
