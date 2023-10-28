//
// Created by Letton on 28.10.2023.
//

#ifndef INC_4_PRACTICE_AVLTREE_H
#define INC_4_PRACTICE_AVLTREE_H

#include <iostream>
#include <algorithm>

class AVLTree {

    class Node {
    public:
        int key_;
        std::string value_;
        Node *left_ = nullptr;
        Node *right_ = nullptr;
        int height_ = 0;

        Node(int key, std::string value);
    };

    static int GetHeight(Node *node);

    static void UpdateHeight(Node *node);

    static int GetBalance(Node *node);

    static void Swap(Node *a, Node *b);


    void RightRotate(Node *node);

    void LeftRotate(Node *node);

};


#endif //INC_4_PRACTICE_AVLTREE_H
