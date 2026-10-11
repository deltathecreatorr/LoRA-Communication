#include "LGFX_Config.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static LGFX tft;

extern "C" void app_main() {
    tft.init();
    tft.setBrightness(255);
    tft.setRotation(1);              // landscape, 480x320
    tft.fillScreen(TFT_BLACK);

    // Test 1: plain text straight to the screen
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.drawString("bello papoi", 20, 20);

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}