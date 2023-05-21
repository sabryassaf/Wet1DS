//
// Created by soso_ on 5/16/2023.
//

#ifndef WET1_DATA_H
#define WET1_DATA_H

#include "wet1util.h"
#include "AVLTree.h"

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
    Data();
    Data(int id) : m_id(id)
    {}

    virtual ~Data() = 0;

    virtual int getId() const
    {
        return this->m_id;
    }
};


class UserData : public Data {
private:
    int m_aloneViews[5];
    int m_groupViews[5];
    bool m_vip;
    bool m_groupMem;
    int m_groupId;

public:
    UserData();

    UserData(int Id, bool Status) : Data(Id), m_vip(Status), m_groupMem(false), m_groupId(-1) {
        for (int i = 0; i < 5; i++) {
            m_aloneViews[i] = 0;
            m_groupViews[i] = 0;
        }
    }

    ~UserData() = default;

    bool getVipStatus() const {
        return m_vip;
    }

    int getGroupId() const {
        return m_groupId;
    }

    void updateAloneViews(Genre genre) {
        switch (genre) {
            case Genre::COMEDY:
                m_aloneViews[0]++;
            case Genre::DRAMA:
                m_aloneViews[1]++;
            case Genre::ACTION:
                m_aloneViews[2]++;
            case Genre::FANTASY:
                m_aloneViews[3]++;
        }
        m_aloneViews[4]++;
    }
    void updateGroupViews(Genre genre, int groupsize) {

        switch (genre) {
            case Genre::COMEDY:
                m_groupViews[0]+=1;
            case Genre::DRAMA:
                m_groupViews[1]+=1;
            case Genre::ACTION:
                m_groupViews[2]+=1;
            case Genre::FANTASY:
                m_groupViews[3]+=1;
        }
        m_groupViews[4]++;
    }
    int getNumViewsAlone(int i)const{
        return m_aloneViews[i];
    }
    int getNumViewsGroup(int i)const{
        return m_groupViews[i];
    }
};

class MovieData: public Data
{
private:
    int m_rating;
    Genre m_movieGenre;
    int m_views;
    bool m_vipStatus;
    MovieData *m_movieNodeById;
    MovieData *m_movieNodeByRatingInNone;
    MovieData *m_movieNodeByRatingGenre;
public:
    MovieData();
    MovieData(int MovieId, Genre genre, int Views, bool VipStatus) : Data(MovieId), m_rating(0), m_movieGenre(genre),
                                                                     m_views(Views), m_vipStatus(VipStatus),
                                                                     m_movieNodeById(
                                                                             nullptr), m_movieNodeByRatingGenre(nullptr),
                                                                     m_movieNodeByRatingInNone(nullptr)
    {

    }
    MovieData(int ratings,int MovieId, Genre genre, int Views, bool VipStatus) : Data(MovieId), m_rating(ratings), m_movieGenre(genre),
                                                                     m_views(Views), m_vipStatus(VipStatus),
                                                                     m_movieNodeById(
                                                                             nullptr), m_movieNodeByRatingGenre(nullptr),
                                                                     m_movieNodeByRatingInNone(nullptr)
    {

    }

    ~MovieData() = default;

    void setMovieIdNode(MovieData &NodeId)
    {
        m_movieNodeById = &NodeId;
    }

    void setMovieRatingNoneNode(MovieData &NodeId)
    {
        m_movieNodeByRatingInNone = &NodeId;
    }

    void setMovieRatingGenreNode(MovieData &NodeId)
    {
        m_movieNodeByRatingGenre = &NodeId;
    }

    MovieData *getMovieNodeById() const
    {
        return m_movieNodeById;
    }

    MovieData *getMovieNodeByRatingNone() const
    {
        return m_movieNodeByRatingInNone;
    }

    MovieData *getMovieNodeByRatingGenre() const
    {
        return m_movieNodeByRatingGenre;
    }
    void UpdateMovieViewsode(int i)
    {
        this->m_views += i;
    }
    void UpdateMovieRating(int i)
    {
        this->m_rating += i;
    }
    int getMovieRating() const
    {
        return m_rating;
    }

    int getMovieViews() const
    {
        return m_views;
    }
    Genre getMovieGenre() const
    {
        return m_movieGenre;
    }
    int getMovieId() const
    {
        return m_id;
    }
    bool getMovieStatus()const{
        return m_vipStatus;
    }

};

class GroupData : public Data {
private:
    bool m_vip;
    int m_groupId;
    int m_MembersSum;
    AVLtree<int, UserData *> m_GroupUserstree;
    int m_arrViewsSum[5] = {0, 0, 0, 0, 0};

public:
    GroupData(int Id) : Data(Id), m_vip(false), m_MembersSum(0), m_GroupUserstree() {}

    ~GroupData() = default;

    bool getVipStatus() const {
        return m_vip;
    }

    int getGroupId() const {
        return m_groupId;
    }

    int getGroupsize() const {
        return m_GroupUserstree.getSize();
    }

    StatusType add_user(int userkey, UserData *userdata) {


        if (m_GroupUserstree.Insert(userkey, userdata) == StatusType::SUCCESS) {
            if (userdata->getVipStatus()) {
                this->m_vip = true;
            }

            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;

    }


    AVLtree<int, UserData *> &getGroupUsers() {
        return m_GroupUserstree;
    }

    StatusType remove_user(int key) {

        return m_GroupUserstree.Remove(key);

    }

    void updateTogtherViews(MovieData *movie) {
        UserData **arr = nullptr;
        if (m_MembersSum > 0) {
            arr = new UserData *[m_MembersSum];
            if (arr == nullptr) {
                return;
            }
            m_GroupUserstree.InOrderArray(arr);
            for (int i = 0; i < m_MembersSum; i++) {
                arr[i]->updateGroupViews(movie->getMovieGenre(), m_MembersSum);

            }
            movie->UpdateMovieViewsode(m_MembersSum);

        }

    }

    void getGenreViews(int *temparr) {
        UserData **arr = nullptr;
        if (m_MembersSum > 0) {
            arr = new UserData *[m_MembersSum];
            if (arr == nullptr) {
                return;
            }
            m_GroupUserstree.InOrderArray(arr);
            for (int i = 0; i < m_MembersSum; i++) {
                for (int j = 0; j < 5; j++) {
                    temparr[j] += arr[i]->getNumViewsAlone(j) + arr[i]->getNumViewsGroup(j);
                }
            }

        }
    }
    Genre PopularGenre() {
        int arr[5] = {0};
        int n = 0;
        Genre genre;
        getGenreViews(arr);
        for (int i = 0; i < 5; ++i) {
            if (arr[i] > arr[n]) {
                n = i;
            }

        }
        for (int i = 0; i < 5; ++i) {
            if (n == 0)
                return Genre::COMEDY;
            if (n == 1)
                return Genre::DRAMA;
            if (n == 2)
                return Genre::ACTION;
            if (n == 3)
                return Genre::FANTASY;
        }
    }
};


#endif //WET1_DATA_H
