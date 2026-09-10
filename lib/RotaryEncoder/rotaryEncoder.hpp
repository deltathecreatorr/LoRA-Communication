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
    Pressed,
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

        void isr_pinBtn();

    private:
        IGpio& gpio;
        gpio_num_t pinA, pinB, pinBtn;

        Direction lastDirection = Direction::None;
        ButtonState lastButtonState = ButtonState::None;
        uint32_t buttonPressStartTime = 0;
        bool isTimingPress = false;
        bool longPressHandled = false;
};

