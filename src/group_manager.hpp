#pragma once
#include <FL/Fl_Group.H>
#include <FL/Fl.H>
#include <map>
#include <string>

class GroupManager : Fl_Group{
    std::map<std::string, Fl_Group*> group_table;
    static GroupManager *instance;
public:
    static GroupManager &getInstance();
    
    void addGroup(const std::string &key, Fl_Group &group);
    void deleteGroup(const std::string &key);
private:
    GroupManager()
        : Fl_Group(0, 0, Fl::w(), Fl::h()), group_table(){}
    ~GroupManager() {}
};
