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

void UserData::  updateAloneViews(Genre genre)
{
    switch (genre)
    {
        case Genre::COMEDY:
            m_aloneViews[0]++;
        case Genre::DRAMA:
            m_aloneViews[1]++;
        case Genre::ACTION:
            m_aloneViews[2]++;
        case Genre::FANTASY:
            m_aloneViews[3]++;
        case Genre::NONE:
            break;
    }
    m_aloneViews[4]++;
}

void UserData:: updateGroupViews(Genre genre, int groupsize)
{

    switch (genre)
    {
        case Genre::COMEDY:
            m_groupViews[0] += 1;
        case Genre::DRAMA:
            m_groupViews[1] += 1;
        case Genre::ACTION:
            m_groupViews[2] += 1;
        case Genre::FANTASY:
            m_groupViews[3] += 1;
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