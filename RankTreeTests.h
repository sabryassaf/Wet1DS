
#include <iostream>
#include "AVLNode.h"
#include "wet1util.h"
#include "Data.h"




template <typename Key, typename Data>
class AVLTree {
public:
    AVLNode<Key,Data>* getRoot(){return root;}

    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear();
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    void insert(const Key& key, const Data& data) {
        AVLNode<Key, Data>* newNode = new AVLNode<Key, Data>(key, data);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        AVLNode<Key, Data>* currentNode = root;
        while (true) {
            if (key < currentNode->getKey()) {
                if (currentNode->getLeftChild() == nullptr) {
                    currentNode->setLeftChild(newNode);
                    break;
                } else {
                    currentNode = currentNode->getLeftChild();
                }
            } else if (key > currentNode->getKey()) {
                if (currentNode->getRightChild() == nullptr) {
                    currentNode->setRightChild(newNode);
                    break;
                } else {
                    currentNode = currentNode->getRightChild();
                }
            } else {
                // Key already exists, update the data
                delete newNode;
                currentNode->setData(data);
                return;
            }
        }

        newNode->setParent(currentNode);
        balanceTree(newNode);
    }

    void remove(const Key& key) {
        AVLNode<Key, Data>* node = searchNode(key);
        if (node == nullptr) {
            return;  // Key not found
        }

        AVLNode<Key, Data>* parentNode = node->getParent();

        if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr) {
            if (parentNode != nullptr) {
                if (parentNode->getLeftChild() == node) {
                    parentNode->setLeftChild(nullptr);
                } else {
                    parentNode->setRightChild(nullptr);
                }
                delete node;
                balanceTree(parentNode);
            } else {
                delete node;
                root = nullptr;
            }
        } else if (node->getLeftChild() != nullptr && node->getRightChild() == nullptr) {
            if (parentNode != nullptr) {
                if (parentNode->getLeftChild() == node) {
                    parentNode->setLeftChild(node->getLeftChild());
                } else {
                    parentNode->setRightChild(node->getLeftChild());
                }
                node->getLeftChild()->setParent(parentNode);
                delete node;
                balanceTree(parentNode);
            } else {
                node->getLeftChild()->setParent(nullptr);
                delete node;
                root = node->getLeftChild();
            }
        } else if (node->getLeftChild() == nullptr && node->getRightChild() != nullptr) {
            if (parentNode != nullptr) {
                if (parentNode->getLeftChild() == node) {
                    parentNode->setLeftChild(node->getRightChild());
                } else {
                    parentNode->setRightChild(node->getRightChild());
                }
                node->getRightChild()->setParent(parentNode);
                delete node;
                balanceTree(parentNode);
            } else {
                node->getRightChild()->setParent(nullptr);
                delete node;
                root = node->getRightChild();
            }
        } else {
            AVLNode<Key, Data>* successorNode = findSuccessor(node);
            node->swap(successorNode);
            AVLNode<Key, Data>* successorParent = successorNode->getParent();
            if (successorParent->getLeftChild() == successorNode) {
                successorParent->setLeftChild(successorNode->getRightChild());
            } else {
                successorParent->setRightChild(successorNode->getRightChild());
            }
            if (successorNode->getRightChild() != nullptr) {
                successorNode->getRightChild()->setParent(successorParent);
            }
            delete successorNode;
            balanceTree(successorParent);
        }
    }

    Data* search(const Key& key) const {
        AVLNode<Key, Data>* node = searchNode(key);
        if (node != nullptr) {
            return &(node->getData());
        }
        return nullptr;
    }

    bool contains(const Key& key) const {
        return (searchNode(key) != nullptr);
    }

private:
    void clear(AVLNode<Key, Data>* node) {
        if (node != nullptr) {
            clear(node->getLeftChild());
            clear(node->getRightChild());
            delete node;
        }
    }

    AVLNode<Key, Data>* findSuccessor(AVLNode<Key, Data>* node) const {
        AVLNode<Key, Data>* successor = node->getRightChild();
        while (successor->getLeftChild() != nullptr) {
            successor = successor->getLeftChild();
        }
        return successor;
    }

    AVLNode<Key, Data>* searchNode(const Key& key) const {
        AVLNode<Key, Data>* currentNode = root;
        while (currentNode != nullptr) {
            if (key < currentNode->getKey()) {
                currentNode = currentNode->getLeftChild();
            } else if (key > currentNode->getKey()) {
                currentNode = currentNode->getRightChild();
            } else {
                return currentNode;
            }
        }
        return nullptr;
    }

    void rotateLeft(AVLNode<Key, Data>* node) {
        AVLNode<Key, Data>* pivot = node->getRightChild();
        AVLNode<Key, Data>* parent = node->getParent();

        node->setRightChild(pivot->getLeftChild());
        if (pivot->getLeftChild() != nullptr) {
            pivot->getLeftChild()->setParent(node);
        }

        pivot->setLeftChild(node);
        node->setParent(pivot);

        pivot->setParent(parent);
        if (parent != nullptr) {
            if (parent->getLeftChild() == node) {
                parent->setLeftChild(pivot);
            } else {
                parent->setRightChild(pivot);
            }
        } else {
            root = pivot;
        }

        node->updateParameters();
        pivot->updateParameters();
    }

    void rotateRight(AVLNode<Key, Data>* node) {
        AVLNode<Key, Data>* pivot = node->getLeftChild();
        AVLNode<Key, Data>* parent = node->getParent();

        node->setLeftChild(pivot->getRightChild());
        if (pivot->getRightChild() != nullptr) {
            pivot->getRightChild()->setParent(node);
        }

        pivot->setRightChild(node);
        node->setParent(pivot);

        pivot->setParent(parent);
        if (parent != nullptr) {
            if (parent->getLeftChild() == node) {
                parent->setLeftChild(pivot);
            } else {
                parent->setRightChild(pivot);
            }
        } else {
            root = pivot;
        }

        node->updateParameters();
        pivot->updateParameters();
    }

    void balanceTree(AVLNode<Key, Data>* node) {
        while (node != nullptr) {
            node->updateParameters();
            int balanceFactor = node->getBalanceFactor();

            if (balanceFactor > 1) {
                if (node->getLeftChild()->getBalanceFactor() < 0) {
                    rotateLeft(node->getLeftChild());
                }
                rotateRight(node);
            } else if (balanceFactor < -1) {
                if (node->getRightChild()->getBalanceFactor() > 0) {
                    rotateRight(node->getRightChild());
                }
                rotateLeft(node);
            }

            node = node->getParent();
        }
    }
private:
    AVLNode<Key, Data>* root;
};

