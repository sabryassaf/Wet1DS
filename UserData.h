//
// Created by halam on 22/05/2023.
//

#ifndef AVLNODE_H_USERDATA_H
#define AVLNODE_H_USERDATA_H
#include "wet1util.h"
#include "MovieData.h"
#include "GroupData.h"
#define GENRE_NUMBERS 5
class GroupData;

class UserData {
private:
    int m_id;
    int m_groupViewsBefore[GENRE_NUMBERS];
    int m_AllViews[GENRE_NUMBERS];
    bool m_vip;
    int m_groupId;
    GroupData* m_group;

public:
    UserData();

    UserData(int Id, bool Status);

    ~UserData();

    bool getVipStatus() const;

    int getGroupId() const;


    void updateAloneViews(Genre genre);


    int getNumViewsAlone(int i) const;

    int getNumViewsGroup(int i);

    void ResetgroupIdPtr();

    void UpdateUserParameters(int i,GroupData* ptr);

    GroupData* getGrouptr() const;

    void groupwatch(int* arr);


 };


#endif //AVLNODE_H_USERDATA_H
