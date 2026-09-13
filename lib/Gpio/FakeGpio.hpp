#ifndef HIGH
#define HIGH 1
#define LOW  0
#endif

#pragma once
#include "IGpio.hpp"
#include <map>

class FakeGpio : public IGpio {
    public:
    void set_level(gpio_num_t gpio_num, int level) {
        pinStates[gpio_num] = level;
    }

    int gpio_get_level(gpio_num_t gpio_num) override {
        return pinStates[gpio_num]; 
    }

    void gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode) override {
        (void)gpio_num;
        (void)mode;
    }
    private:
        std::map<gpio_num_t, int> pinStates;
};