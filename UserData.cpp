//
// Created by halam on 22/05/2023.
//

#include "UserData.h"


UserData:: UserData()=default;

UserData:: UserData(int Id, bool Status) : m_id(Id),m_groupViewsBefore{},m_AllViews{},m_vip(Status),m_groupId(0),m_group(nullptr)
{}

UserData:: ~UserData()  = default;

bool UserData:: getVipStatus() const
{
    return m_vip;
}

int UserData::  getGroupId() const
{
    return m_groupId;
}


void UserData::  updateAloneViews(Genre genre)
{
    switch (genre)
    {
        case Genre::COMEDY:
            m_AllViews[COMEDYINDEX]++;
            break;
        case Genre::DRAMA:
            m_AllViews[DRAMAINDEX]++;
            break;
        case Genre::ACTION:
            m_AllViews[ACTIONINDEX]++;
            break;
        case Genre::FANTASY:
            m_AllViews[FANTASYINDEX]++;
            break;
        case Genre::NONE:
            break;
    }
    m_AllViews[NONEINDEX]++;

}

int UserData:: getNumViewsAlone(int i) const
{
    return m_AllViews[i];
}

int UserData:: getNumViewsGroup(int i)
{
    if(m_groupId > 0 )
       return (m_group->getNumViewsIndex(i) - this->m_groupViewsBefore[i]);

    return 0;
}

void UserData:: ResetgroupIdPtr() {
    this->m_groupId = 0;
    int arr[GENRENUM] = {0};
    groupwatch(arr);
    for (int i = 0; i < GENRENUM; i++) {
        m_AllViews[i] += arr[i]; // we update the groups views for user just when we remove the group
    }
    this->m_group = nullptr;

}
void UserData:: UpdateUserParameters(int i,GroupData* ptr)
{
    this->m_groupId=i;
    this->m_group=ptr;
    ptr->copyGroupArr(m_groupViewsBefore);
}

GroupData* UserData:: getGrouptr() const{
    return m_group;
}

void UserData::groupwatch(int* arr){
    for(int i=0;i<GENRENUM;i++){
        arr[i]=m_group->getNumViewsIndex(i)-m_groupViewsBefore[i];
        if(arr[i]< 0)
            arr[i]=0;
    }
}