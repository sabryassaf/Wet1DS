//
// Created by halam on 22/05/2023.
//

#include "GroupData.h"

GroupData::GroupData(int Id) : m_id(Id), m_vip(false), m_MembersSum(0), m_GroupUserstree()
{}

GroupData::~GroupData() = default;

bool GroupData::getVipStatus() const
{
    return m_vip;
}


int GroupData::getGroupsize() const
{
    return m_GroupUserstree.getSize();
}

StatusType GroupData::add_user(int userkey, UserData *userdata)
{
    if (m_GroupUserstree.Insert(userkey, userdata) == StatusType::SUCCESS)
    {
        if (userdata->getVipStatus())
        {
            this->m_vip = true;
        }
        m_MembersSum++;
        return StatusType::SUCCESS;
    }
    return StatusType::FAILURE;

}


RankTree<int, UserData *> &GroupData::getGroupUsers()
{
    return m_GroupUserstree;
}

StatusType GroupData::remove_user(int key)
{

    return m_GroupUserstree.Remove(key);

}

void GroupData::updateTogtherViews(MovieData *movie)
{
    if (m_MembersSum <= 0)
        return;
    try
    {
        UserData **arr = new UserData *[m_MembersSum];

        m_GroupUserstree.BuildInOrderArray(arr);
        for (int i = 0; i < m_MembersSum; i++)
        {
            arr[i]->updateGroupViews(movie->getMovieGenre());

        }
        movie->UpdateMovieViewer(m_MembersSum);
        delete[] arr;
    }
    catch (const std::bad_alloc &)
    {
        return;
    }

}

StatusType GroupData::deleteUserID()
{
    if (m_MembersSum <= 0)
        return StatusType::FAILURE;

    try
    {
        UserData **arr = new UserData *[m_MembersSum];
        m_GroupUserstree.BuildInOrderArray(arr);
        for (int i = 0; i < m_MembersSum; i++)
        {
            arr[i]->ResetgroupID();
        }
        delete[] arr;
    }
    catch (const std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

void GroupData::getGenreViews(int *temparr)
{

    UserData **arr = nullptr;
    if (m_MembersSum <= 0)
        return;
    try
    {
        arr = new UserData *[m_MembersSum];
        m_GroupUserstree.BuildInOrderArray(arr);
        for (int i = 0; i < m_MembersSum; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                temparr[j] += arr[i]->getNumViewsAlone(j) + arr[i]->getNumViewsGroup(j);
            }
        }
        delete[] arr;
    }
    catch (const std::bad_alloc &)
    {
        return;
    }
}


Genre GroupData::PopularGenre()
{
    int arr[5] = {0};
    int n = 0;
    getGenreViews(arr);
    for (int i = 0; i < 5; ++i)
    {
        if (arr[i] > arr[n])
        {
            n = i;
        }
    }

    for (int i = 0; i < 5; ++i)
    {
        if (n == 0)
            return Genre::COMEDY;
        if (n == 1)
            return Genre::DRAMA;
        if (n == 2)
            return Genre::ACTION;
        if (n == 3)
            return Genre::FANTASY;
    }
    return Genre::NONE;

}

void GroupData::updatealoneviews(Genre genre){

    switch (genre)
    {
        case Genre::COMEDY:
             m_arrViewsSum[0]++;
            break;
        case Genre::DRAMA:
            m_arrViewsSum[1]++;
            break;
        case Genre::ACTION:
            m_arrViewsSum[2]++;
            break;
        case Genre::FANTASY:
            m_arrViewsSum[3]++;
            break;
        case Genre::NONE:
            break;

    }
    m_arrViewsSum[4]++;

}

