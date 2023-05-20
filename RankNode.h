//
// Created by soso_ on 5/15/2023.
//

#ifndef WET1_RankNode_H
#define WET1_RankNode_H

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


template<class Key, class Value>
class RankNode
{
public:
    
    Value *value;
    Key *key;
    NodeType m_type;


    RankNode *parent;
    RankNode *right_son;
    RankNode *left_son;

    int height;
    int BalanceFactor;

    RankNode(Value *value, Key *key);

    ~RankNode();

    Value *getvalue();

    void setRightChild(RankNode *node);

    void setLeftChild(RankNode *node);

    void setParent(RankNode *node);

    void setvalue(Value *value);

    int getBalanceFactor() const;

    int getHeight() const;

    Key *getKey() const;

    Value *getvalue() const;

    RankNode *getLeftChild() const;

    RankNode *getRightChild() const;

    RankNode *getParent() const;

    void updateParameters();

    bool operator<(RankNode &compare) const;

    bool operator==(RankNode &compare) const;

    bool operator>(RankNode &compare) const;

};

template<class Key, class Value>
bool RankNode<key, Value>::operator<(RankNode<Key, Value> &compare) const
{
    return this->key < compare.key;
}

template<class Key, class Value>
bool RankNode<Key, Value>::operator==(RankNode<key, Value> &compare) const
{
    return this->key == compare.key;
}

template<class Key, class Value>
bool RankNode<Key, Value>::operator>(RankNode<key, Value> &compare) const
{
    return this->key>compare.key;
}

template<class Key, class Value>
RankNode<key, Value> *RankNode<key, Value>::getLeftChild() const
{
    return left_son;
}

template<class Key, class Value>
RankNode<Key, Value> *RankNode<key, Value>::getRightChild() const
{
    return right_son;
}

template<class Key, class Value>
RankNode<Key, Value> *RankNode<key, Value>::getParent() const
{
    return parent;
}

template<class Key, class Value>
int RankNode<Key, Value>::getBalanceFactor() const
{
    return BalanceFactor;
}

template<class Key, class Value>
int RankNode<Key, Value>::getHeight() const
{
    return this->height;
}


template<class Key, class Value>
Key *RankNode<Key, Value>::getKey() const
{
    return key;
}

template<class Key, class Value>
Value *RankNode<Key, Value>::getvalue() const
{
    return value;
}

template<class Key, class Value>
RankNode<Key, Value>::RankNode(Value *value, Key *key)
{
/*check if key or value is valid*/
    if (key == NULL)
    {
        throw (AVL_Node_Exceptions("NULL KEY"));
    }
    if (value == NULL)
    {
        throw (AVL_Node_Exceptions("NULL value"));
    }
    Value *temp = new value();
    if (temp == NULL)
    {
        throw (AVL_Node_Exceptions("ALLOCATION_ERROR"));
    }
    /*copy the value */
    *temp = *value;
    this->value = temp;
    this->left_son = NULL;
    this->left_son = NULL;
    this->parent = NULL;
    this->BalanceFactor = 0;
    this->height = 0;
    this->m_type = NodeType::LEAF;

}

template<class Key, class Value>
RankNode<Key, Value>::~RankNode()
{
    if (key != NULL)
    {
        delete this->key;
        key = NULL;
    }
    if (value != NULL)
    {
        delete this->value;
        value = NULL;
    }
}

template<class Key, class Value>
void RankNode<Key, Value>::updateParameters()
{
    if (this->left_son != NULL && this->right_son != NULL)
    {
        m_type = NodeType::HAS_BOTH_CHILDREN;
    } else if (this->left_son != NULL && this->right_son == NULL)
    {
        m_type = NodeType::ONLY_LEFT_CHILD;
    } else if (this->left_son == NULL && this->right_son != NULL)
    {
        m_type = NodeType::ONLY_RIGHT_CHILD;
    } else
    {
        m_type = NodeType::LEAF;
    }
    switch (this->m_type)
    {
        case NodeType::HAS_BOTH_CHILDREN:

            if (this->left_son->height > this->right_son->height)
            {
                this->height = this->left_son + 1;
            } else
            {
                this->height = this->right_son + 1;
            }
            this->BalanceFactor = this->left_son->height - this->right_son->height;
            break;

        case NodeType::ONLY_RIGHT_CHILD:

            this->height = this->right_son->height + 1;
            this->BalanceFactor = -this->right_son->height;
            break;

        case NodeType::ONLY_LEFT_CHILD:
            this->height = this->left_son->height + 1;
            this - BalanceFactor = this->left_son->height;
            break;

        case NodeType::LEAF:
            this->height = 1;
            this->BalanceFactor = 0;
    }
}

template<class Key, class Value>
void RankNode<Key, Value>::setRightChild(RankNode *node)
{
    this->right_son = node;
    if (node != NULL)
    {
        node->setParent(this);
    }
    updateParameters();
}

template<class Key, class Value>
void RankNode<Key, Value>::setLeftChild(RankNode *node)
{
    this->left_son = node;
    if (node != NULL)
    {
        node->setParent(this);
    }
    updateParameters();
}

template<class Key, class Value>
void RankNode<Key, Value>::setParent(RankNode *node)
{
    this->parent = node;
    updateParameters();
}


#endif //WET1_RankNode_H
