//
// Created by soso_ on 5/16/2023.
//

#ifndef WET1_DATA_H
#define WET1_DATA_H

#include "wet1util.h"

class DATA_Type_Exceptions : public std::exception
{
    std::string m_message;
public:
    explicit DATA_Type_Exceptions(const std::string &message) : m_message(message)
    {}

    const std::string &what()
    {
        return m_message;
    }
};

class Data
{
protected:
    int m_id;
public:
    Data(int id) : m_id(id)
    {}

    virtual ~Data() = 0;

    virtual int getId() const
    {
        return this->m_id;
    }
};


class User : public Data
{
private:
    int m_aloneViews[5];
    int m_groupViews[5];
    bool m_vip;
    bool m_inGroup;

public:
    User(int Id, bool Status) : Data(Id), m_vip(Status), m_inGroup(false)
    {
        for (int i = 0; i < 5; i++)
        {
            m_aloneViews[i] = 0;
            m_groupViews[i] = 0;
        }
    }

    ~User() = default;

};

class Movie : public Data
{
private:
    int m_rating;
    Genre m_movieGenre;
    int m_views;
    bool m_vipStatus;
public:
    Movie(int MovieId, Genre genre, int Views, bool VipStatus) : Data(MovieId), m_rating(0), m_movieGenre(genre),
                                                                 m_views(Views), m_vipStatus(VipStatus)
    {

    }

    ~Movie() = default;

    int getMovieRating() const
    {
        return m_rating;
    }

    int getMovieViews() const
    {
        return m_views;
    }

    int getMovieId() const
    {
        return m_id;
    }

};

#endif //WET1_DATA_H
