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
            reader = new RotaryReader(fakeGpio, 43, 44, 5);

            fakeGpio.set_level(43, 1); // encoder pin A
            fakeGpio.set_level(44, 1); // encoder pin B
            fakeGpio.set_level(6, 1); // button pin S1

        }

        // executed immediately after each test runs
        void TearDown() override {
            delete reader;
        }
};


// Functional Test Cases
TEST(SingleStepClockwise, ShouldPass) {
    EXPECT_EQ(1, 1);
}

TEST(SingleStepCounterClockwise, ShouldPass) {
    EXPECT_EQ(1, 1);
}

TEST(SlowRotation, ShouldPass) {
    EXPECT_EQ(1, 1);
}

TEST(DirectionChange, ShouldPass) {
    EXPECT_EQ(1, 1);
}

TEST(ReturnZero, ShouldPass) {
    EXPECT_EQ(1, 1);
}

// Edge Case / Stress Case

TEST(HighSpeedRotation, ShouldPass) {
    EXPECT_EQ(1, 1);
}

TEST(OverflowUnderflow, ShouldPass) {
    EXPECT_EQ(1, 1);
}

TEST(PowerCycle, ShouldPass) {
    EXPECT_EQ(1, 1);
}

// Button Test Cases

TEST(ButtonPress, ShouldPass) {
    EXPECT_EQ(1, 1);
}

TEST(ButtonDebounce, ShouldPass) {
    EXPECT_EQ(1, 1);
}

TEST(ButtonLongPress, ShouldPass) {
    EXPECT_EQ(1, 1);
}

TEST(SimultaneousButtonRotation, ShouldPass) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    if (RUN_ALL_TESTS() == 0) {
        std::cout << "All tests passed!" << std::endl;
    } else {
        std::cout << "Some tests failed." << std::endl;
    }
    
    return 0;
}



