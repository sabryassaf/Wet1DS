#include "StreamingDBa1.h"

streaming_database::streaming_database()
        : m_AllMoviesId(), m_AllMoviesRating(), m_COMEDY(), m_DRAMA(), m_ACTION(), m_FANTASY(), m_AllUsers(),
          m_AllGroups()
{
    // TODO: Your code goes here
}

streaming_database::~streaming_database()
{
    m_AllMoviesId.FreeData(m_AllMoviesId.getRoot());
    m_AllGroups.FreeData(m_AllGroups.getRoot());
    m_AllUsers.FreeData(m_AllUsers.getRoot());
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    StatusType status = StatusType::FAILURE;

    if (movieId <= 0 || genre == Genre::NONE || views < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        auto *new_movie_data = new MovieData(movieId, genre, views, vipOnly);

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

                    case Genre::NONE:
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
    catch (const std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType streaming_database::remove_movie(int movieId)
{
    StatusType status = StatusType::FAILURE;
    if (movieId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    MovieData *removeMovie = m_AllMoviesId.Find(movieId);

    if (m_AllMoviesId.Remove(movieId) == StatusType::SUCCESS )
    {
        MoviesRankingKey key(movieId, removeMovie->getMovieRating(), removeMovie->getMovieViews());

        if (m_AllMoviesRating.Remove(key) == StatusType::SUCCESS)
        { // removes the node object from the tree

            switch (removeMovie->getMovieGenre()) {
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
                case Genre::NONE:
                    break;
            }
            if (status == StatusType::SUCCESS) {
                delete removeMovie; //frees the memory allocated for the MovieData object in the data,
                return StatusType::SUCCESS;

            }
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
    try
    {
        auto *newUser = new UserData(userId, isVip);

        if (m_AllUsers.Insert(userId, newUser) == StatusType::SUCCESS)
        {

            return StatusType::SUCCESS;
        }
        delete newUser;
        return StatusType::FAILURE;
    }
    catch (const std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType streaming_database::remove_user(int userId)
{
    if (userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    UserData *removeUser = m_AllUsers.Find(userId);
    if (m_AllUsers.Remove(userId) == StatusType::SUCCESS) {
        if (removeUser->getGroupId() > 0) { //he is in a group
            GroupData *userGroup = removeUser->getGrouptr();
            userGroup->remove_user(userId, removeUser->getVipStatus(),removeUser);
            delete removeUser;
            return StatusType::SUCCESS;
        }


        delete removeUser;
        return StatusType::SUCCESS;
    }
    return StatusType::FAILURE;

}

StatusType streaming_database::add_group(int groupId)
{
    if (groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        auto *newGroup = new GroupData(groupId);
        if (m_AllGroups.Insert(groupId, newGroup) == StatusType::SUCCESS)
        {

            return StatusType::SUCCESS;
        }
        delete newGroup;
        return StatusType::FAILURE;
    }
    catch (const std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType streaming_database::remove_group(int groupId)
{
    if (groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    GroupData *removeGroup = m_AllGroups.Find(groupId);

    if (m_AllGroups.Remove(groupId) == StatusType::SUCCESS)
    {
        removeGroup->deleteUserIdPtr();
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
    GroupData *toGroup = m_AllGroups.Find(groupId);
    UserData *addUser = m_AllUsers.Find(userId);

    if ( toGroup== nullptr || addUser == nullptr)
    {
        return StatusType::FAILURE;
    }

    // check if user isn't already in a group
    if (addUser->getGroupId() > 0)
        return StatusType::FAILURE;

    if (toGroup->add_user(userId, addUser) == StatusType::SUCCESS)
    {
        addUser->UpdateUserParameters(groupId,toGroup);
        return StatusType::SUCCESS;

    }
    return StatusType::FAILURE;

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
    watchUser->updateAloneViews(watchMovie->getMovieGenre());

    if(watchUser->getGroupId() > 0) {
        watchUser->getGrouptr()->updatealoneviews(watchMovie->getMovieGenre(),1);
    }

    watchMovie->UpdateMovieViewer(1);
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
    if (watchGroup == nullptr || watchMovie == nullptr || watchGroup->Empty())
        return StatusType::FAILURE;

    if (watchMovie->getMovieStatus())
    {
        if (!watchGroup->getVipStatus())
            return StatusType::FAILURE;
    }

    watchGroup->updateTogtherViews(watchMovie);
    //  printf(" group %d , size is %d\n*******",groupId,watchGroup->getGroupsize());
    //   MovieData **arr = new MovieData *[100];
    //  MovieData **arr2 = new MovieData *[100];
    //  m_AllMoviesId.BuildInOrderArray(arr2);
    //  m_AllMoviesRating.BuildInOrderArray(arr);
//int ratsize = m_AllMoviesRating.getSize();
    //   printf(" rat sie is %d \n",ratsize);
//int idsize = m_AllMoviesId.getSize();
    // printf(" rat sie is %d \n",idsize);
    // printf("number of users %d \n" , m_AllUsers.getSize());
    //  for(int i=0;i<m_AllMoviesRating.getSize();i++){
    //    printf(" the ids are : %d and the ratings %d and the vies %d\n",arr[i]->getId(),arr[i]->getMovieRating(),arr[i]->getMovieViews());
    //    printf(" the ids are : %d  %d\n",arr2[i]->getId());
    // }
//    delete[] arr;
    //   delete[] arr2;
    //   printf("the group size is %d \n",watchGroup->getGroupsize());
    //  watchGroup->printarr();
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

    int arrSize;
    if (!output)
        return StatusType::FAILURE;
    arrSize = get_all_movies_count(genre).ans();
    //   printf("arrsize is %d \n",arrSize);
    if (arrSize <= 0)
        return StatusType::FAILURE;
    try
    {
        auto **arr = new MovieData *[arrSize];
        switch (genre)
        {
            case Genre::COMEDY:
                if (m_COMEDY.getSize() <= 0)
                    return StatusType::FAILURE;
                m_COMEDY.BuildInOrderArray(arr);
                break;
            case Genre::DRAMA:
                if (m_DRAMA.getSize() <= 0)
                    return StatusType::FAILURE;
                m_DRAMA.BuildInOrderArray(arr);
                break;
            case Genre::ACTION:
                if (m_ACTION.getSize() <= 0)
                    return StatusType::FAILURE;
                m_ACTION.BuildInOrderArray(arr);
                break;
            case Genre::FANTASY:
                if (m_FANTASY.getSize() <= 0)
                    return StatusType::FAILURE;
                m_FANTASY.BuildInOrderArray(arr);
                break;
            case Genre::NONE:
                if (m_AllMoviesRating.getSize() <= 0)
                    return StatusType::FAILURE;
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

    catch (const std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }

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
            return watchUser->getNumViewsAlone(0) + watchUser->getNumViewsGroup(0);
        case Genre::DRAMA:
            return watchUser->getNumViewsAlone(1) + watchUser->getNumViewsGroup(1);
        case Genre::ACTION:
            return watchUser->getNumViewsAlone(2) + watchUser->getNumViewsGroup(2);
        case Genre::FANTASY:
            return watchUser->getNumViewsAlone(3) + watchUser->getNumViewsGroup(3);
        case Genre::NONE:
            return watchUser->getNumViewsAlone(4) + watchUser->getNumViewsGroup(4);
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

    double i = watchMovie->UpdateMovieRating(rating);

    return UpdateRatingsMoviesTrees(movieId, watchMovie, i, 0);

}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{

    Genre favgenre;
    if (groupId <= 0)
        return StatusType::INVALID_INPUT;

    GroupData *watchGroup = m_AllGroups.Find(groupId);
    if (watchGroup == nullptr || watchGroup->Empty() || m_AllMoviesId.EmptyTree())
        return StatusType::FAILURE;


    favgenre = watchGroup->PopularGenre();
    switch (favgenre)
    {
        case Genre::COMEDY:
            if (m_COMEDY.getSize() != 0)
            {
                //     printf(" comedyyyyy\n");
                return m_COMEDY.getMax()->getData()->getId();
            }
            break;

        case Genre::DRAMA:
            //  printf(" dramaaa\n");
            if (m_DRAMA.getSize() != 0)
            {
                return m_DRAMA.getMax()->getData()->getId();
            }
            break;

        case Genre::ACTION:
            if (m_ACTION.getSize() != 0)
            {
                //   printf(" action\n");

                return m_ACTION.getMax()->getData()->getId();
            }
            break;

        case Genre::FANTASY:
            if (m_FANTASY.getSize() != 0)
            {
                //     printf(" fantsyyy with watch %d \n");

                return m_FANTASY.getMax()->getData()->getId();
            }
            break;

        case Genre::NONE:
            return StatusType::FAILURE;
    }
    return StatusType::FAILURE;
}

/////////////////////////////added functions to private section/////////////
StatusType
streaming_database::UpdateRatingsMoviesTrees(int movieId, MovieData *movieData, double added_rating, int added_views)
{

    MoviesRankingKey old_movie_key(movieId,
                                   movieData->getMovieRating() - added_rating,
                                   movieData->getMovieViews() - added_views);

    MoviesRankingKey new_movie_key(movieId, movieData->getMovieRating(), movieData->getMovieViews());

    if (m_AllMoviesRating.Remove(old_movie_key) == StatusType::SUCCESS)
    {
        if (m_AllMoviesRating.Insert(new_movie_key, movieData) == StatusType::SUCCESS)
        {

            //    printf("***************i entered the if *************\n");
            switch (movieData->getMovieGenre())
            {
                case Genre::COMEDY:
                    if (m_COMEDY.Remove(old_movie_key) == StatusType::SUCCESS)
                        return m_COMEDY.Insert(new_movie_key, movieData);
                    break;
                case Genre::DRAMA:
                    if (m_DRAMA.Remove(old_movie_key) == StatusType::SUCCESS)
                        return m_DRAMA.Insert(new_movie_key, movieData);
                    break;
                case Genre::ACTION:
                    if (m_ACTION.Remove(old_movie_key) == StatusType::SUCCESS)
                        return m_ACTION.Insert(new_movie_key, movieData);
                    break;
                case Genre::FANTASY:
                    if (m_FANTASY.Remove(old_movie_key) == StatusType::SUCCESS)
                        return m_FANTASY.Insert(new_movie_key, movieData);
                    break;
                case Genre::NONE:
                    return StatusType::FAILURE;

            }

        }
        return StatusType::FAILURE;

    }

    return StatusType::FAILURE;

}



