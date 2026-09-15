#pragma once
#include <iostream>
#include <string>
#include <vector>

// The interface every page implements
struct IMenuAction {
    virtual ~IMenuAction() = default;
    virtual void execute() = 0;
};

// The tree of pages that we will navigate
struct MenuNode {
    std::string label;
    std::vector<MenuNode> children; // an array of leaf nodes for menus
    IMenuAction* action = nullptr; // 
};

// 
class MenuEngine {
    public:
        MenuNode root;
        std::vector<std::pair<std::vector<MenuNode>*, int>> nav_stack; // a stack of pairs (MenuNode pointer, int index)
        MenuEngine(const MenuNode& injectedRoot) { // constructor takes parameter of root node to create menu, doesnt create a copy
            root = injectedRoot;
            nav_stack.push_back({&root.children, 0});
        };
};
