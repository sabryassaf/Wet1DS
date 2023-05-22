#include "StreamingDBa1.h"

streaming_database::streaming_database()
        : m_AllMoviesId(), m_AllMoviesRating(), m_COMEDY(), m_DRAMA(), m_ACTION(), m_FANTASY(), m_AllUsers(),
          m_AllGroups()
{

    // TODO: Your code goes here
}

streaming_database::~streaming_database()
{
    // TODO: Your code goes here
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    StatusType status = StatusType::FAILURE;

    if (movieId <= 0 || genre == Genre::NONE || views < 0)
    {
        return StatusType::INVALID_INPUT;
    }

    MovieData *new_movie_data = new MovieData(movieId, genre, views, vipOnly);
    if (!new_movie_data)
        return StatusType::ALLOCATION_ERROR;
    if (m_AllMoviesId.Insert(movieId, new_movie_data) == StatusType::SUCCESS)
    {
        MoviesRankingKey new_movie_key(movieId, views);
        if (m_AllMoviesRating.Insert(new_movie_key, new_movie_data) == StatusType::SUCCESS)
        {

            switch (genre)
            {
                case Genre::COMEDY:
                    status = m_COMEDY.Insert(new_movie_key, new_movie_data);
                    break;
                case Genre::DRAMA:
                    status = m_DRAMA.Insert(new_movie_key, new_movie_data);
                    break;
                case Genre::ACTION:
                    status = m_ACTION.Insert(new_movie_key, new_movie_data);
                    break;
                case Genre::FANTASY:
                    status = m_FANTASY.Insert(new_movie_key, new_movie_data);
                    break;
            }

            if (status == StatusType::SUCCESS)
            {
                return StatusType::SUCCESS;

            }
        }
    }
    delete new_movie_data;
    return StatusType::FAILURE;

}

