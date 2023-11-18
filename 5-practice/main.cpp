#include <Windows.h>
#include "AVLTree.h"

void show(AVLTree::Node *node) {
    std::cout << node->value_ << " ";
}


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    bool flag = false;
    AVLTree::Node *root = nullptr;
    while (true) {
        std::cout << "Choose action:\n"
                     "1 - Insert element\n"
                     "2 - Simetrical Traversal\n"
                     "3 - Depth First Traversal\n"
                     "4 - Sum of leaf values\n"
                     "5 - Show tree height\n"
                     "6 - Exit\n";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                if (!flag) {
                    std::cout << "Input node data: key, value\n";
                    int key;
                    std::string value;
                    std::cin >> key >> value;
                    root = new AVLTree::Node(key, value);
                    flag = true;
                } else {
                    std::cout << "Input node data: key, value\n";
                    int key;
                    std::string value;
                    std::cin >> key >> value;
                    AVLTree::Insert(root, key, value);
                }
                break;
            }
            case 2: {
                AVLTree::SimetricalTraversal(root, show);
                std::cout << "\n";
                break;
            }
            case 3: {
                AVLTree::DepthFirstTraversal(root, show);
                std::cout << "\n";
                break;
            }
            case 4: {
                std::cout << "Concatenated value of all leaves: " << AVLTree::SumOfLeafValues(root) << "\n";
                break;
            }
            case 5: {
                std::cout << "Tree height\n";
                std::cout << AVLTree::GetHeight(root) << "\n";
                break;
            }
            case 6: {
                return 0;
            }
            default:
                std::cout << "Incorrect choose. Try again.\n";
                break;
        }
    }
}