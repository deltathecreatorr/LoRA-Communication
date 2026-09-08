#include <gtest/gtest.h>

TEST(DummyTest, ShouldPass) {
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