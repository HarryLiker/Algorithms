#pragma once

#include "functions.hpp"

template <class TKey, class TValue>
struct Node {
    TKey Key;
    TValue Value;
    Node *Right;
    Node *Left;
    Node *Parent;
    unsigned int Height; // Высота поддерева
    Node(): Key(), Value(), Right(), Left(), Parent(), Height(1) {}

    Node(TKey key, TValue value): Key(key), Value(value), Right(nullptr), Left(nullptr), Parent(nullptr), Height(1) {}

    unsigned int FindHeight(Node<TKey, TValue> *node) {
        if (node) {
            return node->Height;
        } else {
            return 0;
        }
    }
    
    int HeightDifference(Node<TKey, TValue>* node) {
        return FindHeight(node->Left) - FindHeight(node->Right);
    }

    void OverHeight (Node<TKey, TValue> *node) {
        int height_left = FindHeight(node->Left);
        int height_right = FindHeight(node->Right);
        node->Height = (height_left > height_right ? height_left : height_right) + 1;
    }

    ~Node() {}
};

template <class TKey, class TValue>
class AVLTree {
private:
    Node<TKey, TValue> *Root;
public:
    AVLTree(): Root(nullptr) {}

    Node<TKey, TValue> *Search(TKey key) {
        Node<TKey, TValue> *current_node = Root;
        while (current_node != nullptr && key != current_node->Key) {
            if (key < current_node->Key) {
                current_node = current_node->Left;
            }
            else {
                current_node = current_node->Right;
            }
        }
        return current_node;
    }

    void RightRotation(Node<TKey, TValue> *rotation_node) {
        Node<TKey, TValue> *left_node = rotation_node->Left;
        rotation_node->Left = left_node->Right;
        if (left_node->Right != nullptr) {
            left_node->Right->Parent = rotation_node;
        }
        left_node->Parent = rotation_node->Parent;
        if (rotation_node->Parent == nullptr) {
            Root = left_node;
        } else if (rotation_node == rotation_node->Parent->Left) {
            rotation_node->Parent->Left = left_node;
        } else {
            rotation_node->Parent->Right = left_node;
        }
        left_node->Right = rotation_node;
        rotation_node->Parent = left_node;
        rotation_node->OverHeight();
        left_node->OverHeight();
    }

    void LeftRotation(Node<TKey, TValue> *rotation_node) {
        Node<TKey, TValue> *right_node = rotation_node->Right;
        rotation_node->Right = right_node->Left;
        if (right_node->Left != nullptr) {
            right_node->Left->Parent = rotation_node;
        } 
        right_node->Parent = rotation_node->Parent;
        if (rotation_node->Parent == nullptr) {
            Root = right_node;
        } else if (rotation_node == rotation_node->Parent->Left) {
            rotation_node->Parent->Left = right_node;
        } else {
            rotation_node->Parent->Right = right_node;
        }
        right_node->Left = rotation_node;
        rotation_node->Parent = right_node;
        rotation_node->OverHeight();
        right_node->OverHeight();
    }

    Node<TKey, TValue> *Balance(Node<TKey, TValue> *node) {
        node->OverHeight();
        if (node->HeightDifference() == 2) {
            if (node->Right->HeightDifference < 0) {
                // node->Right = node->Right->RightRotation
            }
        }
    }

    void Insert(Node<TKey, TValue> *new_node) {
        Node<TKey, TValue> *current_node = Root;
        Node<TKey, TValue> *parent_node = nullptr;
        while (current_node != nullptr) {
            parent_node = current_node;
            if (new_node->Key < current_node->Key) {
                current_node = current_node->Left;
            }
            else {
                current_node = current_node->Right;
            }
        }
        if (new_node->Key < parent_node->Key) {
            parent_node->Left = new_node;
        }
        else {
            parent_node->Right = new_node;
        }
        new_node->Parent = parent_node;
        parent_node->Height += 1;
    }
};