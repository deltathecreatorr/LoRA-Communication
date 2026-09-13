#include <gtest/gtest.h>
#include "FakeGpio.hpp"
#include "rotaryEncoder.hpp"

// google test fixture, google test creates a new instance of this class before each test runs
class RotaryEncoderTest : public ::testing::Test {
    protected:
        FakeGpio fakeGpio;
        RotaryReader* reader;

        // executed immediately before each new test runs
        void SetUp() override {
            reader = new RotaryReader(fakeGpio, 43, 44, 6);

            fakeGpio.set_level(43, 1); // encoder pin A
            fakeGpio.set_level(44, 1); // encoder pin B
            fakeGpio.set_level(6, 1); // button pin S1
        }

        // executed immediately after each test runs
        void TearDown() override {
            delete reader;
        }
};


// Clockwise: Pin A connects to ground and drops to zero first, and then Pin B
// Counter Clockwise: Pin B connects to ground first and drops to zero, and then Pin A

// Functional Test Cases
TEST_F(RotaryEncoderTest, OneClockwise) {
    EXPECT_EQ(reader->getLastDirection(), Direction::None);
    fakeGpio.set_level(43, 0);
    reader->isr_pinA();
    EXPECT_EQ(reader->getLastDirection(), Direction::CW);
}

TEST_F(RotaryEncoderTest, OneCounterClockwise) {
    EXPECT_EQ(reader->getLastDirection(), Direction::None);
    fakeGpio.set_level(44, 0);
    reader->isr_pinA();
    EXPECT_EQ(reader->getLastDirection(), Direction::CCW);
}

TEST_F(RotaryEncoderTest, SecondRotationOverwritesFirstIfUnread) {
    fakeGpio.set_level(44, 0);
    reader->isr_pinA(); // sets CCW, not yet read

    fakeGpio.set_level(44, 1);
    fakeGpio.set_level(43, 0);
    reader->isr_pinA(); // fires again before anyone read the CCW

    EXPECT_EQ(reader->getLastDirection(), Direction::CW); // only the latest survives
}

// Edge Case / Stress Case

TEST_F(RotaryEncoderTest, ReadingDirectionTwiceReturnsNoneSecondTime) {
    fakeGpio.set_level(43, 0); // trigger pin A falling edge
    reader->isr_pinA();

    EXPECT_EQ(reader->getLastDirection(), Direction::CW); // or CCW

    EXPECT_EQ(reader->getLastDirection(), Direction::None); // consumed
}

// Button Test Cases

TEST_F(RotaryEncoderTest, NoPressReturnsNone) {
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
    fakeGpio.set_level(6, 1);
    reader->isr_pinBtn(0);
    reader->update(0);
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
}

TEST_F(RotaryEncoderTest, ButtonPress) {
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
    fakeGpio.set_level(6, 0);
    reader->isr_pinBtn(0);
    reader->update(0);
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
    fakeGpio.set_level(6, 1);
    reader->isr_pinBtn(30);
    reader->update(0);
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::Released);
}

TEST_F(RotaryEncoderTest, ButtonLongPress) {
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
    fakeGpio.set_level(6, 0);
    reader->isr_pinBtn(0);
    reader->update(900);
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
    fakeGpio.set_level(6, 1);
    reader->isr_pinBtn(900);
    reader->update(0);
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::LongPressed);
}

TEST_F(RotaryEncoderTest, ButtonDebounce) {
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
    fakeGpio.set_level(6, 0);
    reader->isr_pinBtn(0);
    reader->update(0);
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
    fakeGpio.set_level(6, 1);
    reader->isr_pinBtn(10);
    reader->update(0);
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
}

TEST_F(RotaryEncoderTest, SimultaneousButtonPressRotation) {
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
    EXPECT_EQ(reader->getLastDirection(), Direction::None);
    fakeGpio.set_level(43, 0);
    fakeGpio.set_level(6, 0);
    reader->isr_pinBtn(0);
    reader->update(0);
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::None);
    fakeGpio.set_level(6, 1);
    reader->isr_pinA();
    reader->isr_pinBtn(30);
    reader->update(0);
    EXPECT_EQ(reader->getLastDirection(), Direction::CW);
    EXPECT_EQ(reader->getLastButtonState(), ButtonState::Released);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}



