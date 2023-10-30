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

void AVLTree::Balance(AVLTree::Node *node) {
    int balance = GetBalance(node);
    if (balance == -2) {
        if (GetBalance(node->left_) == 1) LeftRotate(node->left_);
        RightRotate(node);
    } else if (balance == 2) {
        if (GetBalance(node->right_) == -1) RightRotate(node->right_);
        LeftRotate(node);
    }

}

void AVLTree::Insert(AVLTree::Node *node, int key, std::string value) {
    if (key < node->key_) {
        if (node->left_ == nullptr) node->left_ = new Node(key, std::move(value));
        else Insert(node->left_, key, value);
    } else if (key >= node->key_) {
        if (node->right_ == nullptr) node->right_ = new Node(key, std::move(value));
        else Insert(node->right_, key, value);
    }
    UpdateHeight(node);
    Balance(node);
}

AVLTree::Node *AVLTree::Delete(AVLTree::Node *node, int key) {
    if (node == nullptr) return nullptr;
    else if (key < node->key_) node->left_ = Delete(node->left_, key);
    else if (key > node->key_) node->right_ = Delete(node->right_, key);
    else {
        if (node->left_ == nullptr || node->right_ == nullptr) {
            node = (node->left_ == nullptr) ? node->right_ : node->left_;
        } else {
            Node *max_ln_left = GetMax(node->left_);
            node->key_ = max_ln_left->key_;
            node->value_ = max_ln_left->value_;
            node->right_ = Delete(node->right_, max_ln_left->key_);
        }
    }
    if (node != nullptr) {
        UpdateHeight(node);
        Balance(node);
    }
}

AVLTree::Node *AVLTree::Search(AVLTree::Node *node, int key) {
    if (node == nullptr) return nullptr;
    if (node->key_ == key) return node;
    return (key < node->key_) ? Search(node->left_, key) : Search(node->right_, key);
}

AVLTree::Node *AVLTree::GetMin(AVLTree::Node *node) {
    if (node == nullptr) return nullptr;
    if (node->left_ == nullptr) return node;
    return GetMin(node->left_);
}

AVLTree::Node *AVLTree::GetMax(AVLTree::Node *node) {
    if (node == nullptr) return nullptr;
    if (node->right_ == nullptr) return node;
    return GetMax(node->right_);
}
