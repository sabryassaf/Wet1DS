//
// Created by halam on 22/05/2023.
//

#ifndef AVLNODE_H_GROUPDATA_H
#define AVLNODE_H_GROUPDATA_H

#include "wet1util.h"
#include "UserData.h"
#include "MovieData.h"
#include "RankTree.h"
#define GENRENUM 5
#define NONEINDEX 4
#define FANTASYINDEX 3
#define ACTIONINDEX 2
#define DRAMAINDEX 1
#define COMEDYINDEX 0

class UserData;

class GroupData
{

private:
    int m_id;
    bool m_vip;
    int m_MembersSum;
    RankTree<int, UserData *> m_GroupUserstree;
    int m_arrViewsSum[GENRENUM];
    int m_VIPCounter;
    int m_MembersAloneViews[GENRENUM];
    int m_groupWatchBySize[GENRENUM];

public:

    GroupData()=default;

    GroupData(int Id);

    ~GroupData();

    bool getVipStatus() const;

    bool Empty () const;

    int getGroupsize() const;


    StatusType add_user(int userkey, UserData *userdata);



    StatusType remove_user(int key,bool Status,UserData* userdata);


    void updateTogtherViews(MovieData *movie);



    Genre PopularGenre();

    StatusType deleteUserIdPtr();

    void updatealoneviews(Genre genre,int i);


    void copyGroupArr(int* arr) ;

    int  getNumViewsIndex(int i) const;


};
int findMaxIndex(const int* arr, int size);


#endif //AVLNODE_H_GROUPDATA_H
