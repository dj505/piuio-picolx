
#include "piuio_config.h"

#ifdef ENABLE_WS2812_SUPPORT
#include "piuio_ws2812.h"
#include "piuio_ws2812_helpers.h"

#include "ws2812.pio.h"
#include "pico/multicore.h"

mutex_t mutex;
semaphore_t sem;

static struct lampArray* lamp;

void ws2812_update(uint32_t counter) {
  // Write lamp.data to WS2812Bs
  put_pixel(lamp->bass_light ? ws2812_color[2] : urgb_u32(0, 0, 0));   // Top middle
  put_pixel(lamp->l1_halo ? ws2812_color[1] : urgb_u32(0, 0, 0));      // Top left
  put_pixel(lamp->l2_halo ? ws2812_color[0] : urgb_u32(0, 0, 0));      // Bottom left
  put_pixel(lamp->bass_light ? ws2812_color[3] : urgb_u32(0, 0, 0));   // Bottom middle
  put_pixel(lamp->r2_halo ? ws2812_color[0] : urgb_u32(0, 0, 0));      // Bottom right
  put_pixel(lamp->r1_halo ? ws2812_color[1] : urgb_u32(0, 0, 0));      // Top right
  put_pixel(lamp->p2_ur_light ? ws2812_color[14] : urgb_u32(0, 0, 0)); // P2 UR
  put_pixel(lamp->p2_dr_light ? ws2812_color[15] : urgb_u32(0, 0, 0)); // P2 DR
  put_pixel(lamp->p2_cn_light ? ws2812_color[13] : urgb_u32(0, 0, 0)); // P2 CN
  put_pixel(lamp->p2_dl_light ? ws2812_color[11] : urgb_u32(0, 0, 0)); // P2 DL
  put_pixel(lamp->p2_ul_light ? ws2812_color[12] : urgb_u32(0, 0, 0)); // P2 UL
  put_pixel(lamp->p1_ur_light ? ws2812_color[9] : urgb_u32(0, 0, 0));  // P1 UR
  put_pixel(lamp->p1_dr_light ? ws2812_color[10] : urgb_u32(0, 0, 0)); // P1 DR
  put_pixel(lamp->p1_cn_light ? ws2812_color[8] : urgb_u32(0, 0, 0));  // P1 CN
  put_pixel(lamp->p1_dl_light ? ws2812_color[6] : urgb_u32(0, 0, 0));  // P1 DL
  put_pixel(lamp->p1_ul_light ? ws2812_color[7] : urgb_u32(0, 0, 0));  // P1 UL

  for (int i = 0; i < 3; ++i) {
    put_pixel(color_wheel((counter + i * (int)(768 / 10)) % 768));
  }

  // put_pixel(lamp->bass_light ? ws2812_color[16] : urgb_u32(0, 0, 0));  // Logo 1
  // put_pixel(lamp->bass_light ? ws2812_color[17] : urgb_u32(0, 0, 0));  // Logo 2
  // put_pixel(lamp->bass_light ? ws2812_color[18] : urgb_u32(0, 0, 0));  // Logo 3
}

void ws2812_core1() {
    uint32_t counter = 0;
    while (true) {
        ws2812_lock_mtx();
        ws2812_update(++counter);
        ws2812_unlock_mtx();
        sleep_ms(5);
    }
}

void ws2812_lock_mtx() {
    uint32_t owner = 0;

    sem_release(&sem);
    if (!mutex_try_enter(&mutex, &owner)) {
        mutex_enter_blocking(&mutex);
    }
}

void ws2812_unlock_mtx() {
    mutex_exit(&mutex);
}

void ws2812_init(struct lampArray* l) {
    mutex_init(&mutex);
    sem_init(&sem, 0, 2);
    lamp = l;

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, WS2812_IS_RGBW);

    multicore_launch_core1(ws2812_core1);
}
#endif
