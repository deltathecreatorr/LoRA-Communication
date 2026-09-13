#pragma once
#include <cstdint>
#include "IGpio.hpp"

enum class Direction {
    None,
    CW,
    CCW
};

enum class ButtonState {
    None,
    Released,
    LongPressed
};


class RotaryReader {
    public:
        RotaryReader(IGpio& gpio, gpio_num_t pinA, gpio_num_t pinB, gpio_num_t pinBtn)
            : gpio(gpio), pinA(pinA), pinB(pinB), pinBtn(pinBtn) {
                
            }
        
        void update(uint32_t currentTimeMs);

        Direction getLastDirection();

        ButtonState getLastButtonState();

        void isr_pinA();

        void isr_pinBtn(uint32_t currentTimeMs);

    private:
        IGpio& gpio;
        gpio_num_t pinA, pinB, pinBtn;

        Direction lastDirection = Direction::None;
        ButtonState lastButtonState = ButtonState::None;

        bool wasButtonHeld = false;
        bool buttonHeld = false;
        uint32_t pressStartTime = 0;
        static constexpr uint32_t LongPressThresholdMs = 800;
        static constexpr uint32_t DebounceWindowMs = 30;
        uint32_t lastDebounceTimeMs = 0;
        bool hasAcceptedFirstReading = false;
};

