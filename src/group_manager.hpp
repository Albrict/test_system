#pragma once
#include <FL/Fl_Group.H>
#include <vector>

class GroupManager {
    std::vector<Fl_Group*> group_vector;
    int current_group;

    static GroupManager *instance;
public:
    static GroupManager &getInstance();
    
    void showCurrentGroup()
    { group_vector[current_group]->show(); }

    void hideCurrentGroup()
    { group_vector[current_group]->hide(); }

    void nextGroup();
    void prevGroup();
    void newGroup(Fl_Group &new_group)
    { group_vector.push_back(&new_group); }
private:
    GroupManager()
        : group_vector(), current_group(0) {}
    ~GroupManager() {}
};
