#include "test_group.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <iostream>


TestGroup::TestGroup(const Student p_student)
    : Fl_Group(0, 0, Fl::h(), Fl::w()),
    button(nullptr),
    student(p_student)
{
    begin();
    {
        Fl_Box *box = new Fl_Box(50, 50, Fl::w() - 50, 300);
    }
    end(); 
}
