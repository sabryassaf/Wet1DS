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


template<class Key, class Data>
class AVLNode
{
    Data *m_data;
    Key m_key;
    NodeType m_type;


    AVLNode *m_parent;
    AVLNode *m_rightChild;
    AVLNode *m_leftChild;

    int m_height;
    int m_balanceFactor;

public:
    AVLNode(Key key, Data *data);

    AVLNode( AVLNode<Key, Data>& other);

    ~AVLNode();

    Data *getData();

    void setRightChild(AVLNode *node);

    void setLeftChild(AVLNode *node);

    void setParent(AVLNode *node);

    void setData(Data & data);

    void setHeight(int i);

    void setKey(Key key);

    int getBalanceFactor() const;

    int getHeight() const;

    Key getKey() const;

    Data *getData() const;

    AVLNode *getLeftChild() const;

    AVLNode *getRightChild() const;

    AVLNode *getParent() const;

    void updateParameters();

    bool operator<(AVLNode &compare) const;

    bool operator==(AVLNode &compare) const;

    bool operator>(AVLNode &compare) const;

    void swap(AVLNode* node);

};

template <class Key ,class Data>
void AVLNode<Key,Data>::swap(AVLNode* node){
    Key tempKey = this->m_key;
    Data * tempVal = this->m_data;
    this->m_key = node->m_key;
    this->m_data = node->m_data;
    node->m_key = tempKey;
    node->m_data = tempVal;
}


template <class Key, class Data>
AVLNode<Key, Data>::AVLNode( AVLNode<Key, Data>& other) {
    this->m_key = other.m_key;
    this->m_data = other.m_data;

    if (other.m_leftChild != nullptr) {
        this->m_leftChild = new AVLNode<Key, Data>(*other.m_leftChild);
    }
    if (other.m_rightChild != nullptr) {
        this->m_rightChild = new AVLNode<Key, Data>(*other.m_rightChild);
    }
}

template<class Key, class Data>
void AVLNode<Key, Data>::setHeight(int i){
    this->m_height = i;
}

template<class Key, class Data>
void AVLNode<Key, Data>::setKey(Key key)
{
    this->m_key = key;
}

template<class Key, class Data>
void AVLNode<Key, Data>::setData(Data & data)
{
    this->m_data = new Data(data);
}

template<class Key, class Data>
bool AVLNode<Key, Data>::operator<(AVLNode<Key, Data> &compare) const
{
    return this->m_key < compare.m_key;
}

template<class Key, class Data>
bool AVLNode<Key, Data>::operator==(AVLNode<Key, Data> &compare) const
{
    return this->m_key == compare.m_key;
}

template<class Key, class Data>
bool AVLNode<Key, Data>::operator>(AVLNode<Key, Data> &compare) const
{
    return this->m_key > compare.m_key;
}

template<class Key, class Data>
AVLNode<Key, Data> *AVLNode<Key, Data>::getLeftChild() const
{
    if (this== nullptr)
    {
        return 0;
    }
    else{
        return m_leftChild;
    }
}

template<class Key, class Data>
AVLNode<Key, Data> *AVLNode<Key, Data>::getRightChild() const
{
    if (this== nullptr)
    {
        return 0;
    }
    else{
    return m_rightChild;
    }
}

template<class Key, class Data>
AVLNode<Key, Data> *AVLNode<Key, Data>::getParent() const {
    if (this == nullptr) {
        return 0;
    } else {
        return m_parent;
    }
}
template<class Key, class Data>
int AVLNode<Key, Data>::getBalanceFactor() const
{
    if (this== nullptr)
    {
        return 0;
    }
    else{
        return m_balanceFactor;
    }
}

template<class Key, class Data>
int AVLNode<Key, Data>::getHeight() const
{
    if (this== nullptr)
    {
        return 0;
    }
    else{
        return m_height;
    }
}

template<class Key, class Data>
Key AVLNode<Key, Data>::getKey() const
{
    if (this== nullptr)
    {
        return -1;
    }
    else{
        return m_key;
    }
}

template<class Key, class Data>
Data *AVLNode<Key, Data>::getData() const
{
    return m_data;
}

template<class Key, class Data>
AVLNode<Key, Data>::AVLNode(Key key, Data *data)
{
/*check if key or data is valid*/
    if (key == NULL)
    {
        throw (AVL_Node_Exceptions("NULL KEY"));
    }
    if (data == nullptr)
    {
        throw (AVL_Node_Exceptions("NULL Data"));
    }
    Data *temp = new Data();
    if (temp == nullptr)
    {
        throw (AVL_Node_Exceptions("ALLOCATION_ERROR"));
    }
    /*copy the data */
    *temp = *data;
    this->m_key = key;
    this->m_data = temp;
    this->m_leftChild = nullptr;
    this->m_rightChild = nullptr;
    this->m_parent = nullptr;
    this->m_balanceFactor = 0;
    this->m_height = 0;
    this->m_type = NodeType::LEAF;

}

template<class Key, class Data>
AVLNode<Key, Data>::~AVLNode()
{
    if (m_data != nullptr)
    {
        delete this->getData();
        m_data = nullptr;
    }
}

template<class Key, class Data>
void AVLNode<Key, Data>::updateParameters()
{
    if (this->m_leftChild != nullptr && this->m_rightChild != nullptr)
    {
        m_type = NodeType::HAS_BOTH_CHILDREN;
    } else if (this->m_leftChild != nullptr && this->m_rightChild == nullptr)
    {
        m_type = NodeType::ONLY_LEFT_CHILD;
    } else if (this->m_leftChild == nullptr && this->m_rightChild != nullptr)
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
                this->m_height = this->m_leftChild->getHeight() + 1;
            } else
            {
                this->m_height = this->m_rightChild->getHeight() + 1;
            }
            this->m_balanceFactor = this->m_leftChild->m_height - this->m_rightChild->m_height;
            break;

        case NodeType::ONLY_RIGHT_CHILD:

            this->m_height = this->m_rightChild->m_height + 1;
            this->m_balanceFactor = -this->m_rightChild->m_height;
            break;

        case NodeType::ONLY_LEFT_CHILD:
            this->m_height = this->m_leftChild->m_height + 1;
            this->m_balanceFactor = this->m_leftChild->m_height;
            break;

        case NodeType::LEAF:
            this->m_height = 0;
            this->m_balanceFactor = 0;
            break;
        default:
            this->m_height=0;
            this->m_balanceFactor=0;
            break;
    }
}

template<class Key, class Data>
void AVLNode<Key, Data>::setRightChild(AVLNode *node)
{
    if (node== nullptr){
        m_rightChild = nullptr;
        updateParameters();
        return;
    }
    this->m_rightChild = node;
    if (node != nullptr)
    {
        node->setParent(this);
    }
    updateParameters();
}

template<class Key, class Data>
void AVLNode<Key, Data>::setLeftChild(AVLNode *node)
{
    if (node== nullptr){
        m_leftChild = nullptr;
        updateParameters();
        return;
    }
    this->m_leftChild = node;
    if (node != nullptr)
    {
        node->setParent(this);
    }
    updateParameters();
}

template<class Key, class Data>
void AVLNode<Key, Data>::setParent(AVLNode *node)
{
    this->m_parent = node;
    this->updateParameters();
}

template<class Key, class Data>
Data *AVLNode<Key, Data>::getData() {
    return this->m_data;
}


#endif //WET1_AVLNODE_H
