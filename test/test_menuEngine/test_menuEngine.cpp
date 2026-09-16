#include <gtest/gtest.h>
#include "menuEngine.hpp"

class MockMenuAction : public IMenuAction {
    public:
        void execute() override { callCount++; }
        int callCount = 0;
};

// create test fixture that setups a tree with one child menuNode from root
class MenuEngineTest : public ::testing::Test {
    protected:
        MenuEngine* menuEngine;
        MockMenuAction mockAction1;
        MockMenuAction mockAction2;
        void SetUp() {
            MenuNode menuNode = MenuNode();
            MenuNode child1;
            MenuNode child2;
            child1.label = "Page 1";
            child1.action = &mockAction1;
            child2.label = "Page 2";
            child2.action = &mockAction2;
            menuNode.children = { child1, child2 };

            menuEngine = new MenuEngine(menuNode);
        }

        void TearDown() override {
            delete menuEngine;
        }
};

TEST_F(MenuEngineTest, CheckConstruction) {
    auto& top = menuEngine->nav_stack.back(); // .back() returns the last element of the vector
    // auto means compiler infers the type, & top is a reference to the pair inside the vector
    MenuNode current = (*top.first)[top.second];
    EXPECT_EQ(current.label, "Page 1");
};

TEST_F(MenuEngineTest, NextPage) {
    menuEngine->next();
    auto& bottom = menuEngine->nav_stack.back();

    MenuNode current = (*bottom.first)[bottom.second];
    EXPECT_EQ(current.label, "Page 2");
}

TEST_F(MenuEngineTest, PreviousPage) {
    menuEngine->next();
    auto& bottom = menuEngine->nav_stack.back();

    MenuNode current = (*bottom.first)[bottom.second];
    EXPECT_EQ(current.label, "Page 2");

    menuEngine->previous();
    auto& top = menuEngine->nav_stack.back();

    MenuNode current2 = (*top.first)[top.second];
    EXPECT_EQ(current2.label, "Page 1");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();

};