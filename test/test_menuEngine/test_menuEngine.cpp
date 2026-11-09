#include <gtest/gtest.h>
#include "menuEngine.hpp"

class MockMenuAction : public IMenuAction {
    public:
        void execute() override { callCount++; }
        int callCount = 0;
};

// create test fixture that setups a tree with three children menuNode from root
class MenuEngineTest : public ::testing::Test {
    protected:
        MenuEngine* menuEngine;
        MockMenuAction mockAction1;
        MockMenuAction mockAction2;
        void SetUp() {
            MenuNode menuNode = MenuNode();
            MenuNode child1;
            MenuNode child2;
            MenuNode child3;
            MenuNode grandchild1;
            MenuNode grandchild2;
            child1.label = "Page 1";
            child2.label = "Page 2";

            grandchild1.label = "grandchild1";
            grandchild1.action = &mockAction1;
            child1.children = { grandchild1 };

            grandchild2.label = "grandchild2";
            grandchild2.action = &mockAction2;
            child2.children = { grandchild2 };

            child3.label = "Page 3";

            menuNode.children = { child1, child2, child3 };


            menuEngine = new MenuEngine(menuNode);
        }

        void TearDown() override {
            delete menuEngine;
        }
};

TEST_F(MenuEngineTest, CheckConstruction) {
    auto& top = menuEngine->nav_stack.back(); // .back() returns the last element of the vector
    // auto means compiler infers the type, & top is a reference to the pair inside the vector
    MenuNode& current = (*top.first)[top.second];
    EXPECT_EQ(current.label, "Page 1");
};

TEST_F(MenuEngineTest, NextPage) {
    menuEngine->next();
    auto& top = menuEngine->nav_stack.back();

    MenuNode& current = (*top.first)[top.second];
    EXPECT_EQ(current.label, "Page 2");
};

TEST_F(MenuEngineTest, PreviousPage) {
    menuEngine->next();
    auto& top = menuEngine->nav_stack.back();

    MenuNode& current = (*top.first)[top.second];
    EXPECT_EQ(current.label, "Page 2");

    menuEngine->previous();
    auto& bottom = menuEngine->nav_stack.back();

    MenuNode& current2 = (*bottom.first)[bottom.second];
    EXPECT_EQ(current2.label, "Page 1");
}

TEST_F(MenuEngineTest, EnterSubmenu) {
    menuEngine->select(); 
    auto& top = menuEngine->nav_stack.back();
    MenuNode& current = (*top.first)[top.second];  
    EXPECT_EQ(current.label, "grandchild1");
}

TEST_F(MenuEngineTest, ExitSubmenu) {
    menuEngine->next();
    menuEngine->select();
    EXPECT_EQ(menuEngine->nav_stack.size(), 2u);
    menuEngine->back_page(); 

    auto& top = menuEngine->nav_stack.back();
    MenuNode& current = (*top.first)[top.second];  
    EXPECT_EQ(current.label, "Page 2");
}

TEST_F(MenuEngineTest, mockActionTest) {
    menuEngine->select(); // goes to grandchild1
    menuEngine->select();
    
    EXPECT_EQ(mockAction1.callCount, 1);

    // navigate to page 2 from grandchild1
    menuEngine->back_page();
    menuEngine->next();
    menuEngine->select();
    menuEngine->select();
    EXPECT_EQ(mockAction1.callCount, 1);
    EXPECT_EQ(mockAction2.callCount, 1); // mockAction2 is a protected member variable and can be directly accessed.
}

TEST_F(MenuEngineTest, nullActionTest) {
    menuEngine->next();
    menuEngine->next();

    menuEngine->select();
    EXPECT_EQ(menuEngine->nav_stack.size(), 1u);
    auto& top = menuEngine->nav_stack.back();
    MenuNode& current = (*top.first)[top.second];  
    EXPECT_EQ(current.label, "Page 3");
    EXPECT_EQ(mockAction1.callCount, 0);
    EXPECT_EQ(mockAction2.callCount, 0);
}

TEST_F(MenuEngineTest, RootProtection) {
    menuEngine->back_page();
    EXPECT_EQ(menuEngine->nav_stack.size(), 1u);
    auto& top = menuEngine->nav_stack.back();
    MenuNode& current = (*top.first)[top.second];  
    EXPECT_EQ(current.label, "Page 1");
}

TEST_F(MenuEngineTest, PreviousProtection) {
    menuEngine->previous(); // cant move backwards from page 1 in list
    auto& top = menuEngine->nav_stack.back();
    MenuNode& current = (*top.first)[top.second];  
    EXPECT_EQ(current.label, "Page 1");

}

TEST_F(MenuEngineTest, NextProtection) {
    menuEngine->next();
    menuEngine->next();
    menuEngine->next();
    auto& top = menuEngine->nav_stack.back();
    MenuNode& current = (*top.first)[top.second];  
    EXPECT_EQ(current.label, "Page 3");

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();

}