# Menu Engine

Here is how the menu engine works as it is made of a tree and stack based navigation model.

## MenuNode

```
struct MenuNode{};
```
This represents a single item or page in the menu. Each node contains a label (what the page is supposed to display), and an optional action pointer that triggers behaviour when selected.

## IMenuAction

```
struct IMenuAction{};
```

This is an interface that allows you to attach executable code to a leaf node. When a user selects a final menu option, it will trigger this action.

## MenuEngine

```
class MenuEngine{};
```

This engine keeps track of where the user currently is using the navigation stack. Instead of storing large copies of the entire menu tree, the stack stores pairs consisting of

- A pointer to the vector of MenuNode items
- An integer index representing the currently highlighted item within that vector

# Functions

## Next

```
void MenuEngine::next(){};
```

Accesses the top of the navigation stack and increments the index. This moves the selection down or to the next item in the current menu list.

## Previous

```
void MenuEngine::previous() {};
```

Accesses the top of the stack and decrements the index. This moves the selection down or to the next item in the current menu list.

## Select

```
void MenuEngine::select() {};
```

Identifies the currently highlighted MenuNode using the active vector pointer and index
- If the node has children, it pushes the new pair onto the stack pointing to those children.
- If the node has no children but has an assigned action, it will execute that action

## Back Page

```
void MenuEngine::back_page(){};
```

Checks if the stack size is greater than 1, and removes the top item from nav_stack, returning the user to the previous menu level.

previous() and back_page() sound similar, but previous goes backwards in the stack, while back_page() moves up the tree node