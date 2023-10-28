//
// Created by Letton on 28.10.2023.
//

#include "AVLTree.h"

#include <utility>

AVLTree::Node::Node(int key, std::string value) : key_(key), value_(std::move(value)), height_(0) {}

int AVLTree::GetHeight(AVLTree::Node *node) {
    return node == nullptr ? -1 : node->height_;
}

void AVLTree::UpdateHeight(AVLTree::Node *node) {
    node->height_ = std::max(GetHeight(node->left_), GetHeight(node->right_)) + 1;
}

int AVLTree::GetBalance(AVLTree::Node *node) {
    return (node == nullptr) ? 0 : GetHeight(node->right_) - GetHeight((node->left_));
}

void AVLTree::Swap(AVLTree::Node *a, AVLTree::Node *b) {
    int a_key = a->key_;
    a->key_ = b->key_;
    b->key_ = a_key;
    std::string a_value = a->value_;
    a->value_ = b->value_;
    b->value_ = a_value;
}

void AVLTree::RightRotate(AVLTree::Node *node) {
    Swap(node, node->left_);
    Node *buffer = node->right_;
    node->right_ = node->left_;
    node->left_ = node->right_->left_;
    node->right_->left_ = node->right_->right_;
    node->right_->right_ = buffer;
    UpdateHeight(node->right_);
    UpdateHeight(node);
}

void AVLTree::LeftRotate(AVLTree::Node *node) {
    Swap(node, node->right_);
    Node *buffer = node->left_;
    node->left_ = node->right_;
    node->right_ = node->left_->right_;
    node->right_->left_ = node->right_->right_;
    node->left_->right_ = node->left_->left_;
    node->left_->left_ = buffer;
    UpdateHeight(node->left_);
    UpdateHeight(node);

}
