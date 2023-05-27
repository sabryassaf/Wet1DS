//
// Created by halam on 22/05/2023.
//

#ifndef AVLNODE_H_USERDATA_H
#define AVLNODE_H_USERDATA_H
#include "wet1util.h"
#include "MovieData.h"
#include "GroupData.h"

class GroupData;

class UserData {
private:
    int m_id;
    int m_aloneViews[5];
    int m_groupViewsBefore[5];
    int m_AllViews[5];
    bool m_vip;
    bool m_groupMem;
    int m_groupId;
    GroupData* m_group;

public:
    UserData();

    UserData(int Id, bool Status);

    ~UserData();

    bool getVipStatus() const;

    int getGroupId() const;

    int getUserId() const;

    void updateAloneViews(Genre genre);

    void updateGroupViews(Genre genre);

    int getNumViewsAlone(int i) const;

    int getNumViewsGroup(int i);

    void ResetgroupIdPtr();

    void UpdateUserParameters(int i,GroupData* ptr);

    GroupData* getGrouptr() const;

    void setGrouptr(GroupData* ptr);

    void ResetgroupId();

    };


#endif //AVLNODE_H_USERDATA_H
