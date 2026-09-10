#include "rotaryEncoder.hpp"

Direction RotaryReader::getLastDirection() {
    Direction current = lastDirection;
    lastDirection = Direction::None;
    return current;
}

ButtonState RotaryReader::getLastButtonState() {
    ButtonState current = lastButtonState;
    lastButtonState = ButtonState::None;
    return current;
}

void RotaryReader::update(uint32_t currentTimeMs) {

    ButtonState state = getLastButtonState();
    if (state == ButtonState::Pressed) {
        uint32_t buttonPressStartTime = currentTimeMs;
        bool isTimingPress = true;
    }

}

// test functions

void RotaryReader::isr_pinA() {
    int stateB = gpio.gpio_get_level(pinB);

    if (stateB == 1) {
        lastDirection = Direction::CW;
    } else {
        lastDirection = Direction::CCW;
    }

}

void RotaryReader::isr_pinBtn() {
    int stateBtn = gpio.gpio_get_level(pinBtn);

    if (stateBtn == 1) {
        lastButtonState = ButtonState::Released;
    } else {
        lastButtonState = ButtonState::Pressed;
    }
}