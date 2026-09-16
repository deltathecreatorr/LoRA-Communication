#include <gtest/gtest.h>
#include "menuEngine.hpp"

class MockMenuAction : public IMenuAction {
    public:
        void execute() override { callCount++; }
        int callCount = 0;
};

class MenuEngineTest : public ::testing::Test {
    protected:
        MenuEngine* menuEngine;
        MockMenuAction mockAction;
        void SetUp() {
            MenuNode menuNode = MenuNode();
            MenuNode child;
            child.label = "Page 1";
            child.action = &mockAction;
            menuNode.children = { child };
            menuEngine = new MenuEngine(menuNode);
        }

        void TearDown() override {
            delete menuEngine;
        }
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();

};