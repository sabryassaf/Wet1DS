//
// Created by halam on 19/05/2023.
//

#ifndef DATA_H_MOVIESRANKINGKEY_H
#define DATA_H_MOVIESRANKINGKEY_H

class MoviesRankingKey{

private:
    int m_id;
    int m_rating;
    int m_viewers;
public:
    MoviesRankingKey(int m_id,int m_viewers);
    MoviesRankingKey() = default;
    MoviesRankingKey(const MoviesRankingKey& copy) =default;
    MoviesRankingKey& operator=(const MoviesRankingKey& copy) =default;
    ~MoviesRankingKey()=default;
    bool operator<(const MoviesRankingKey &other) const;
};

bool operator==(const MoviesRankingKey&,const MoviesRankingKey&);
bool operator!=(const MoviesRankingKey&,const MoviesRankingKey&);
bool operator<(const MoviesRankingKey& movie1,const MoviesRankingKey&);
bool operator<=(const MoviesRankingKey& movie1,const MoviesRankingKey& movie2);
bool operator>=(const MoviesRankingKey& movie1,const MoviesRankingKey& movie2);
bool operator>(const MoviesRankingKey& movie1,const MoviesRankingKey& movie2);




#endif //DATA_H_MOVIESRANKINGKEY_H
