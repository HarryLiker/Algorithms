#include <iostream>
#include <string>
#include "BSTree.hpp"

int main() {
    BinarySearchTree <unsigned long long, std::string> *tree;
    tree = new BinarySearchTree<unsigned long long, std::string>;
    unsigned long long key;
    std::string value;
    while (std::cin >> key >> value) {
        Node<unsigned long long, std::string> *new_node;
        new_node = new Node<unsigned long long, std::string>(key, value);
        tree->Insert(new_node);
    }
    tree->Delete(15);
}