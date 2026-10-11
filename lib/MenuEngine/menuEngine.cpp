#include "menuEngine.hpp"

// the pair in the stack consists of, (std::vector<MenuNode>, int index)
// the MenuNode, consists of (std::string, std::vector<MenuNode> children)
// label must be set, but children can be zero if there are no submenus for the item

void MenuEngine::next() {
    auto& top = nav_stack.back();
    // only increment if aren't already at last item
    if (top.second + 1 < top.first->size()) {
        top.second++;
    } //goes to the second last member of the stack and increments by one to go to the next menu.
};

void MenuEngine::previous() {
    auto& top = nav_stack.back();
    // only decrement if above first item (index 0)
    if (top.second > 0) {
        top.second--;
    } //goes to the second last member of the stack and decrements by one to go the previous menu.
};

void MenuEngine::select() {
    auto& top = nav_stack.back(); //get the top member of the stack
    MenuNode& current = (*top.first)[top.second]; // get the label and MenuNode object

    if (!current.children.empty()) { // if the current MenuNode has children
        nav_stack.push_back({&current.children, 0}); // push all of the child nodes of the current MenuNode into the stack.
    } else if (current.action) { // check if the child node has an associated action
        current.action->execute(); //execute the childs action
    }
};

void MenuEngine::back_page() {
    if (nav_stack.size() > 1) {
        nav_stack.pop_back();
    }
};