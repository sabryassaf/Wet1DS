//
// Created by halam on 22/05/2023.
//

#ifndef AVLNODE_H_USERDATA_H
#define AVLNODE_H_USERDATA_H
#include "wet1util.h"
/*
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
*/
class UserData {
private:
    int m_id;
    int m_aloneViews[5];
    int m_groupViews[5];
    bool m_vip;
    bool m_groupMem;
    int m_groupId;

public:
    UserData();

    UserData(int Id, bool Status);

    ~UserData();

    bool getVipStatus() const;

    int getGroupId() const;

    void updateAloneViews(Genre genre);

    void updateGroupViews(Genre genre, int groupsize);

    int getNumViewsAlone(int i) const;

    int getNumViewsGroup(int i) const;

    void ResetgroupID();

    void UpdategroupID(int i);
};


#endif //AVLNODE_H_USERDATA_H
