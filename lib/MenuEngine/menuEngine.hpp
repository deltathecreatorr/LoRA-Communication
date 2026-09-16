#pragma once
#include <iostream>
#include <string>
#include <vector>

// The interface every page implements
struct IMenuAction {
    virtual ~IMenuAction() = default; // virtual deconstructor
    virtual void execute() = 0; // will not do anything unless injectedroot can execute a pages action
};

// The tree of pages that we will navigate
struct MenuNode {
    std::string label;
    std::vector<MenuNode> children; // an array of leaf MenuNodes for menus
    IMenuAction* action = nullptr; // a pointer to connect a MenuNode to actual behaviour for a page
};

// class that allows for the navigation in the tree
class MenuEngine {
    public:
        MenuNode root;
        std::vector<std::pair<std::vector<MenuNode>*, int>> nav_stack; // a stack of pairs (MenuNode pointer, int index)
        MenuEngine(const MenuNode& injectedRoot) { // constructor takes parameter of root node to create menu, doesnt create a copy from memory due to const
            root = injectedRoot;
            nav_stack.push_back({&root.children, 0}); // push/pop through the stack to navigate through menus.
        };
};
