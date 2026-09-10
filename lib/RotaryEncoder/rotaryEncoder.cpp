#include "rotaryEncoder.hpp"

Direction RotaryReader::getLastDirection() const {
    return lastDirection;
}

ButtonState RotaryReader::getLastButtonState() const {
    return lastButtonState;
}

void RotaryReader::update() {

}