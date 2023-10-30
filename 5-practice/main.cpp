#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>
#include "AVLTree.h"


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    auto *root = new AVLTree::Node(1, "hello");
    AVLTree::Insert(root, 2, "2");
    AVLTree::Insert(root, 3, "3");
    std::cout << "done";
    return 0;
}