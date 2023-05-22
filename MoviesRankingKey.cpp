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
MoviesRankingKey:: MoviesRankingKey(const MoviesRankingKey& copy){
    this->m_rating=copy.getRATINGS();
    this->m_viewers=copy.getVIEWS();
    this->m_id=copy.getID();
}

     int MoviesRankingKey:: getID()const {
         return m_id;
}
    int MoviesRankingKey:: getVIEWS()const{
        return m_viewers;
}
     int MoviesRankingKey:: getRATINGS()const {
         return m_rating;


     }

bool MoviesRankingKey:: operator<(MoviesRankingKey& other) const {
    return ::operator<(*this, other);
}

bool MoviesRankingKey::operator>(MoviesRankingKey& other) const {
    return ::operator<(other, *this);
}

bool operator>(const MoviesRankingKey& movie1,const MoviesRankingKey& movie2)
{
    return ::operator<(movie2, movie1);
}

bool operator<(const MoviesRankingKey& movie1, const MoviesRankingKey& movie2){

        if(movie1.getRATINGS()==movie2.getRATINGS()){
            if(movie1.getVIEWS()==movie2.getVIEWS()){
                return movie1.getID()>movie2.getID();
            }
            return movie1.getVIEWS()>movie2.getVIEWS();
        }
        return  movie1.getRATINGS()>movie2.getRATINGS();
    }

bool operator==(const MoviesRankingKey& movie1, const MoviesRankingKey& movie2)
{
    return ((movie1.getID()==movie2.getID()) && (movie1.getVIEWS()==movie2.getVIEWS()) && (movie1.getRATINGS()==movie2.getRATINGS()));
}
