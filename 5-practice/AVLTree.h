//
// Created by Letton on 28.10.2023.
//

#ifndef INC_4_PRACTICE_AVLTREE_H
#define INC_4_PRACTICE_AVLTREE_H

#include <iostream>
#include <algorithm>

class AVLTree {
public:
    class Node {
    public:
        int key_;
        std::string value_;
        Node *left_ = nullptr;
        Node *right_ = nullptr;
        int height_ = 0;

        Node(int key, std::string value);
    };

    static Node *Search(Node *node, int key);

    static Node *GetMin(Node *node);

    static Node *GetMax(Node *node);

    static int GetHeight(Node *node);

    static void UpdateHeight(Node *node);

    static int GetBalance(Node *node);

    static void Swap(Node *a, Node *b);

    static void Balance(Node *node);

    static void RightRotate(Node *node);

    static void LeftRotate(Node *node);

    static void Insert(Node *node, int key, std::string value);

    static Node *Delete(Node *node, int key);
};


#endif //INC_4_PRACTICE_AVLTREE_H
