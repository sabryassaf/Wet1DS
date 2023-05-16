//
// Created by soso_ on 5/15/2023.
//

#ifndef WET1_AVLNODE_H
#define WET1_AVLNODE_H

#include <exception>
#include <string>
#include "Data.h"

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


template<class Data>
class AVLNode
{
protected:
    Data *m_data;
    NodeType m_type;


    AVLNode *m_parent;
    AVLNode *m_rightChild;
    AVLNode *m_leftChild;

    int m_height;
    int m_balanceFactor;

public:
    AVLNode(Data *data);

    ~AVLNode();

    Data *getData();

    void setRightChild(AVLNode *node);

    void setLeftChild(AVLNode *node);

    void setParent(AVLNode *node);

    void setData(Data *data);

    int getBalanceFactor() const;

    int getHeight() const;


    Data *getData() const;

    AVLNode *getLeftChild() const;

    AVLNode *getRightChild() const;

    AVLNode *getParent() const;

    void updateParameters();

    virtual int compareNodes(const AVLNode &other) const = 0;

};

template<class Data>
class NodeByID : public AVLNode<Data>
{
    int compareNodes(const AVLNode<Data> &other) const override
    {
        const NodeByID<Data> *derived = dynamic_cast<const NodeByID<Data> *>(&other);
        if (derived != nullptr)
        {
            return this->m_data->m_id - derived->getData()->m_id;
        } else
        {
            throw (DATA_Type_Exceptions("The Data Types Aren't comparable "));
        }
    }

};

class MovieByRating : public AVLNode<Movie>
{
    int compareNodes(const AVLNode<Movie> &other) const override
    {
        const MovieByRating *derived = dynamic_cast<const MovieByRating *>(&other);
        if (derived != nullptr)
        {
            int ratingDifference;
            ratingDifference = this->m_data->getMovieRating() - derived->getData()->getMovieRating();
            if (ratingDifference > 0)
            {
                return 1;
            }
            if (ratingDifference < 0)
            {
                return -1;

            } else
            {
                int viewDifference;
                viewDifference = this->m_data->getMovieViews() - derived->getData()->getMovieViews();
                if (viewDifference > 0)
                {
                    return 1;

                }
                if (viewDifference < 0)
                {
                    return -1;
                } else
                {
                    return derived->getData()->getMovieId() - this->m_data->getId();
                }
            }
        } else
        {
            throw AVL_Node_Exceptions("The Data Types Aren't comparable");
        }
    }
};


template<class Data>
AVLNode<Data> *AVLNode<Data>::getLeftChild() const
{
    return m_leftChild;
}

template<class Data>
AVLNode<Data> *AVLNode<Data>::getRightChild() const
{
    return m_rightChild;
}

template<class Data>
AVLNode<Data> *AVLNode<Data>::getParent() const
{
    return m_parent;
}

template<class Data>
int AVLNode<Data>::getBalanceFactor() const
{
    return m_balanceFactor;
}

template<class Data>
int AVLNode<Data>::getHeight() const
{
    return m_height;
}

template<class Data>
Data *AVLNode<Data>::getData() const
{
    return m_data;
}

template<class Data>
AVLNode<Data>::AVLNode(Data *data)
{
/*check if key or data is valid*/
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

template<class Data>
AVLNode<Data>::~AVLNode()
{
    if (m_data != NULL)
    {
        delete this->data;
        m_data = NULL;
    }
}

template<class Data>
void AVLNode<Data>::updateParameters()
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
    }
}

template<class Data>
void AVLNode<Data>::setRightChild(AVLNode *node)
{
    this->m_rightChild = node;
    if (node != NULL)
    {
        node->setParent(this);
    }
    updateParameters();
}

template<class Data>
void AVLNode<Data>::setLeftChild(AVLNode *node)
{
    this->m_leftChild = node;
    if (node != NULL)
    {
        node->setParent(this);
    }
    updateParameters();
}

template<class Data>
void AVLNode<Data>::setParent(AVLNode *node)
{
    this->m_parent = node;
    updateParameters();
}


#endif //WET1_AVLNODE_H
