#pragma once
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <vector>

struct Student {
    const char *first_name;
    const char *second_name;
    const char *middle_name;
    const char *group_name;
    const char *id;
};

class TestGroup : public Fl_Group {
    Fl_Button *button;
    Fl_Label *label;
    Student student;
public:
    TestGroup(const Student p_student);
};
