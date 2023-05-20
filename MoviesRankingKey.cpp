//
// Created by halam on 19/05/2023.
//
#include <exception>
#include <string>
#include "MoviesRankingKey.h"
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

MoviesRankingKey:: MoviesRankingKey(int id, int views) : m_id(id),m_rating(0),m_viewers(views){}
MoviesRankingKey:: MoviesRankingKey(int id,int rating,int views) : m_id(id), m_rating(rating),m_viewers(views)
{}

bool MoviesRankingKey:: operator<(const MoviesRankingKey &other) const
{
    const MoviesRankingKey *otherMovie = dynamic_cast<const MoviesRankingKey *>(&other);
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

#include "MoviesRankingKey.h"
