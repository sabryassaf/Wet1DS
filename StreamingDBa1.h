// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_


#include "UserData.h"
#include "GroupData.h"
#include "MoviesRankingKey.h"
#include "MovieData.h"
#include "UserData.h"
#define MAXRATING 100

class streaming_database
{

private:
    RankTree<int, MovieData *> m_AllMoviesId; //the key would be movie id
    RankTree<MoviesRankingKey, MovieData *> m_AllMoviesRating; // the key according to ratings
    RankTree<MoviesRankingKey, MovieData *> m_COMEDY;
    RankTree<MoviesRankingKey, MovieData *> m_DRAMA;
    RankTree<MoviesRankingKey, MovieData *> m_ACTION;
    RankTree<MoviesRankingKey, MovieData *> m_FANTASY;
    RankTree<int, UserData *> m_AllUsers; //the key would be user id
    RankTree<int, GroupData *> m_AllGroups; //the key would be group id
    StatusType UpdateRatingsMoviesTrees(int movieId, MovieData *movieData, double added_rating, int added_views);


public:
    // <DO-NOT-MODIFY> {

    streaming_database();

    virtual ~streaming_database();

    StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);

    StatusType remove_movie(int movieId);

    StatusType add_user(int userId, bool isVip);

    StatusType remove_user(int userId);

    StatusType add_group(int groupId);

    StatusType remove_group(int groupId);

    StatusType add_user_to_group(int userId, int groupId);

    StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId, int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);

    output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);

    output_t<int> get_group_recommendation(int groupId);

    // } </DO-NOT-MODIFY>

};

#endif // STREAMINGDBA1_H_
