//
// Created by halam on 22/05/2023.
//

#include "MovieData.h"

MovieData::MovieData()=default;

MovieData::MovieData(int MovieId, Genre genre, int Views, bool VipStatus) : m_id(MovieId), m_rating(0), m_movieGenre(genre),
                                                                 m_views(Views), m_vipStatus(VipStatus),m_raters(0)
{

}

MovieData::MovieData(int ratings, int MovieId, Genre genre, int Views, bool VipStatus) : m_id(MovieId), m_rating(ratings),
                                                                              m_movieGenre(genre),
                                                                              m_views(Views),
                                                                              m_vipStatus(VipStatus),m_raters(0)
{

}

MovieData::~MovieData() = default;


void MovieData:: UpdateMovieViewer(int i)
{
    this->m_views += i;
}

double MovieData:: UpdateMovieRating(int i)
{
    double add= (m_rating*m_raters+i)/(m_raters+1)- m_rating;
    m_rating=(m_rating*m_raters+i)/(m_raters+1);
    m_raters+=1;
    return add;
}

double MovieData::getMovieRating() const
{
    return m_rating;
}

int MovieData::getMovieViews() const
{
    return m_views;
}

Genre MovieData::getMovieGenre() const
{
    return m_movieGenre;
}

int MovieData:: getId() const
{
    return m_id;
}

bool MovieData:: getMovieStatus() const
{
    return m_vipStatus;
}

