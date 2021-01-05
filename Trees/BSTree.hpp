#pragma once

template <class TKey, class TValue>
struct Node {
    TKey Key;
    TValue Value;
    Node *Parent;
    Node *Left;
    Node *Right;
    Node(): Key(), Value(), Parent(nullptr), Left(nullptr), Right(nullptr) {}
    Node(TKey key, TValue value): Key(key), Value(value) {}
    ~Node() {}
};


template <class TKey, class TValue>
class BinarySearchTree {
private:
    Node<TKey, TValue> *Root;
public:
    BinarySearchTree(): Root(nullptr) {}

    // Search node in tree
    Node<TKey,TValue> *Search(TKey key) {
        Node<TKey,TValue> *current_root = Root;
        while (current_root != nullptr && key != current_root->Key) {
            if (key < current_root->Key) {
                current_root = current_root->Left;
            }
            else {
                current_root = current_root->Right;
            }
        }
        return current_root;
    }

    // Insert node in tree
    void Insert(Node<TKey, TValue> *new_node) {
        if (Root == nullptr) {
            Root = new_node;
            return;
        }
        Node<TKey, TValue> *current_root = Root;
        Node<TKey, TValue> *parent_root = nullptr;
        while (current_root != nullptr) {
            parent_root = current_root;
            if (new_node->Key != current_root->Key) {
                if (new_node->Key < current_root->Key) {
                    current_root = current_root->Left;
                }
                else {
                    current_root = current_root->Right;
                }
            }
        }
        current_root = new_node;
        if (new_node->Key < parent_root->Key) {
            parent_root->Left = new_node;
        }
        else {
            parent_root->Right = new_node;
        }
        current_root->Parent = parent_root;
    }

    // Find minimal node in subtree
    Node<TKey, TValue> *MinimalNode(Node<TKey, TValue> *node) {
        while (node->Left != nullptr) {
            node = node->Left;
        }
        return node;
    }

    // Delete node by key
    void Delete(TKey key) {
        Node<TKey, TValue> *current_node = Root;
        Node<TKey, TValue> *parent_node = nullptr;
        while (current_node != nullptr && current_node->Key != key) {
            parent_node = current_node;
            if (key < current_node->Key) {
                current_node = current_node->Left;
            }
            else {
                current_node = current_node->Right;
            }
        }
        if (current_node->Left == nullptr && current_node->Right == nullptr) {
        }
        else if (current_node->Left == nullptr || current_node->Right == nullptr) {
            if (current_node->Left == nullptr) {
                if (parent_node->Left == current_node) {
                    parent_node->Left = current_node->Right;
                }
                else {
                    parent_node->Right = current_node->Right;
                }
            }
            else {
                if (parent_node->Left == current_node) {
                    parent_node->Left = current_node->Left;
                }
                else {
                    parent_node->Right = current_node->Right;
                }
            }
        }
        else {
            Node<TKey,TValue> *min_node = MinimalNode(current_node->Right);
            if (min_node->Parent->Left == min_node) {
                min_node->Parent->Left = nullptr;
            }
            else {
                min_node->Parent->Right = nullptr;
            }
            min_node->Parent = parent_node;
            if (parent_node->Left == current_node) {
                parent_node->Left = min_node;
            }
            else {
                parent_node->Right = min_node;
            }
            min_node->Right = current_node->Right;
            min_node->Left = current_node->Left;
        }
        delete current_node;
    }

    ~BinarySearchTree() {}
};
