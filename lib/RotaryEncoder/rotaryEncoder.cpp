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
    if (buttonHeld && !wasButtonHeld) {
        pressStartTime = currentTimeMs;
        lastButtonState = ButtonState::None;
    } else if (!buttonHeld && wasButtonHeld) {
        uint32_t heldDuration = currentTimeMs - pressStartTime;
        if (heldDuration >= LongPressThresholdMs) {
            lastButtonState = ButtonState::LongPressed;
        } else {
            lastButtonState = ButtonState::Released;
        }
    } else {
        lastButtonState = ButtonState::None;
    }
    wasButtonHeld = buttonHeld;
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
    buttonHeld = (stateBtn == 0);
}