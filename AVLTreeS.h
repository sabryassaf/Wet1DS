#include "AVLNode.h"

template<class Data>
class AVLTree
{
private:
    AVLNode<Data>* m_root;

public:
    AVLTree() : m_root(nullptr) {}

    ~AVLTree()
    {
        clear();
    }

    void insert(Data* data)
    {
        if (m_root == nullptr)
        {
            m_root = new AVLNode<Data>(data);
        }
        else
        {
            insertRecursive(data, m_root);
        }
    }

    bool remove(Data* data)
    {
        if (m_root == nullptr)
        {
            return false;
        }
        else
        {
            return removeRecursive(data, m_root);
        }
    }

    void clear()
    {
        clearRecursive(m_root);
        m_root = nullptr;
    }

private:
    void insertRecursive(Data* data, AVLNode<Data>* node)
    {
        int compareResult = node->compareNodes(*data);
        if (compareResult == 0)
        {
            // Data already exists in the tree
            return;
        }
        else if (compareResult > 0)
        {
            // Data should be inserted to the left
            if (node->getLeftChild() == nullptr)
            {
                AVLNode<Data>* newNode = new AVLNode<Data>(data);
                node->setLeftChild(newNode);
            }
            else
            {
                insertRecursive(data, node->getLeftChild());
            }
        }
        else
        {
            // Data should be inserted to the right
            if (node->getRightChild() == nullptr)
            {
                AVLNode<Data>* newNode = new AVLNode<Data>(data);
                node->setRightChild(newNode);
            }
            else
            {
                insertRecursive(data, node->getRightChild());
            }
        }

        // Balance the tree
        balance(node);
    }

    bool removeRecursive(Data* data, AVLNode<Data>* node)
    {
        int compareResult = node->compareNodes(*data);
        if (compareResult == 0)
        {
            // Found the node to remove
            if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr)
            {
                // Node is a leaf
                AVLNode<Data>* parent = node->getParent();
                if (parent != nullptr)
                {
                    if (parent->getLeftChild() == node)
                    {
                        parent->setLeftChild(nullptr);
                    }
                    else
                    {
                        parent->setRightChild(nullptr);
                    }

                    delete node;
                    balance(parent);
                }
                else
                {
                    // Removing the root node
                    delete node;
                    m_root = nullptr;
                }
            }
            else if (node->getLeftChild() != nullptr && node->getRightChild() == nullptr)
            {
                // Node has only a left child
                AVLNode<Data>* leftChild = node->getLeftChild();
                AVLNode<Data>* parent = node->getParent();
                if (parent != nullptr)
                {
                    if (parent->getLeftChild() == node)
                    {
                        parent->setLeftChild(leftChild);
                    }
                    else
                    {
                        parent->setRightChild(leftChild);
                    }

                    leftChild->setParent(parent);
                    delete node;
                    balance(parent);
                }
                else
                {
                    // Removing the root node
                    m_root = leftChild;
                    leftChild->setParent(nullptr);
                    delete node;
                }
            }
            else if (node->getLeftChild() == nullptr && node->getRightChild() != nullptr)
            {
                // Node has only a right child
                AVLNode<Data>* rightChild = node->getRightChild();
                AVLNode<Data>* parent = node->getParent();
                if (parent != nullptr)
                {
                    if (parent->getLeftChild() == node)
                    {
                        parent->setLeftChild(rightChild);
                    }
                    else
                    {
                        parent->setRightChild(rightChild);
                    }

                    rightChild->setParent(parent);
                    delete node;
                    balance(parent);
                }
                else
                {
                    // Removing the root node
                    m_root = rightChild;
                    rightChild->setParent(nullptr);
                    delete node;
                }
            }
            else
            {
                // Node has both left and right children
                AVLNode<Data>* successor = findSuccessor(node);
                Data* successorData = successor->getData();
                remove(successorData);
                node->setData(successorData);
            }

            return true;
        }
        else if (compareResult > 0 && node->getLeftChild() != nullptr)
        {
            // Data might be in the left subtree
            return removeRecursive(data, node->getLeftChild());
        }
        else if (compareResult < 0 && node->getRightChild() != nullptr)
        {
            // Data might be in the right subtree
            return removeRecursive(data, node->getRightChild());
        }

        return false;
    }

    AVLNode<Data>* findSuccessor(AVLNode<Data>* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        AVLNode<Data>* current = node->getRightChild();
        while (current != nullptr && current->getLeftChild() != nullptr)
        {
            current = current->getLeftChild();
        }

        return current;
    }

    void clearRecursive(AVLNode<Data>* node)
    {
        if (node != nullptr)
        {
            clearRecursive(node->getLeftChild());
            clearRecursive(node->getRightChild());
            delete node;
        }
    }

    void balance(AVLNode<Data>* node)
    {
        if (node == nullptr)
        {
            return;
        }

        int balanceFactor = node->getBalanceFactor();
        if (balanceFactor > 1)
        {
            // Left subtree is taller
            AVLNode<Data>* leftChild = node->getLeftChild();
            int leftChildBalanceFactor = leftChild->getBalanceFactor();
            if (leftChildBalanceFactor >= 0)
            {
                // Left-Left case
                rotateRight(node);
            }
            else
            {
                // Left-Right case
                rotateLeft(leftChild);
                rotateRight(node);
            }
        }
        else if (balanceFactor < -1)
        {
            // Right subtree is taller
            AVLNode<Data>* rightChild = node->getRightChild();
            int rightChildBalanceFactor = rightChild->getBalanceFactor();
            if (rightChildBalanceFactor <= 0)
            {
                // Right-Right case
                rotateLeft(node);
            }
            else
            {
                // Right-Left case
                rotateRight(rightChild);
                rotateLeft(node);
            }
        }

        balance(node->getParent());
    }

    void rotateLeft(AVLNode<Data>* node)
    {
        if (node == nullptr)
        {
            return;
        }

        AVLNode<Data>* rightChild = node->getRightChild();
        if (rightChild == nullptr)
        {
            return;
        }

        AVLNode<Data>* parent = node->getParent();
        if (parent != nullptr)
        {
            if (parent->getLeftChild() == node)
            {
                parent->setLeftChild(rightChild);
            }
            else
            {
                parent->setRightChild(rightChild);
            }
        }
        else
        {
            m_root = rightChild;
        }

        rightChild->setParent(parent);
        node->setRightChild(rightChild->getLeftChild());
        rightChild->setLeftChild(node);
    }

    void rotateRight(AVLNode<Data>* node)
    {
        if (node == nullptr)
        {
            return;
        }

        AVLNode<Data>* leftChild = node->getLeftChild();
        if (leftChild == nullptr)
        {
            return;
        }

        AVLNode<Data>* parent = node->getParent();
        if (parent != nullptr)
        {
            if (parent->getLeftChild() == node)
            {
                parent->setLeftChild(leftChild);
            }
            else
            {
                parent->setRightChild(leftChild);
            }
        }
        else
        {
            m_root = leftChild;
        }

        leftChild->setParent(parent);
        node->setLeftChild(leftChild->getRightChild());
        leftChild->setRightChild(node);
    }
};
