//
// Created by halam on 22/05/2023.
//

#ifndef AVLNODE_H_MOVIEDATA_H
#define AVLNODE_H_MOVIEDATA_H


//#include "wet1util.h"
#include "RankTree.h"

class MovieData {
private:
    int m_id;
    double m_rating;
    Genre m_movieGenre;
    int m_views;
    bool m_vipStatus;
    int m_raters;

public:
    MovieData();
    MovieData(int MovieId, Genre genre, int Views, bool VipStatus);
    MovieData(int ratings, int MovieId, Genre genre, int Views, bool VipStatus);
    ~MovieData();
    void UpdateMovieViewer(int i);
    double UpdateMovieRating(int i);
    double getMovieRating() const;
    int getMovieViews() const;
    Genre getMovieGenre() const;
    int getId() const;
    bool getMovieStatus() const;
};

#endif //AVLNODE_H_MOVIEDATA_H
