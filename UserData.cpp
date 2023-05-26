//
// Created by halam on 22/05/2023.
//

#include "UserData.h"

UserData:: UserData(){}

UserData:: UserData(int Id, bool Status) : m_id(Id), m_vip(Status), m_groupMem(false), m_groupId(0)
{
    for (int i = 0; i < 5; i++)
    {
        m_aloneViews[i] = 0;
        m_groupViews[i] = 0;
    }
}

UserData:: ~UserData()  = default;

bool UserData:: getVipStatus() const
{
    return m_vip;
}

int UserData::  getGroupId() const
{
    return m_groupId;
}
int UserData::  getUserId() const
{
    return m_id;
}

void UserData::  updateAloneViews(Genre genre)
{
    switch (genre)
    {
        case Genre::COMEDY:
            m_aloneViews[0]++;
            break;
        case Genre::DRAMA:
            m_aloneViews[1]++;
            break;
        case Genre::ACTION:
            m_aloneViews[2]++;
            break;
        case Genre::FANTASY:
            m_aloneViews[3]++;
            break;
        case Genre::NONE:
            break;
    }
    m_aloneViews[4]++;

}

void UserData:: updateGroupViews(Genre genre)
{


    switch (genre)
    {
        case Genre::COMEDY:
            m_groupViews[0]++;
            break;
        case Genre::DRAMA:
            m_groupViews[1]++;
            break;
        case Genre::ACTION:
            m_groupViews[2]++;
            break;
        case Genre::FANTASY:
            m_groupViews[3]++;
            break;
        case Genre::NONE:
            break;
    }
    m_groupViews[4]++;
}

int UserData:: getNumViewsAlone(int i) const
{
    return m_aloneViews[i];
}

int UserData:: getNumViewsGroup(int i) const
{
    //if(m_groupId <= 0)
     //   return 0;
    return m_groupViews[i];
}
void UserData:: ResetgroupID()
{
    this->m_groupId=0;
}

void UserData:: UpdategroupID(int i)
{
    this->m_groupId=i;
}
