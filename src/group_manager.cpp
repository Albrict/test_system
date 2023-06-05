#include "group_manager.hpp"
#include <iostream>
#include <FL/Fl.H>

GroupManager *GroupManager::instance = nullptr;

GroupManager &GroupManager::getInstance()
{
    if (instance == nullptr) {
        instance = new GroupManager();
        return *instance;
    } else {
        return *instance;
    }
}

void GroupManager::addGroup(const std::string &key, Fl_Group &group)
{
    add(group);
    group_table.insert({key, &group});
}

void GroupManager::deleteGroup(const std::string &key)
{
    group_table[key]->hide();
    remove(group_table[key]);
    group_table.erase(key);
    redraw();
}
