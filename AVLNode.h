//
// Created by soso_ on 5/15/2023.
//

#ifndef WET1_AVLNODE_H
#define WET1_AVLNODE_H


enum struct NodeType
{
    HAS_BOTH_CHILDREN,
    LEAF,
    ONLY_LEFT_CHILD,
    ONLY_RIGHT_CHILD
};



template<class Key, class Data>
class AVLNode
{
    Key m_key;
    Data m_data;
    AVLNode *m_leftChild;
    AVLNode *m_rightChild;
    AVLNode *m_parent;
    int m_balanceFactor;
    int m_height;
    NodeType m_type;



public:
    AVLNode(Key key, Data data);

    AVLNode(AVLNode<Key, Data> &other);

    ~AVLNode();

    void setRightChild(AVLNode *node);

    void setLeftChild(AVLNode *node);

    void setParent(AVLNode *node);


    void setHeight(int i);


    int getBalanceFactor() const;

    int getHeight() const;

    Key getKey() const;

    Data getData() const;

    AVLNode *getLeftChild() const;

    AVLNode *getRightChild() const;

    AVLNode *getParent() const;

    void updateParameters();

    bool operator<(AVLNode &compare) const;

    bool operator==(AVLNode &compare) const;

    bool operator>(AVLNode &compare) const;

    void swap(AVLNode *node);

};

template<class Key, class Data>
void AVLNode<Key, Data>::swap(AVLNode *node)
{
    Key tempKey = this->m_key;
    this->m_key = node->m_key;
    node->m_key = tempKey;
    Data tempVal = this->m_data;
    this->m_data = node->m_data;
    node->m_data = tempVal;
}


template<class Key, class Data>
AVLNode<Key, Data>::AVLNode(AVLNode<Key, Data> &other)
{
    this->m_key = other.m_key;
    this->m_data = other.m_data;

    if (other.m_leftChild != nullptr)
    {
        this->m_leftChild = new AVLNode<Key, Data>(*other.m_leftChild);
    }
    if (other.m_rightChild != nullptr)
    {
        this->m_rightChild = new AVLNode<Key, Data>(*other.m_rightChild);
    }
}

template<class Key, class Data>
void AVLNode<Key, Data>::setHeight(int i)
{
    this->m_height = i;
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
    return m_leftChild;
}

template<class Key, class Data>
AVLNode<Key, Data> *AVLNode<Key, Data>::getRightChild() const
{
    return m_rightChild;
}

template<class Key, class Data>
AVLNode<Key, Data> *AVLNode<Key, Data>::getParent() const
{
    return m_parent;
}

template<class Key, class Data>
int AVLNode<Key, Data>::getBalanceFactor() const
{
    return m_balanceFactor;
}

template<class Key, class Data>
int AVLNode<Key, Data>::getHeight() const
{
    return m_height;
}

template<class Key, class Data>
Key AVLNode<Key, Data>::getKey() const
{
    return m_key;
}

template<class Key, class Data>
Data AVLNode<Key, Data>::getData() const
{
    return m_data;
}

template<class Key, class Data>
AVLNode<Key, Data>::AVLNode(Key key, Data data) :m_key(key),m_data(data),m_leftChild(nullptr),m_rightChild(nullptr),m_parent(
        nullptr),m_balanceFactor(0),m_height(0),m_type(NodeType::LEAF)
{
}

template<class Key, class Data>
AVLNode<Key, Data>::~AVLNode()=default;

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
            this->m_height = 0;
            this->m_balanceFactor = 0;
            break;
    }
}

template<class Key, class Data>
void AVLNode<Key, Data>::setRightChild(AVLNode *node)
{
    if (node == nullptr)
    {
        m_rightChild = nullptr;
        updateParameters();
        return;
    }
    this->m_rightChild = node;
    if (node)
    {
        node->setParent(this);
    }
    updateParameters();
}

template<class Key, class Data>
void AVLNode<Key, Data>::setLeftChild(AVLNode *node)
{
    if (node == nullptr)
    {
        m_leftChild = nullptr;
        updateParameters();
        return;
    }
    this->m_leftChild = node;
    if (node)
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

#endif //WET1_AVLNODE_H
