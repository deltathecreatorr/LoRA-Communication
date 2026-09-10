#pragma once
#include <cstdint>

class IGpio {
    public:
        virtual ~IGpio() = default;

        virtual int digitalRead(uint8_t pin) = 0;
        virtual void pinMode(uint8_t pin, uint8_t mode) = 0;
};