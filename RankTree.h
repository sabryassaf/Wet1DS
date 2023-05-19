//
// Created by halam on 15/05/2023.
//

#ifndef STREAMINGDBA1_CPP_RankTree_H
#define STREAMINGDBA1_CPP_RankTree_H
#include <iostream>
#include "AVLNode.h"
#include "wet1util.h"
#include "Data.h"

template <class Key, class Data>
class RankTree
{
private:

    int size;
    AVLNode<Key,Data> *root;
    AVLNode<Key,Data> *RotateRight(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *RotateLeft(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *RollingRR(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *RollingLL(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *RollingLR(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *RollingRL(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *MakeBalance(AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *InsertNode( Key &key, Data & data, AVLNode<Key,Data> *node);
    AVLNode<Key,Data> *DeleteNode(const Key &key, AVLNode<Key,Data> *node);
    int BalanceFactor(AVLNode<Key,Data>* node);
    void UpdateHeight(AVLNode<Key,Data>* node);
    AVLNode<Key,Data>* FindNode(const Key& key,AVLNode<Key,Data>* node);
    void BuildInOrderArray(AVLNode<Key,Data>* node, Data* InOrderArray);


public:
    void DeleteTree(AVLNode<Key,Data>* node);
    RankTree() : size(0), root(nullptr){}
    RankTree(const RankTree &other) = delete;
    RankTree &operator=(const RankTree &other) = delete;
    virtual ~RankTree(){
        DeleteTree(root);
    }
    int getSize() const;
    StatusType Insert( Key &key,  Data &data);
    StatusType Remove(const Key &key);
    Data * Find(const Key &key);
    bool ElementInTree(const Key &key);
    AVLNode<Key,Data> * getRoot()const;
    void setRoot(AVLNode<Key,Data> * newRoot);
};
////////////////////// Implementations for private//////////////

template <class Key ,class Data>
void RankTree<Key,Data>::setRoot(AVLNode<Key,Data> * newRoot)
{
    this->root = newRoot;
}

template <class Key ,class Data>

AVLNode<Key,Data> * RankTree<Key,Data>::getRoot() const
{
    return this->root;
}

template <class Key ,class Data>
int RankTree<Key,Data>::BalanceFactor(AVLNode<Key,Data> *node)
{
    return (node->getLeftChild()->getHeight() - node->getRightChild()->getHeight());
}
template <class Key ,class Data>
AVLNode<Key,Data> *RankTree<Key,Data>::RotateRight(AVLNode<Key,Data> *node)
{
    AVLNode<Key,Data>* newnode = node->getLeftChild();
    node->setLeftChild(newnode->getRightChild());
    if (newnode->getRightChild() != nullptr){
        newnode->getRightChild()->setParent(node);
    }
    newnode->setRightChild(node);
    newnode->setParent( node->getParent());
    if (node->getParent() != nullptr) {
        if (node->getParent()->getLeftChild() == node) {
            node->getParent()->setLeftChild(newnode);
        } else {
            node->getParent()->setRightChild(newnode);
        }
    }
    node->setParent(newnode);
//    node->setParent(newnode);
    node->updateParameters();
    newnode->updateParameters();
    return newnode;

}
template <class Key ,class Data>
AVLNode<Key,Data> *RankTree<Key,Data>::RotateLeft(AVLNode<Key,Data> *node)
{
    AVLNode<Key,Data>* newnode = node->getRightChild();
    node->setRightChild(newnode->getLeftChild());
    if (newnode->getRightChild() != nullptr){
        newnode->getLeftChild()->setParent(node);
    }
    newnode->setLeftChild(node);
    newnode->setParent(node->getParent());
    if (node->getParent() != nullptr) {
        if (node->getParent()->getLeftChild() == node) {
            node->getParent()->setLeftChild(newnode);
        } else {
            node->getParent()->setRightChild(newnode);
        }
    }
    node->setParent(newnode);
//    node->setParent(newnode);
    node->updateParameters();
    newnode->updateParameters();
    return newnode;

}
template <class Key ,class Data>
AVLNode<Key,Data>  *RankTree<Key,Data>::RollingRR(AVLNode<Key,Data>* node){
    return RotateRight(node);
}

template <class Key ,class Data>
AVLNode<Key,Data>  *RankTree<Key,Data>::RollingLL(AVLNode<Key,Data>* node){
    return RotateLeft(node);
}

template <class Key ,class Data>
AVLNode<Key,Data>  *RankTree<Key,Data>::RollingRL(AVLNode<Key,Data>* node)
{
    node->setRightChild(RotateRight(node->getRightChild()));
    return RotateLeft(node);
}

template <class Key ,class Data>
AVLNode<Key,Data>  *RankTree<Key,Data>::RollingLR(AVLNode<Key,Data>* node)
{    node->setLeftChild(RotateLeft(node->getLeftChild()));
    return RotateRight(node);
}

template <class Key ,class Data>
AVLNode<Key,Data> *RankTree<Key,Data>:: MakeBalance(AVLNode<Key,Data>* node)
{
    int BalanceFactor = RankTree<Key,Data>::BalanceFactor(node);
    if (BalanceFactor == 2)
    {
        if(RankTree<Key,Data>::BalanceFactor(node->getLeftChild()) > 0)
        {
            return RollingLL(node);
        }
        else if (RankTree<Key,Data>::BalanceFactor(node->getLeftChild()) < 0)
        {
            return RollingLR(node);
        }
    }
    else if (BalanceFactor == -2)
    {
        if(RankTree<Key,Data>::BalanceFactor(node->getRightChild()) > 0)
        {
            return RollingRL(node);
        }
        else if (RankTree<Key,Data>::BalanceFactor(node->getRightChild()) < 0)
        {
            return RollingRR(node);
        }
    }
    root->setParent(nullptr);
    return node;
}
template <class Key ,class Data>
AVLNode<Key,Data> *RankTree<Key,Data>::InsertNode( Key &key,  Data &data
                                                  , AVLNode<Key,Data> *node)
{
    if (node == nullptr) //tree is empty
    {
        AVLNode<Key,Data>* newElement = new AVLNode< Key,Data>(key,&data);
        if (newElement == nullptr){
            return nullptr;
        }
        newElement->setKey(key);
        newElement->setData(data);
        newElement->setHeight(0);
        if (root == nullptr){
            root = newElement;
        }
        return newElement;
    }
    else //tree not empty
    {
        if(key > node->getKey())
        {
            AVLNode<Key,Data>* newNode = InsertNode(key, data,node->getRightChild());
            newNode->setParent(node);
            node->setRightChild(newNode);
            node->getRightChild()->setParent(node);
        }
        else if(key < node->getKey())
        {
            AVLNode<Key,Data>* newNode = InsertNode(key, data,node->getLeftChild()
            );
            newNode->setParent(node);
            node->setLeftChild(newNode);
            node->getLeftChild()->setParent(node);
        }
    }
    node->updateParameters();
    node = MakeBalance(node);
    return node;
}
template <class Key ,class Data>
AVLNode<Key,Data> *RankTree<Key,Data>::DeleteNode(const Key &key, AVLNode<Key, Data> *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if(node->getKey() == key)

    {
        AVLNode<Key,Data>* tempNode;
        if ((node->getLeftChild() ) && (node->getRightChild() )) // two SONS
        {
            tempNode = node->getRightChild();
            while (tempNode->getLeftChild()) {
                tempNode = tempNode->getLeftChild();
            }
            tempNode->swap(node);
            node->setRightChild(DeleteNode(key,node->getRightChild()));
        }

        else if ((node->getLeftChild() == nullptr) || (node->getRightChild() == nullptr)) //ONE CHILD ONLY
        {
            if (node->getLeftChild())
            {
                tempNode = node->getLeftChild();
            }
            else
            {
                tempNode = node->getRightChild();
            }
            tempNode->setParent(node->getParent());
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
    else if (node->getKey() < key)
    {
        node->setRightChild(DeleteNode(key,node->getRightChild()));
    }
    else if (node->getKey() > key)
    {
        node->setLeftChild(DeleteNode(key,node->getLeftChild()));
    }
    node->updateParameters();
    return MakeBalance(node);
}
template <class Key ,class Data>
AVLNode<Key,Data> *RankTree<Key,Data>:: FindNode(const Key& key,AVLNode<Key,Data>* node){
    if (node == nullptr)
    {
        return nullptr;
    }
    if(key == node->getKey())
    {
        return node;
    }
    else if(key > node->getKey())
    {
        return FindNode(key,node->getRightChild());
    }
    else if(key < node->getKey())
    {
        return FindNode(key,node->getLeftChild());
    }
    else
    {
        return nullptr;
    }
}
template <class Key ,class Data>
void RankTree<Key,Data>::DeleteTree(AVLNode<Key,Data> *node)
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
StatusType RankTree<Key,Data>::Insert( Key &key,  Data &data
)
{

    if (this->Find(key))
    {
        return StatusType::FAILURE;
    }
    root = InsertNode(key, data
                      ,root);
    if(root == nullptr)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    size++;
    return StatusType::SUCCESS;
}
template <class Key ,class Data>
StatusType RankTree<Key,Data>::Remove(const Key &key)
{

    if (FindNode(key,root) == nullptr){
        return StatusType::FAILURE;
    }
    root = DeleteNode(key,root);
    size--;
    return StatusType::SUCCESS;

}
template <class Key ,class Data>
Data * RankTree<Key,Data>::Find(const Key& key)
{
    AVLNode<Key,Data>* tmp = FindNode(key,root);
    if (tmp == nullptr){
        return nullptr;
    }
    return tmp->getData()
    ;
}
template <class Key ,class Data>
bool RankTree<Key,Data>:: ElementInTree(const Key& key){
    if (root == nullptr){//tree empty
        return false;
    }
    if (this->FindNode(key,root) == nullptr){
        return false;
    }else{
        return true;
    }
}
template <class Key ,class Data>
int RankTree<Key,Data>::getSize() const {
    return size;
}




















#endif //STREAMINGDBA1_CPP_RankTree_H
