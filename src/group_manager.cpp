#include "group_manager.hpp"
#include <iostream>

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

void GroupManager::nextGroup()
{
    if (current_group == group_vector.size() - 1) {
        std::cerr << "No groups anymore in vector!\n";
    } else {
        group_vector[current_group]->hide();
        ++current_group;
        group_vector[current_group]->show();
    }
}

void GroupManager::prevGroup()
{
    if (current_group == group_vector.size() == 0) {
        std::cerr << "No groups anymore in vector!\n";
    } else {
        group_vector[current_group]->hide();
        --current_group;
        group_vector[current_group]->show();
    }
}
