//
// Created by halam on 15/05/2023.
//

#ifndef STREAMINGDBA1_CPP_RankTree_H
#define STREAMINGDBA1_CPP_RankTree_H

#include <iostream>
#include "AVLNode.h"
#include "wet1util.h"
//#include "Data.h"

template<class Key, class Data>
class RankTree
{
private:

    int size;
    AVLNode<Key, Data> *root;
    AVLNode<Key, Data> *m_max;

    AVLNode<Key, Data> *RotateRight(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RotateLeft(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingRR(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingLL(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingLR(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingRL(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *MakeBalance(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *InsertNode(Key &key, Data &data, AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *DeleteNode(const Key &key, AVLNode<Key, Data> *node);

    int BalanceFactor(AVLNode<Key, Data> *node);

    void UpdateHeight(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *FindNode(const Key &key, AVLNode<Key, Data> *node);

    void BuildInOrderArrayAux(AVLNode<Key, Data> *node, Data *InOrderArray, int *index);

public:
    void FreeData(AVLNode<Key, Data> *node);

    void DeleteTree(AVLNode<Key, Data> *node);

    RankTree() : size(0), root(nullptr), m_max(nullptr)
    {}

    RankTree(const RankTree &other) = delete;

    RankTree &operator=(const RankTree &other) = delete;

    virtual ~RankTree()
    {
        DeleteTree(root);
    }

    int getSize() const;

    StatusType Insert(Key &key, Data &data);

    StatusType Remove(const Key &key);

    Data Find(const Key &key);

    bool ElementInTree(const Key &key);

    AVLNode<Key, Data> *getRoot() const;

    AVLNode<Key, Data> *getMax() const;

    void setRoot(AVLNode<Key, Data> *newRoot);

    void BuildInOrderArray(Data *InOrderArray);

    bool EmptyTree() const;

};
////////////////////// Implementations for private//////////////

template<class Key, class Data>
void RankTree<Key, Data>::setRoot(AVLNode<Key, Data> *newRoot)
{
    this->root = newRoot;
}

template<class Key, class Data>

AVLNode<Key, Data> *RankTree<Key, Data>::getRoot() const
{
    return this->root;
}

template<class Key, class Data>

AVLNode<Key, Data> *RankTree<Key, Data>::getMax() const
{
    return this->m_max;
}

template<class Key, class Data>
int RankTree<Key, Data>::BalanceFactor(AVLNode<Key, Data> *node)
{
    return (node->getLeftChild()->getHeight() - node->getRightChild()->getHeight());
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RotateRight(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *newnode = node->getLeftChild();
    node->setLeftChild(newnode->getRightChild());

    if (node->getParent() != nullptr)
    {
        if (node->getParent()->getLeftChild() == node)
        {
            node->getParent()->setLeftChild(newnode);
        } else
        {
            node->getParent()->setRightChild(newnode);
        }
    }
    newnode->setParent(node->getParent());
    newnode->setRightChild(node);
    if (this->root == node)
    {
        this->root = newnode;
    }
    node->updateParameters();
    newnode->updateParameters();
    return newnode;

}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RotateLeft(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *newnode = node->getRightChild();
    node->setRightChild(newnode->getLeftChild());

    if (node->getParent() != nullptr)
    {
        if (node->getParent()->getLeftChild() == node)
        {
            node->getParent()->setLeftChild(newnode);
        } else
        {
            node->getParent()->setRightChild(newnode);
        }
    }
    newnode->setParent(node->getParent());
    newnode->setLeftChild(node);
    if (this->root == node)
    {
        this->root = newnode;
    }
    node->updateParameters();
    newnode->updateParameters();
    return newnode;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingLL(AVLNode<Key, Data> *node)
{
    return RotateRight(node);
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingRR(AVLNode<Key, Data> *node)
{
    return RotateLeft(node);
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingRL(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *newnode = node->getRightChild();
    node->setRightChild(RollingLL(newnode));
    return RollingRR(node);
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingLR(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *newnode = node->getLeftChild();
    node->setLeftChild(RollingRR(newnode));
    return RollingLL(node);
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::MakeBalance(AVLNode<Key, Data> *node)
{
    int BF = node->getBalanceFactor();
    if (BF > 1)
    {
        if (node->getLeftChild()->getBalanceFactor() >= 0)
        {
            return RollingLL(node);
        } else
        {
            return RollingLR(node);
        }
    } else if (BF < -1)
    {
        if (node->getRightChild()->getBalanceFactor() > 0)
        {
            return RollingRL(node);
        } else
        {
            return RollingRR(node);
        }
    }
//    root->setParent(nullptr);
    return node;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::InsertNode(Key &key, Data &data, AVLNode<Key, Data> *node)
{
    if (node == nullptr)
    {
        AVLNode<Key, Data> *newElement = new AVLNode<Key, Data>(key, data);
        if (newElement == nullptr)
        {
            return nullptr;
        }
//        newElement->setKey(key);
//        newElement->setData(data);
        newElement->setHeight(0);
        if (root == nullptr)
        {
            root = newElement;
            m_max = newElement;
        } else if (this->m_max && key > this->m_max->getKey())
        {
            m_max = newElement;
        }
        return newElement;
    } else
    {
        if (key > node->getKey())
        {
            AVLNode<Key, Data> *newNode = InsertNode(key, data, node->getRightChild());
            node->setRightChild(newNode);
        } else if (key < node->getKey())
        {
            AVLNode<Key, Data> *newNode = InsertNode(key, data, node->getLeftChild());
            node->setLeftChild(newNode);
        }
    }
    node->updateParameters();
    AVLNode<Key, Data> *balancedNode = MakeBalance(node);
    if (node == this->root)
    {
        this->root = balancedNode;
    }
    return balancedNode;
}
//
template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::DeleteNode(const Key &key, AVLNode<Key, Data> *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->getKey() == key)
    {
        AVLNode<Key, Data> *tempNode;
        if ((node->getLeftChild()) && (node->getRightChild())) // two SONS
        {
            tempNode = node->getRightChild();
            while (tempNode->getLeftChild())
            {
                tempNode = tempNode->getLeftChild();
            }
            tempNode->swap(node);
            node->setRightChild(DeleteNode(key, node->getRightChild()));
        } else if (((node->getLeftChild() == nullptr) && node->getRightChild()) ||
                   ((node->getRightChild() == nullptr) && node->getLeftChild())) //ONE CHILD ONLY
        {
            if (node->getLeftChild())
            {
                tempNode = node->getLeftChild();
            } else
            {
                tempNode = node->getRightChild();
            }

            if (root == node)
            {
                root = tempNode;
                root->setParent(nullptr);
            } else
            {
                tempNode->setParent(node->getParent());
            }

            delete node;
            node = tempNode;
        } else //no sons
        {
            if (root == node)
            {
                root = nullptr;
            }

            delete node;
            return nullptr;
        }
    } else if (node->getKey() < key)
    {
        node->setRightChild(DeleteNode(key, node->getRightChild()));
    } else if (node->getKey() > key)
    {
        node->setLeftChild(DeleteNode(key, node->getLeftChild()));
    }

    node->updateParameters();
    node = MakeBalance(node);
    if (node && node->getRightChild() == nullptr)
    {
        m_max = node;
    }
    return node;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::FindNode(const Key &key, AVLNode<Key, Data> *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (key == node->getKey())
    {
        return node;
    }

    if (key > node->getKey())
    {
        return FindNode(key, node->getRightChild());
    }

    if (key < node->getKey())
    {
        return FindNode(key, node->getLeftChild());
    }

    return nullptr;
}
////////////////////// Implementations for public//////////////

template<class Key, class Data>
void RankTree<Key, Data>::DeleteTree(AVLNode<Key, Data> *node)
{
    if (node == nullptr)
    {
        return;
    }

    DeleteTree(node->getRightChild());
    DeleteTree(node->getLeftChild());
    delete node;
}

template<class Key, class Data>
void RankTree<Key, Data>::FreeData(AVLNode<Key, Data> *node)
{
    if (node == nullptr)
    {
        return;
    }
    FreeData(node->getRightChild());
    FreeData(node->getLeftChild());
    delete node->getData();
    delete node;
}

template<class Key, class Data>
StatusType RankTree<Key, Data>::Insert(Key &key, Data &data)
{
    if (this->FindNode(key, root))
    {
        return StatusType::FAILURE;
    }

    root = InsertNode(key, data, root);
    if (root == nullptr)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    size++;
    return StatusType::SUCCESS;
}

template<class Key, class Data>
StatusType RankTree<Key, Data>::Remove(const Key &key)
{

    if (FindNode(key, root) == nullptr)
    {
        return StatusType::FAILURE;
    }
    root = DeleteNode(key, root);
    size--;
    return StatusType::SUCCESS;

}

template<class Key, class Data>
Data RankTree<Key, Data>::Find(const Key &key)
{
    AVLNode<Key, Data> *tmp = FindNode(key, root);
    if (tmp == nullptr)
    {
        return nullptr;
    }
    return tmp->getData();
}

template<class Key, class Data>
bool RankTree<Key, Data>::ElementInTree(const Key &key)
{
    if (root == nullptr)
    {
        return false;
    }

    return this->FindNode(key, root) != nullptr;
}

template<class Key, class Data>
int RankTree<Key, Data>::getSize() const
{
    return size;
}

template<class Key, class Data>
void RankTree<Key, Data>::BuildInOrderArrayAux(AVLNode<Key, Data> *node, Data *InOrderArray, int *index)
{
    if (node == nullptr)
    {
        return;
    }
    BuildInOrderArrayAux(node->getRightChild(), InOrderArray, index);
    InOrderArray[(*index)++] = node->getData();
    BuildInOrderArrayAux(node->getLeftChild(), InOrderArray, index);
}

template<class Key, class Data>
void RankTree<Key, Data>::BuildInOrderArray(Data *InOrderArray)
{
    int index = 0;
    BuildInOrderArrayAux(root, InOrderArray, &index);
}

template<class Key, class Data>
bool RankTree<Key, Data>::EmptyTree() const
{
    return size <= 0;
}

#endif //STREAMINGDBA1_CPP_RankTree_H
