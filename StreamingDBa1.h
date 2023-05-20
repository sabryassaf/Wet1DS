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

#include "wet1util.h"
#include "AVLTree.h"
#include "Data.h"
#include "MoviesRankingKey.h"
class streaming_database {

private:
    AVLtree<int,MovieData*> m_AllMoviesId; //the key would be movie id
    AVLtree<MoviesRankingKey,MovieData*> m_AllMoviesRating; // the key according to ratings
    AVLtree<MoviesRankingKey,MovieData*>  m_COMEDY;
    AVLtree<MoviesRankingKey,MovieData*>  m_DRAMA;
    AVLtree<MoviesRankingKey,MovieData*>  m_ACTION;
    AVLtree<MoviesRankingKey,MovieData*>  m_FANTASY;
    AVLtree<int,UserData*> m_AllUsers; //the key would be user id
    AVLtree<int,GroupData*> m_AllGroups; //the key would be group id






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

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);

    output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);

    output_t<int> get_group_recommendation(int groupId);

    // } </DO-NOT-MODIFY>
    StatusType RatingsMoviesTrees(int movieId,MovieData* movieData, int added_rating,int added_views);

};

#endif // STREAMINGDBA1_H_
