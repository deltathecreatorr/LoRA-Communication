#ifndef HIGH
#define HIGH 1
#define LOW  0
#endif

#pragma once
#include "IGpio.hpp"
#include <map>

class FakeGpio : public IGpio {
    public:
        void setPinState(uint8_t pin, int value) {
            pinStates[pin] = value;
        }

        int digitalRead(uint8_t pin) override {
            return pinStates[pin];
        }

        void pinMode(uint8_t pin, uint8_t mode) override {
            (void)pin;
            (void)mode;
        }
    private:
        std::map<uint8_t, int> pinStates;
};