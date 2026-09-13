#pragma once
#include <driver/gpio.h>

class IGpio {
    public:
        virtual ~IGpio() = default;

        virtual int gpio_get_level(gpio_num_t gpio_num) = 0;
        virtual void gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode) = 0;
};