StatusType streaming_database::remove_movie(int movieId)
{
    StatusType status = StatusType::FAILURE;;
    if (movieId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    MovieData *removeMovie = m_AllMoviesId.Find(movieId);
    if (!removeMovie)
    {
        return StatusType::FAILURE;
    }
    MoviesRankingKey key(movieId, removeMovie->getMovieRating(), removeMovie->getMovieViews());

    if (m_AllMoviesId.Remove(movieId) == StatusType::SUCCESS && m_AllMoviesRating.Remove(key) == StatusType::SUCCESS)
    { // removes the node object from the tree
        switch (removeMovie->getMovieGenre())
        {
            case Genre::COMEDY:
                status = m_COMEDY.Remove(key);
                break;
            case Genre::DRAMA:
                status = m_DRAMA.Remove(key);
                break;
            case Genre::ACTION:
                status = m_ACTION.Remove(key);
                break;
            case Genre::FANTASY:
                status = m_FANTASY.Remove(key);
                break;
        }
        if (status == StatusType::SUCCESS)
        {
            delete removeMovie; //frees the memory allocated for the MovieData object in the data,
            return StatusType::SUCCESS;

        }
    }
    return StatusType::FAILURE;

}


StatusType streaming_database::add_user(int userId, bool isVip)
{
    if (userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    UserData *newUser = new UserData(userId, isVip);
    if (!newUser)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    if (m_AllUsers.Insert(userId, newUser) == StatusType::SUCCESS)
    {

        return StatusType::SUCCESS;
    }
    delete newUser;
    return StatusType::FAILURE;
}

StatusType streaming_database::remove_user(int userId)
{
    if (userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    UserData *removeUser = m_AllUsers.Find(userId);
    if (!removeUser)
    {
        return StatusType::FAILURE;
    }
    if (m_AllUsers.Remove(userId) == StatusType::SUCCESS)
    {
        if (removeUser->getGroupId() > 0)
        { //he is in a group
            GroupData *userGroup = m_AllGroups.Find(removeUser->getGroupId());
            if (userGroup->remove_user(userId) == StatusType::SUCCESS)
            {
                delete removeUser;
                return StatusType::SUCCESS;
            }
        } else
        {
            delete removeUser;
            return StatusType::SUCCESS;
        }
    }
    return StatusType::FAILURE;

}

StatusType streaming_database::add_group(int groupId)
{
    if (groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    GroupData *newGroup = new GroupData(groupId);
    if (!newGroup)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    if (m_AllGroups.Insert(groupId, newGroup) == StatusType::SUCCESS)
    {

        return StatusType::SUCCESS;
    }
    delete newGroup;
    return StatusType::FAILURE;
}


StatusType streaming_database::remove_group(int groupId)
{
    if (groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    // to update all the group users with id = 0;
    if (m_AllUsers.Remove(groupId) == StatusType::SUCCESS)
    {
        GroupData *removeGroup = m_AllGroups.Find(groupId);
        delete removeGroup;
        return StatusType::SUCCESS;


    }
    return StatusType::FAILURE;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if (groupId <= 0 || userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if (m_AllUsers.Find(userId) == nullptr || m_AllGroups.Find(groupId) == nullptr)
    {
        return StatusType::FAILURE;
    }
    // check if user isn't already in a group
    UserData *addUser = m_AllUsers.Find(userId);
    GroupData *toGroup = m_AllGroups.Find(groupId);
    return toGroup->add_user(userId, addUser);
}

StatusType streaming_database::user_watch(int userId, int movieId)
{

    if (movieId <= 0 || userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    UserData *watchUser = m_AllUsers.Find(userId);
    MovieData *watchMovie = m_AllMoviesId.Find(movieId);
    if (watchUser == nullptr || watchMovie == nullptr)
        return StatusType::FAILURE;

    if (watchMovie->getMovieStatus())
    {
        if (!watchUser->getVipStatus())
            return StatusType::FAILURE;
    }
    if (watchUser->getGroupId() <= 0) // not in a group
    {
        watchUser->updateAloneViews(watchMovie->getMovieGenre());
    }
    watchMovie->UpdateMovieViewsode(1);
    //***************updating tree views************//
    return UpdateRatingsMoviesTrees(movieId, watchMovie, 0, 1);


}

StatusType streaming_database::group_watch(int groupId, int movieId)
{
    if (movieId <= 0 || groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    GroupData *watchGroup = m_AllGroups.Find(groupId);
    MovieData *watchMovie = m_AllMoviesId.Find(movieId);
    if (watchGroup == nullptr || watchMovie == nullptr)
        return StatusType::FAILURE;
    if (watchMovie->getMovieStatus())
    {
        if (!watchGroup->getVipStatus())
            return StatusType::FAILURE;
    }
    watchGroup->updateTogtherViews(watchMovie);
    return UpdateRatingsMoviesTrees(movieId, watchMovie, 0, watchGroup->getGroupsize());
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{

    switch (genre)
    {
        case Genre::COMEDY:
            return m_COMEDY.getSize();
        case Genre::DRAMA:
            return m_DRAMA.getSize();
        case Genre::ACTION:
            return m_ACTION.getSize();
        case Genre::FANTASY:
            return m_FANTASY.getSize();
        case Genre::NONE:
            return m_AllMoviesRating.getSize();

    }
    return StatusType::FAILURE;

}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    int arrSize = 0;
    if (!output)
        return StatusType::INVALID_INPUT;
    arrSize = get_all_movies_count(genre).ans();
    if (arrSize <= 0)
        return StatusType::FAILURE;

    MovieData **arr = new MovieData *[arrSize];
    if (!arr)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    switch (genre)
    {
        case Genre::COMEDY:
            m_COMEDY.BuildInOrderArray(arr);
            break;
        case Genre::DRAMA:
            m_DRAMA.BuildInOrderArray(arr);
            break;
        case Genre::ACTION:
            m_ACTION.BuildInOrderArray(arr);
            break;
        case Genre::FANTASY:
            m_FANTASY.BuildInOrderArray(arr);
            break;
        case Genre::NONE:
            m_AllMoviesRating.BuildInOrderArray(arr);
            break;

    }
    for (int i = 0; i < arrSize; i++)
    {
        output[i] = arr[i]->getId();
    }
    delete[] arr;
    return StatusType::SUCCESS;

}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    if (userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    UserData *watchUser = m_AllUsers.Find(userId);
    if (!watchUser)
    {
        return StatusType::FAILURE;
    }

    switch (genre)
    {
        case Genre::COMEDY:
            return watchUser->getNumViewsAlone(0) + watchUser->getNumViewsAlone(0);
        case Genre::DRAMA:
            return watchUser->getNumViewsAlone(1) + watchUser->getNumViewsAlone(1);
        case Genre::ACTION:
            return watchUser->getNumViewsAlone(2) + watchUser->getNumViewsAlone(2);
        case Genre::FANTASY:
            return watchUser->getNumViewsAlone(3) + watchUser->getNumViewsAlone(3);
        case Genre::NONE:
            return watchUser->getNumViewsAlone(4) + watchUser->getNumViewsAlone(4);

    }
    return StatusType::FAILURE;

}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{

    if (movieId <= 0 || userId <= 0 || rating < 0 || rating > 100)
    {
        return StatusType::INVALID_INPUT;
    }
    UserData *watchUser = m_AllUsers.Find(userId);
    MovieData *watchMovie = m_AllMoviesId.Find(movieId);
    if (watchUser == nullptr || watchMovie == nullptr)
        return StatusType::FAILURE;
    if (watchMovie->getMovieStatus())
    {
        if (!watchUser->getVipStatus())
            return StatusType::FAILURE;
    }
    watchMovie->UpdateMovieRating(rating);
    return UpdateRatingsMoviesTrees(movieId, watchMovie, rating, 0);

}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    Genre favgenre;

    if (groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    GroupData *watchGroup = m_AllGroups.Find(groupId);
    if (watchGroup == nullptr)
        return StatusType::FAILURE;
    favgenre = watchGroup->PopularGenre();
///////////////// not finished

}


/////////////////////////////added functions/////////////
StatusType
streaming_database::UpdateRatingsMoviesTrees(int movieId, MovieData *movieData, int added_rating, int added_views)
{
    StatusType status1 = StatusType::FAILURE;
    StatusType status2 = StatusType::FAILURE;
//// check if rating should be average or accumulated
    MoviesRankingKey old_movie_key(movieId, movieData->getMovieViews() - added_views,
                                   movieData->getMovieRating() - added_rating);
    MoviesRankingKey new_movie_key(movieId, movieData->getMovieViews(), movieData->getMovieRating());
    if (m_AllMoviesRating.Remove(old_movie_key) == StatusType::SUCCESS &&
        m_AllMoviesRating.Insert(new_movie_key, movieData) == StatusType::SUCCESS)
    {
        switch (movieData->getMovieGenre())
        {
            case Genre::COMEDY:
                status1 = m_COMEDY.Remove(old_movie_key);
                status2 = m_COMEDY.Insert(new_movie_key, movieData);
                break;
            case Genre::DRAMA:
                status1 = m_DRAMA.Remove(old_movie_key);
                status2 = m_DRAMA.Insert(new_movie_key, movieData);
                break;
            case Genre::ACTION:
                status1 = m_ACTION.Remove(old_movie_key);
                status2 = m_ACTION.Insert(new_movie_key, movieData);
                break;
            case Genre::FANTASY:
                status1 = m_FANTASY.Remove(old_movie_key);
                status2 = m_FANTASY.Insert(new_movie_key, movieData);
                break;
        }


        if (status1 == StatusType::SUCCESS && status2 == StatusType::SUCCESS)
        {
            return StatusType::SUCCESS;

        }

    }
    return StatusType::FAILURE;
}



