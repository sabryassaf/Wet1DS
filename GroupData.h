//
// Created by halam on 22/05/2023.
//

#ifndef AVLNODE_H_GROUPDATA_H
#define AVLNODE_H_GROUPDATA_H

#include "wet1util.h"
#include "UserData.h"
#include "MovieData.h"
#include "RankTree.h"


class GroupData
{

private:
    int m_id;
    bool m_vip;
    int m_MembersSum;
    RankTree<int, UserData *> m_GroupUserstree;
    int m_arrViewsSum[5] = {0, 0, 0, 0, 0};

public:

    GroupData();

    GroupData(int Id);

    ~GroupData();

    bool getVipStatus() const;


    int getGroupsize() const;


    StatusType add_user(int userkey, UserData *userdata);


    RankTree<int, UserData *> &getGroupUsers();

    StatusType remove_user(int key);


    void updateTogtherViews(MovieData *movie);


    void getGenreViews(int *temparr);

    Genre PopularGenre();

    StatusType deleteUserID();

    void updatealoneviews(Genre genre);

};


#endif //AVLNODE_H_GROUPDATA_H
