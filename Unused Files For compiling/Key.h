//
// Created by soso_ on 5/16/2023.
//


#ifndef WET1_KEY_H
#define WET1_KEY_H

#include <exception>
#include <string>

class Key_Type_Exceptions : public std::exception
{
    std::string m_message;
public:
    explicit Key_Type_Exceptions(const std::string &message) : m_message(message)
    {}

    const std::string &what()
    {
        return m_message;
    }
};

class MovieOrderById
{
    int m_id;
    int m_rating;
    int m_viewers;
public:
    MovieOrderById(int id, int views) : m_id(id), m_rating(0), m_viewers(views)
    {}

    bool operator<(const MovieOrderById &other) const
    {
        const MovieOrderById *otherMovie = dynamic_cast<const MovieOrderById *>(&other);
        if (otherMovie != nullptr)
        {
            return this->m_id < otherMovie->m_id;
        } else
        {
            throw (Key_Type_Exceptions("The Data Types Aren't comparable "));
        }

    }
};

class MovieOrderByRating
{
    int m_id;
    int m_rating;
    int m_viewers;
public:
    MovieOrderByRating(int id, int views) : m_id(id), m_rating(0), m_viewers(views)
    {}

    bool operator<(const MovieOrderByRating &other) const
    {
        const MovieOrderByRating *otherMovie = dynamic_cast<const MovieOrderByRating *>(&other);
        if (otherMovie != nullptr)
        {
            if (this->m_rating > otherMovie->m_rating)
            {
                return true;
            } else if (this->m_rating < otherMovie->m_rating)
            {
                return false;
            } else
            {
                if (this->m_viewers > otherMovie->m_viewers)
                {
                    return true;
                } else if (this->m_viewers < otherMovie->m_viewers)
                {
                    return false;
                } else
                {
                    return this->m_id < otherMovie->m_id;
                }
            }

        } else
        {
            throw (Key_Type_Exceptions("The Data Types Aren't comparable "));
        }

    }
};

//
//class UserId : public Key
//{
//public:
//    UserId(int id) : Key(id)
//    {}
//
//    bool operator<(const Key &other) const override
//    {
//        const UserId *otherUser = dynamic_cast<const UserId *>(&other);
//        if (otherUser != nullptr)
//        {
//            return this->m_id < otherUser->m_id;
//        } else
//        {
//            throw (Key_Type_Exceptions("The Data Types Aren't comparable "));
//        }
//
//    }
//
//    bool operator==(const Key &other) const override
//    {
//        const UserId *otherUser = dynamic_cast<const UserId *>(&other);
//        if (otherUser != nullptr)
//        {
//            return this->m_id == otherUser->m_id;
//        } else
//        {
//            throw (Key_Type_Exceptions("The Data Types Aren't comparable "));
//        }
//
//    }
//
//    bool operator>(const Key &other) const override
//    {
//        const UserId *otherUser = dynamic_cast<const UserId *>(&other);
//        if (otherUser != nullptr)
//        {
//            return this->m_id > otherUser->m_id;
//        } else
//        {
//            throw (Key_Type_Exceptions("The Data Types Aren't comparable "));
//        }
//
//    }
//};

#endif //WET1_KEY_H
