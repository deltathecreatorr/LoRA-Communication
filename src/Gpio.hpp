// src/Gpio.hpp
#pragma once
#include "IGpio.hpp"
#include "driver/gpio.h"

class Gpio : public IGpio {
public:
    void pinMode(uint8_t pin, uint8_t mode) override {
        gpio_config_t io_conf = {};
        io_conf.pin_bit_mask = (1ULL << pin);
        io_conf.mode = (mode == INPUT_PULLUP) ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT;
        io_conf.pull_up_en = (mode == INPUT_PULLUP) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
        gpio_config(&io_conf);
    }

    int digitalRead(uint8_t pin) override {
        return gpio_get_level((gpio_num_t)pin);  
    }
};