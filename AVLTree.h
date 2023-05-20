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
    AVLNode<Key,Data>* FindNode(const Key& key,AVLNode<Key,Data>* node);
    void BuildInOrderArray(AVLNode<Key,Data>* node, Data* InOrderArray);
    void DeleteTree(AVLNode<Key,Data>* node);


public:

    AVLtree() : m_size(0), m_root(nullptr){}
    AVLtree(const AVLtree &other) = delete;
    AVLtree &operator=(const AVLtree &other) = delete;
    virtual ~AVLtree(){
        DeleteTree(m_root);
    }
    int getSize() const;
    StatusType Insert(const Key &key, const Data &data);
    StatusType Remove(const Key &key);
    Data Find(const Key &key);
    bool ElementInTree(const Key &key);
    void InOrderArray(Data* InOrderArray) const;


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
    if (newnode->m_rightChild != nullptr){
        newnode->m_rightChild->m_parent = node;
    }
    node->m_leftChild = newnode->m_rightChild;
    newnode->m_rightChild = node;
    newnode->m_parent = node->m_parent;
    node->m_parent = newnode;
    node->updateParameters();
    newnode->updateParameters();
    return newnode;

}
template <class Key ,class Data>
AVLNode<Key,Data> *AVLtree<Key,Data>::RotateLeft(AVLNode<Key,Data> *node)
{
    AVLNode<Key,Data>* newnode = node->m_rightChild;
    if (newnode->m_leftChild != nullptr){
        newnode->m_leftChild->m_parent = node;
    }
    node->m_rightChild = newnode->m_leftChild;
    newnode->m_leftChild = node;
    newnode->m_parent = node->m_parent;
    node->m_parent = newnode;
    node->updateParameters();
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
    int BF = AVLtree<Key,Data>::BF(node);
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
    m_root-> m_parent == nullptr;
    return node;
}
template <class Key ,class Data>
AVLNode<Key,Data> *AVLtree<Key,Data>::InsertNode(const Key &key, const Data &data, AVLNode<Key,Data> *node)
{
    if (node == nullptr) //tree is empty (we reached appropriate place)
    {
        AVLNode<Key,Data>* newElement = new AVLNode<Key,Data>; //making object to add to the tree
        if (newElement == nullptr){
            return nullptr;
        }
        newElement->m_key = key;
        newElement->m_data = data;
        newElement->m_height = 1;
        if (m_root == nullptr){
            m_root = newElement;
        }
        return newElement;
    }
    else //tree not empty - finding appropriate place
    {
        if(key > node->m_key) //we should put our new node on the right side of the given tree
        {
            AVLNode<Key,Data>* newNode = InsertNode(key, data,node->m_rightChild); //newnode is the right subtree
            newNode->m_parent = node;
            node->m_rightChild = newNode;
            node->m_rightChild->m_parent= node;
        }
        else if(key < node->m_key)
        {
            AVLNode<Key,Data>* newNode = InsertNode(node->m_leftChild, key, data);
            newNode->m_parent = node;
            node->m_leftChild = newNode;
            node->m_leftCHild->m_parent= node;
        }
    }
    node->updateHeight();
    node = MakeBalance(node);
    return node;
}
template <class Key ,class Data>
AVLNode<Key,Data> *AVLtree<Key,Data>::DeleteNode(const Key &key, AVLNode<Key, Data> *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if(node->m_key == key)

    {
        AVLNode<Key,Data>* tempNode;
        if ((node->m_leftChild ) && (node->m_rightChild )) // two SONS
        {
            tempNode = node->m_rightChild;
            while (tempNode->m_leftChild) {
                tempNode = tempNode->m_leftChild;
            }
            tempNode->swap(node);
            node->m_rightChild = DeleteNode(key,node->m_rightChild);
        }

        else if ((node->m_leftChild == nullptr) || (node->m_rightChild == nullptr)) //ONE CHILD ONLY
        {
            if (node->m_leftChild)
            {
                tempNode = node->m_leftChild;
            }
            else
            {
                tempNode = node->m_rightChild;
            }
            tempNode->m_parent = node->m_parent;
            delete node;
            node = tempNode;
        }
        else //no sons
        {
            delete node;
            node = nullptr;
            return node;
        }
    }
    else if (node->m_key < key)
    {
        node->m_rightChild = DeleteNode(key,node->m_rightChild);
    }
    else if (node->m_key > key)
    {
        node->m_leftChild = DeleteNode(key,node->m_leftChild);
    }
    node->updateParameters();
    return MakeBalance(node);
}
template <class Key ,class Data>
AVLNode<Key,Data> *AVLtree<Key,Data>:: FindNode(const Key& key,AVLNode<Key,Data>* node){
    if (node == nullptr)
    {
        return nullptr;
    }
    if(key == node->m_key)
    {
        return node;
    }
    else if(key > node->m_key)
    {
        return FindNode(key,node->m_rightChild);
    }
    else if(key < node-> m_key)
    {
        return FindNode(key,node->m_leftChild);
    }
    else
    {
        return nullptr;
    }
}
template <class Key ,class Data>
void AVLtree<Key,Data>::DeleteTree(AVLNode<Key,Data> *node)
{
    if (node == nullptr)
    {
        return;
    }
    DeleteTree(node->getRightChild());
    DeleteTree(node->getLeftChild());
    delete node;
}

////////////////////// Implementations for public//////////////

template <class Key ,class Data>
StatusType AVLtree<Key,Data>::Insert(const Key &key, const Data &data)
{

    if (this->FindNode(key))
    {
        return StatusType::FAILURE;
    }
    m_root = InsertNode(key, data,m_root);
    if(m_root == nullptr)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    m_size++;
    return StatusType::SUCCESS;
}
template <class Key ,class Data>
StatusType AVLtree<Key,Data>::Remove(const Key &key)
{

    if (FindNode(key,m_root) == nullptr){
        return StatusType::FAILURE;
    }
    m_root = DeleteNode(key,m_root);
    m_size--;
    return StatusType::SUCCESS;

}
template <class Key ,class Data>
Data AVLtree<Key,Data>::Find(const Key& key)
{
    AVLNode<Key,Data>* tmp = FindNode(key,m_root);
    if (tmp == nullptr){
        return nullptr;
    }
    return tmp->m_data;
}
template <class Key ,class Data>
bool AVLtree<Key,Data>:: ElementInTree(const Key& key){
    if (m_root == nullptr){//tree empty
        return false;
    }
    if (this->FindNode(key,m_root) == nullptr){
        return false;
    }else{
        return true;
    }
}
template <class Key ,class Data>
int AVLtree<Key,Data>::getSize() const {
    return m_size;
}




















#endif //STREAMINGDBA1_CPP_AVLTREE_H
