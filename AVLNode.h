//
// Created by soso_ on 5/15/2023.
//

#ifndef WET1_AVLNODE_H
#define WET1_AVLNODE_H

#include <exception>
#include <string>

enum struct NodeType
{
    HAS_BOTH_CHILDREN,
    LEAF,
    ONLY_LEFT_CHILD,
    ONLY_RIGHT_CHILD
};

class AVL_Node_Exceptions : public std::exception
{
    std::string m_message;
public:
    explicit AVL_Node_Exceptions(const std::string &message) : m_message(message)
    {}

    const std::string &what()
    {
        return m_message;
    }
};


template<class Data, class Key>
class AVLNode
{
    Data *m_data;
    Key *m_key;
    NodeType m_type;


    AVLNode *m_parent;
    AVLNode *m_rightChild;
    AVLNode *m_leftChild;

    int m_height;
    int m_balanceFactor;

public:
    AVLNode(Data *data, Key *key);

    ~AVLNode();

    Data *getData();

    void setRightChild(AVLNode *node);

    void setLeftChild(AVLNode *node);

    void setParent(AVLNode *node);

    void setData(Data *data);

    int getBalanceFactor() const;

    int getHeight() const;

    Key *getKey() const;

    Data *getData() const;

    AVLNode *getLeftChild() const;

    AVLNode *getRightChild() const;

    AVLNode *getParent() const;

    void updateParameters();

    bool operator<(AVLNode &compare) const;

    bool operator==(AVLNode &compare) const;

    bool operator>(AVLNode &compare) const;

};

template<class Data, class Key>
bool AVLNode<Data, Key>::operator<(AVLNode<Data, Key> &compare) const
{
    return this->m_key < compare.m_key;
}

template<class Data, class Key>
bool AVLNode<Data, Key>::operator==(AVLNode<Data, Key> &compare) const
{
    return this->m_key == compare.m_key;
}

template<class Data, class Key>
bool AVLNode<Data, Key>::operator>(AVLNode<Data, Key> &compare) const
{
    return this->m_key>compare.m_key;
}

template<class Data, class Key>
AVLNode<Data, Key> *AVLNode<Data, Key>::getLeftChild() const
{
    return m_leftChild;
}

template<class Data, class Key>
AVLNode<Data, Key> *AVLNode<Data, Key>::getRightChild() const
{
    return m_rightChild;
}

template<class Data, class Key>
AVLNode<Data, Key> *AVLNode<Data, Key>::getParent() const
{
    return m_parent;
}

template<class Data, class Key>
int AVLNode<Data, Key>::getBalanceFactor() const
{
    return m_balanceFactor;
}

template<class Data, class Key>
int AVLNode<Data, Key>::getHeight() const
{
    return m_height;
}

template<class Data, class Key>
Key *AVLNode<Data, Key>::getKey() const
{
    return m_key;
}

template<class Data, class Key>
Data *AVLNode<Data, Key>::getData() const
{
    return m_data;
}

template<class Data, class Key>
AVLNode<Data, Key>::AVLNode(Data *data, Key *key)
{
/*check if key or data is valid*/
    if (key == NULL)
    {
        throw (AVL_Node_Exceptions("NULL KEY"));
    }
    if (data == NULL)
    {
        throw (AVL_Node_Exceptions("NULL Data"));
    }
    Data *temp = new Data();
    if (temp == NULL)
    {
        throw (AVL_Node_Exceptions("ALLOCATION_ERROR"));
    }
    /*copy the data */
    *temp = *data;
    this->m_data = temp;
    this->m_leftChild = NULL;
    this->m_leftChild = NULL;
    this->m_parent = NULL;
    this->m_balanceFactor = 0;
    this->m_height = 0;
    this->m_type = NodeType::LEAF;

}

template<class Data, class Key>
AVLNode<Data, Key>::~AVLNode()
{
    if (m_key != NULL)
    {
        delete this->m_key;
        m_key = NULL;
    }
    if (m_data != NULL)
    {
        delete this->data;
        m_data = NULL;
    }
}

template<class Data, class Key>
void AVLNode<Data, Key>::updateParameters()
{
    if (this->m_leftChild != NULL && this->m_rightChild != NULL)
    {
        m_type = NodeType::HAS_BOTH_CHILDREN;
    } else if (this->m_leftChild != NULL && this->m_rightChild == NULL)
    {
        m_type = NodeType::ONLY_LEFT_CHILD;
    } else if (this->m_leftChild == NULL && this->m_rightChild != NULL)
    {
        m_type = NodeType::ONLY_RIGHT_CHILD;
    } else
    {
        m_type = NodeType::LEAF;
    }
    switch (this->m_type)
    {
        case NodeType::HAS_BOTH_CHILDREN:

            if (this->m_leftChild->m_height > this->m_rightChild->m_height)
            {
                this->m_height = this->m_leftChild + 1;
            } else
            {
                this->m_height = this->m_rightChild + 1;
            }
            this->m_balanceFactor = this->m_leftChild->m_height - this->m_rightChild->m_height;
            break;

        case NodeType::ONLY_RIGHT_CHILD:

            this->m_height = this->m_rightChild->m_height + 1;
            this->m_balanceFactor = -this->m_rightChild->m_height;
            break;

        case NodeType::ONLY_LEFT_CHILD:
            this->m_height = this->m_leftChild->m_height + 1;
            this - m_balanceFactor = this->m_leftChild->m_height;
            break;

        case NodeType::LEAF:
            this->m_height = 1;
            this->m_balanceFactor = 0;
            break;
        default:
            this->m_height=0;
            this->m_balanceFactor=0;
            break;
    }
}

template<class Data, class Key>
void AVLNode<Data, Key>::setRightChild(AVLNode *node)
{
    if (node== nullptr){
        m_rightChild = nullptr;
        updateParameters();
        return;
    }
    this->m_rightChild = node;
    if (node != NULL)
    {
        node->setParent(this);
    }
    updateParameters();
}

template<class Data, class Key>
void AVLNode<Data, Key>::setLeftChild(AVLNode *node)
{
    if (node== nullptr){
        m_leftChild = nullptr;
        updateParameters();
        return;
    }
    this->m_leftChild = node;
    if (node != NULL)
    {
        node->setParent(this);
    }
    updateParameters();
}

template<class Data, class Key>
void AVLNode<Data, Key>::setParent(AVLNode *node)
{
    this->m_parent = node;
    updateParameters();
}


#endif //WET1_AVLNODE_H
