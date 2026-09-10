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
    Click,
    LongPress
};


class RotaryReader {
    public:
        RotaryReader(IGpio& gpio, uint8_t pinA, uint8_t pinB, uint8_t pinBtn)
            : gpio(gpio), pinA(pinA), pinB(pinB), pinBtn(pinBtn) {
                
            }
        
        void update();

        Direction getLastDirection() const;

        ButtonState getLastButtonState() const;

    private:
        IGpio& gpio;
        uint8_t pinA, pinB, pinBtn;

        Direction lastDirection = Direction::None;
        ButtonState lastButtonState = ButtonState::None;

};

