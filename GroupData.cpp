//
// Created by halam on 22/05/2023.
//

#include "GroupData.h"

GroupData::GroupData(int Id) : m_id(Id), m_vip(false), m_MembersSum(0), m_GroupUserstree() ,m_arrViewsSum{}, m_VIPCounter(0),m_MembersAloneViews{},m_groupWatchBySize{}
{}

GroupData::~GroupData()=default;


bool GroupData::getVipStatus() const
{
    return m_vip;
}

bool GroupData::Empty() const
{
    return m_GroupUserstree.EmptyTree();
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
            m_VIPCounter++;

        }
        for(int i=0;i<5;i++){
            m_MembersAloneViews[i]+=userdata->getNumViewsAlone(i);
        }
        m_MembersSum++;
        return StatusType::SUCCESS;
    }
    return StatusType::FAILURE;

}


StatusType GroupData::remove_user(int key, bool Status,UserData* userdata)
{
    m_MembersSum--;
    int added[GENRENUM]={0};
    userdata->groupwatch(added);
    if (Status) {
        m_VIPCounter--;
        if(m_VIPCounter <= 0)
            m_vip= false;
    }

    for(int i=0;i<GENRENUM;i++){

        m_MembersAloneViews[i]-= userdata->getNumViewsAlone(i);
        m_groupWatchBySize[i]-=added[i];
        if(m_groupWatchBySize[i] < 0)
            m_groupWatchBySize[i]=0;
        if(m_MembersAloneViews[i]<0)
            m_MembersAloneViews[i]=0;

    }
    return m_GroupUserstree.Remove(key);
}
void GroupData::updateTogtherViews(MovieData *movie){

    if (m_MembersSum <= 0)
        return;
    switch (movie->getMovieGenre())
    {
        case Genre::COMEDY:
            m_arrViewsSum[COMEDYINDEX]++;
            m_groupWatchBySize[COMEDYINDEX]+=m_MembersSum;
            break;
        case Genre::DRAMA:
            m_arrViewsSum[DRAMAINDEX]++;
            m_groupWatchBySize[DRAMAINDEX]+=m_MembersSum;
            break;
        case Genre::ACTION:
            m_arrViewsSum[ACTIONINDEX]++;
            m_groupWatchBySize[ACTIONINDEX]+=m_MembersSum;
            break;
        case Genre::FANTASY:
            m_arrViewsSum[FANTASYINDEX]++;
            m_groupWatchBySize[FANTASYINDEX]+=m_MembersSum;
            break;
        case Genre::NONE:
            break;

    }
    m_arrViewsSum[NONEINDEX]++;
    m_groupWatchBySize[NONEINDEX]+=m_MembersSum;
    movie->UpdateMovieViewer(m_MembersSum);

}

StatusType GroupData::deleteUserIdPtr()
{
    if (m_MembersSum <= 0)
        return StatusType::FAILURE;

    try
    {
        auto **arr = new UserData *[m_MembersSum];
        m_GroupUserstree.BuildInOrderArray(arr);
        for (int i = 0; i < m_MembersSum; i++)
        {
            arr[i]->ResetgroupIdPtr();
        }
        delete[] arr;
    }
    catch (const std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


Genre GroupData::PopularGenre()
{
    int arr[GENRENUM] = {0};
    for(int i=0; i<GENRENUM; i++){
        arr[i]=m_MembersAloneViews[i]+m_groupWatchBySize[i];
    }
    int n = findMaxIndex(arr,NONEINDEX);

    for (int i = 0; i < NONEINDEX; ++i)
    {
        if (n == COMEDYINDEX)
            return Genre::COMEDY;
        if (n == DRAMAINDEX)
            return Genre::DRAMA;
        if (n == ACTIONINDEX)
            return Genre::ACTION;
        if (n == FANTASYINDEX)
            return Genre::FANTASY;
    }
    return Genre::NONE;

}

void GroupData::updatealoneviews(Genre genre, int i){

    switch (genre)
    {
        case Genre::COMEDY:
             m_MembersAloneViews[COMEDYINDEX]+=i;
            break;
        case Genre::DRAMA:
            m_MembersAloneViews[DRAMAINDEX]+=i;
            break;
        case Genre::ACTION:
            m_MembersAloneViews[ACTIONINDEX]+=i;
            break;
        case Genre::FANTASY:
            m_MembersAloneViews[FANTASYINDEX]+=i;
            break;
        case Genre::NONE:
            break;

    }
    m_MembersAloneViews[NONEINDEX]+=i;

}

void GroupData::copyGroupArr(int* arr) {
    for (int i = 0; i < GENRENUM; i++) {
        arr[i] = m_arrViewsSum[i];

    }
}

int GroupData:: getNumViewsIndex(int i) const
{
    return m_arrViewsSum[i];
}



int findMaxIndex(const int* arr, int size) {
    if (size <= 0) {
        return -1;
    }
    int maxElement =0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[maxElement]) {
            maxElement = i;
        }
    }

    return maxElement;
}
