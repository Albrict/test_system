#pragma once
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>

#include <array>

class RegistrationState : public Fl_Group {
    std::array<Fl_Input*, 3> input_field_array;
    
    Fl_Button *button;
    Fl_Choice *combobox;
public:
    RegistrationState();
};
