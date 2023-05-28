//
// Created by halam on 15/05/2023.
//

#ifndef STREAMINGDBA1_CPP_RankTree_H
#define STREAMINGDBA1_CPP_RankTree_H

#include <iostream>
#include "AVLNode.h"
#include "wet1util.h"

template<class Key, class Data>
class RankTree
{
private:

    int m_size;
    AVLNode<Key, Data> *m_root;
    AVLNode<Key, Data> *m_max;

    AVLNode<Key, Data> *rightRotate(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *leftRotate(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingRR(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingLL(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingLR(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingRL(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *MakeBalance(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *InsertNodeAux(Key &key, Data &data, AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *DeleteNodeAux(const Key &key, AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *FindNodeAux(const Key &key, AVLNode<Key, Data> *node);

    void BuildInOrderArrayAux(AVLNode<Key, Data> *node, Data *InOrderArray, int *index);

public:

    void FreeData(AVLNode<Key, Data> *node);

    void DeleteTree(AVLNode<Key, Data> *node);

    RankTree() : m_size(0), m_root(nullptr), m_max(nullptr)
    {}

    RankTree(const RankTree &other) = delete;

    RankTree &operator=(const RankTree &other) = delete;

    virtual ~RankTree()
    {
        DeleteTree(m_root);
    }

    int getSize() const;

    StatusType Insert(Key &key, Data &data);

    StatusType Remove(const Key &key);

    Data Find(const Key &key);

    AVLNode<Key, Data> *getRoot() const;

    AVLNode<Key, Data> *getMax() const;

    void BuildInOrderArray(Data *InOrderArray);

    bool EmptyTree() const;

    void setNewMax();

};
////////////////////// Implementations for private//////////////



template<class Key, class Data>

AVLNode<Key, Data> *RankTree<Key, Data>::getRoot() const
{
    return this->m_root;
}

template<class Key, class Data>

AVLNode<Key, Data> *RankTree<Key, Data>::getMax() const
{
    return this->m_max;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::rightRotate(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *RotateNode = node->getLeftChild();
    node->setLeftChild(RotateNode->getRightChild());

    if (node->getParent())
    {
        if (node->getParent()->getLeftChild() == node)
        {
            node->getParent()->setLeftChild(RotateNode);
        } else
        {
            node->getParent()->setRightChild(RotateNode);
        }
    }
    RotateNode->setParent(node->getParent());
    RotateNode->setRightChild(node);
    if (this->m_root == node)
    {
        this->m_root = RotateNode;
    }
    node->updateParameters();
    RotateNode->updateParameters();
    return RotateNode;

}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::leftRotate(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *RotateNode = node->getRightChild();
    node->setRightChild(RotateNode->getLeftChild());

    if (node->getParent())
    {
        if (node->getParent()->getLeftChild() == node)
        {
            node->getParent()->setLeftChild(RotateNode);
        } else
        {
            node->getParent()->setRightChild(RotateNode);
        }
    }
    RotateNode->setParent(node->getParent());
    RotateNode->setLeftChild(node);
    if (this->m_root == node)
    {
        this->m_root = RotateNode;
    }
    node->updateParameters();
    RotateNode->updateParameters();
    return RotateNode;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingLL(AVLNode<Key, Data> *node)
{
    return rightRotate(node);
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingRR(AVLNode<Key, Data> *node)
{
    return leftRotate(node);
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingRL(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *RotateNode = node->getRightChild();
    node->setRightChild(RollingLL(RotateNode));
    return RollingRR(node);
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingLR(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *RotateNode = node->getLeftChild();
    node->setLeftChild(RollingRR(RotateNode));
    return RollingLL(node);
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::MakeBalance(AVLNode<Key, Data> *node)
{

     if (node->getBalanceFactor() < -1)
    {
        if (node->getRightChild()->getBalanceFactor() > 0)
            return RollingRL(node);
        return RollingRR(node);

    }

     if (node->getBalanceFactor() > 1)
     {
         if (node->getLeftChild()->getBalanceFactor() < 0)
             return RollingLR(node);
         return RollingLL(node);
     }
    return node;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::InsertNodeAux(Key &key, Data &data, AVLNode<Key, Data> *node)
{
    if (node)

    {
        if (key > node->getKey())
        {
            AVLNode<Key, Data> *newNode = InsertNodeAux(key, data, node->getRightChild());
            node->setRightChild(newNode);
        }
        else if (key < node->getKey())
        {
            AVLNode<Key, Data> *newNode = InsertNodeAux(key, data, node->getLeftChild());
            node->setLeftChild(newNode);
        }
    }

    else
    {
        auto *newNode = new AVLNode<Key, Data>(key, data);
        if (!newNode )
            return nullptr;

        newNode->setHeight(0);
        if (!m_root)
        {
            m_root = newNode;
            m_max = newNode;
        }

        return newNode;
    }

    node->updateParameters();
    AVLNode<Key, Data> *balance = MakeBalance(node);
    if (node == this->m_root)
    {
        this->m_root = balance;
    }
    return balance;
}


//
template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::DeleteNodeAux(const Key &key, AVLNode<Key, Data> *node)
{
    if (!node)
        return nullptr;

    if (node->getKey() == key)
    {
        AVLNode<Key, Data> *tempNode;
        if ((node->getLeftChild() == nullptr) && (node->getRightChild() == nullptr)) {
            if (m_root == node) {
                m_root = nullptr;
            }
            delete node;
            return nullptr;
        }
        else if (((node->getLeftChild() == nullptr) && node->getRightChild()) ||
                   ((node->getRightChild() == nullptr) && node->getLeftChild())) //ONE CHILD ONLY
        {
            if (node->getLeftChild()) {
                tempNode = node->getLeftChild();
            } else {
                tempNode = node->getRightChild();
            }

            if (m_root == node) {
                m_root = tempNode;
                m_root->setParent(nullptr);
            } else{
                tempNode->setParent(node->getParent());
            }

            delete node;
            node = tempNode;
        }
        else {
            tempNode = node->getRightChild();
            while (tempNode->getLeftChild()) {
                tempNode = tempNode->getLeftChild();
            }
            tempNode->swap(node);
            node->setRightChild(DeleteNodeAux(key, node->getRightChild()));
        }
    }
    else if (node->getKey() < key)
    {
        node->setRightChild(DeleteNodeAux(key, node->getRightChild()));
    }

    else if (node->getKey() > key)
    {
        node->setLeftChild(DeleteNodeAux(key, node->getLeftChild()));
    }

    node->updateParameters();
    node = MakeBalance(node);
    return node;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::FindNodeAux(const Key &key, AVLNode<Key, Data> *node)
{
    if (!node)
        return nullptr;


    if (key == node->getKey())
        return node;


    if (key > node->getKey())
        return FindNodeAux(key, node->getRightChild());


    if (key < node->getKey())
        return FindNodeAux(key, node->getLeftChild());


    return nullptr;
}

template<class Key, class Data>
void RankTree<Key, Data>::BuildInOrderArrayAux(AVLNode<Key, Data> *node, Data *InOrderArray, int *index)
{
    if (!node)
        return;

    BuildInOrderArrayAux(node->getRightChild(), InOrderArray, index);
    InOrderArray[(*index)++] = node->getData();
    BuildInOrderArrayAux(node->getLeftChild(), InOrderArray, index);
}
////////////////////// Implementations for public//////////////

template<class Key, class Data>
void RankTree<Key, Data>::DeleteTree(AVLNode<Key, Data> *node)
{
    if (!node)
        return;


    DeleteTree(node->getRightChild());
    DeleteTree(node->getLeftChild());
    delete node;
}

template<class Key, class Data>
void RankTree<Key, Data>::FreeData(AVLNode<Key, Data> *node)
{
    if (!node )
        return;

    FreeData(node->getRightChild());
    FreeData(node->getLeftChild());
    delete node->getData();
}

template<class Key, class Data>
StatusType RankTree<Key, Data>::Insert(Key &key, Data &data)
{
    if (this->FindNodeAux(key, m_root))
        return StatusType::FAILURE;


    m_root = InsertNodeAux(key, data, m_root);
    if (!m_root)
        return StatusType::ALLOCATION_ERROR;

    this->setNewMax();
    m_size++;
    return StatusType::SUCCESS;
}

template<class Key, class Data>
StatusType RankTree<Key, Data>::Remove(const Key &key)
{

    if (!FindNodeAux(key, m_root))
        return StatusType::FAILURE;

    m_max = nullptr;
    m_root = DeleteNodeAux(key, m_root);
    this->setNewMax();
    m_size--;
    return StatusType::SUCCESS;
}

template<class Key, class Data>
void RankTree<Key, Data>::setNewMax()
{
    if (!m_root)
    {
        m_max = nullptr;
        return;
    }
    AVLNode<Key, Data> *tmp = m_root;
    while (tmp->getRightChild() != nullptr)
    {
        tmp = tmp->getRightChild();
    }
    m_max = tmp;
}

template<class Key, class Data>
Data RankTree<Key, Data>::Find(const Key &key)
{
    AVLNode<Key, Data> *tmp = FindNodeAux(key, m_root);
    if (!tmp)
        return nullptr;

    return tmp->getData();
}


template<class Key, class Data>
int RankTree<Key, Data>::getSize() const
{
    return m_size;
}


template<class Key, class Data>
void RankTree<Key, Data>::BuildInOrderArray(Data *InOrderArray)
{
    int index = 0;
    BuildInOrderArrayAux(m_root, InOrderArray, &index);
}

template<class Key, class Data>
bool RankTree<Key, Data>::EmptyTree() const
{
    return m_size <= 0;
}

#endif //STREAMINGDBA1_CPP_RankTree_H
