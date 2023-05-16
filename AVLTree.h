//
// Created by halam on 15/05/2023.
//

#ifndef STREAMINGDBA1_CPP_AVLTREE_H
#define STREAMINGDBA1_CPP_AVLTREE_H
#include <iostream>
#include "AVLNode.h"
#include "wet1util.h"

template <class Key, class Data>
class AVLtree
{
private:

    int m_size;
    AVLNode<Key,Data> *m_root;
    AVLNode<Key,Data> *RotateRight(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *RotateLeft(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *RollingRR(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *RollingLL(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *RollingLR(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *RollingRL(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *MakeBalance(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *InsertNode(const Key &key,const Data &data, AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *DeleteNode(const Key &key, AVLNode<Key,Data> *node);
    int BF(AVLNode<Key,Data>* node);
    void UpdateHeight(AVLNode<Key,Data>* node);
    AVLNode<Key,Data>* FindNode(AVLNode<Key,Data>* currentNode, const Key& key);
    void BuildInOrderArray(AVLNode<Key,Data>* node, Data* InOrderArray);
    void DeleteTree(AVLNode<Key,Data>* node);


public:

            AVLtree() : m_size(0), m_root(nullptr){}
            AVLtree(const AVLtree &other) = delete;
            AVLtree &operator=(const AVLtree &other) = delete;
            virtual ~AVLtree();
            int getSize() const;
            StatusType Insert(const Key &key, const Data &data);
            StatusType Remove(const Key &key);
            Data Find(const Key &key);
            bool ElementInTree(const Key &key);

};
            ////////////////////// Implementations for private//////////////

template <class Key ,class Data>
int AVLtree<Key,Data>::BF(AVLNode<Key,Data> *node)
{
    return (node->m_leftChild.getHeight() - node->m_rightChild.getHeight());
}
template <class Key ,class Data>
AVLNode<Key,Data> *AVLtree<Key,Data>::RotateRight(AVLNode<Key,Data> *node)
{
    AVLNode<Key,Data>* newnode = node->m_leftChild;
    AVLNode<Key,Data>* tempnode = node;
    node->m_leftChild = newnode->m_rightChild;
    if (tempnode->m_leftChild != nullptr){
        tempnode->m_leftChild->m_parent = tempnode;
    }
    newnode->m_rightChild = tempnode;
    newnode->m_parent = tempnode->m_parent;
    tempnode->m_parent = newnode;
    tempnode->updateParameters();
    newnode->updateParameters();
    return newnode;

}
template <class Key ,class Data>
AVLNode<Key,Data> *AVLtree<Key,Data>::RotateLeft(AVLNode<Key,Data> *node)
{
    AVLNode<Key,Data>* newnode = node->m_rightChild;
    AVLNode<Key,Data>* tempnode = node;
    node->m_rightChild = newnode->m_leftChild;
    if (tempnode->m_rightChild != nullptr){
        tempnode->m_rightChild->m_parent = tempnode;
    }
    newnode->m_leftChild = tempnode;
    newnode->m_parent = tempnode->m_parent;
    tempnode->m_parent = newnode;
    tempnode->updateParameters();
    newnode->updateParameters();
    return newnode;

}
template <class Key ,class Data>
AVLNode<Key,Data>  *AVLtree<Key,Data>::RollingRR(AVLNode<Key,Data>* node){
    return RotateLeft(node);
}

template <class Key ,class Data>
AVLNode<Key,Data>  *AVLtree<Key,Data>::RollingLL(AVLNode<Key,Data>* node){
    return RotateRight(node);
}

template <class Key ,class Data>
AVLNode<Key,Data>  *AVLtree<Key,Data>::RollingRL(AVLNode<Key,Data>* node)
{
    node->m_rightChild = RotateRight(node->m_rightChild);
    return RotateLeft(node);
}

template <class Key ,class Data>
AVLNode<Key,Data>  *AVLtree<Key,Data>::RollingLR(AVLNode<Key,Data>* node)
{    node->m_leftChild = RotateLeft(node->m_leftChild);
    return RotateRight(node);
}

template <class Key ,class Data>
AVLNode<Key,Data> *AVLtree<Key,Data>:: MakeBalance(AVLNode<Key,Data>* node)
{
    int BF = BF(node);
    if (BF == 2)
    {
        if(BF(node->m_leftChild) >= 0)
        {
            return RollingLL(node);
        }
        else if (BF(node->m_leftChild) == -1)
        {
            return RollingLR(node);
        }
    }
    else if (BF == -2)
    {
        if(BF(node->m_rightChild) == 1)
        {
            return RollingRL(node);
        }
        else if (BF(node->m_rightChild) <= 0)
        {
            return RollingRR(node);
        }
    }
    return node;
}
template <class Key ,class Data>
AVLNode<Key,Data> *AVLtree<Key,Data>::InsertNode(const Key &key, const Data &data, AVLNode<Key,Data> *node)
{
    if (node == nullptr) //tree is empty
    {
        AVLNode<Key,Data>* newElement = new AVLNode<Key,Data>;
        if (newElement == nullptr){
            return nullptr;
        }
        newElement->m_key = key;
        newElement->m_data = data;
        newElement->m_height = 1;
        if (m_root == nullptr){
            m_root = newElement;
        }
        m_size++;
        return newElement;
    }
    else //tree not empty
    {
        if(key > node->m_key)
        {
            AVLNode<Key,Data>* newNode = InsertNode(key, data,node->m_rightChild);
            newNode->m_parent_node = node;
            node->m_rightChild = newNode;
            node->m_rightChild->m_parent_node = node;
        }
        else if(key < node->m_key)
        {
            AVLNode<Key,Data>* newNode = InsertNode(node->m_leftChild, key, data);
            newNode->m_parent_node = node;
            node->m_leftChild = newNode;
            node->m_leftCHild->m_parent_node = node;
        }
    }
    node->updateHeight();
    node = MakeBalance(node);
    return node;
}
template <class Key ,class Data>
AVLNode<Key,Data> *AVLtree<Key,Data>::DeleteNode(const Key &key, AVLNode<Key, Data> *node)
{
    
}
////////////////////// Implementations for public//////////////























#endif //STREAMINGDBA1_CPP_AVLTREE_H
