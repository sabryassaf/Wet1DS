//
// Created by soso_ on 5/16/2023.
//


#ifndef WET1_KEY_H
#define WET1_KEY_H

#include <exception>
#include <string>

enum struct OrderRule
{
    ID, RATING
};

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

class Key
{
protected:
    int m_id;
public:
    Key(int id) : m_id(id)
    {}

    int getId() const
    {
        return m_id;
    }

    virtual bool operator<(const Key &other) const = 0;

    virtual bool operator==(const Key &other) const = 0;

    virtual bool operator>(const Key &other) const = 0;

};


class UserId : public Key
{
public:
    UserId(int id) : Key(id)
    {}

    bool operator<(const Key &other) const override
    {
        const UserId *otherUser = dynamic_cast<const UserId *>(&other);
        if (otherUser != nullptr)
        {
            return this->m_id < otherUser->m_id;
        } else
        {
            throw (Key_Type_Exceptions("The Data Types Aren't comparable "));
        }

    }

    bool operator==(const Key &other) const override
    {
        const UserId *otherUser = dynamic_cast<const UserId *>(&other);
        if (otherUser != nullptr)
        {
            return this->m_id == otherUser->m_id;
        } else
        {
            throw (Key_Type_Exceptions("The Data Types Aren't comparable "));
        }

    }

    bool operator>(const Key &other) const override
    {
        const UserId *otherUser = dynamic_cast<const UserId *>(&other);
        if (otherUser != nullptr)
        {
            return this->m_id > otherUser->m_id;
        } else
        {
            throw (Key_Type_Exceptions("The Data Types Aren't comparable "));
        }

    }
};

class MovieId : public Key
{
    int m_rating;
    int m_viewers;
    OrderRule m_rule;
public:
    MovieId(int id, OrderRule &rule) : Key(id), m_rating(0), m_viewers(0), m_rule(rule)
    {}

    bool operator<(const Key &other) const override
    {
        const MovieId *otherMovie = dynamic_cast<const MovieId *>(&other);
        if (otherMovie != nullptr)
        {
            switch (this->m_rule)
            {
                case OrderRule::ID:
                    return this->m_id < otherMovie->m_id;
                case OrderRule::RATING:
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
            }

        } else
        {
            throw (Key_Type_Exceptions("The Data Types Aren't comparable "));
        }

    }
};

#endif //WET1_KEY_H
