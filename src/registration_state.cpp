#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <iostream>

#include "registration_state.hpp"

namespace  {
    const int input_field_width = 100;
    const int input_field_height = 20;

    const int button_width = 100;
    const int button_height = 30;
    
    const int combobox_width = 100;
    const int combobox_height = 20;

    enum input_fields_name {
        first_name_input_field = 1,
        second_name_input_field,
        middle_name_input_field
    };
    
    std::array<const char *, 3> labels_array = { "First name:", "Second name:", "Middle name:" };
}

static void say_callback(Fl_Widget *widget, void *data)
{
    std::cout << ((Fl_Input*)data)->value() << '\n';
}

RegistrationState::RegistrationState()
    : Fl_Group(0, 0, Fl::h(), Fl::w()),
    input_field_array(),
    button(nullptr),
    combobox(nullptr)
{
    begin();
    {
        for (int i = input_field_array.size(); i > 0; --i) {
            input_field_array[i] = new Fl_Input(Fl::w() / 2 - input_field_width, Fl::h() / 2 - input_field_height * i, 
                                                input_field_width, input_field_height, labels_array[3 - i]);
            input_field_array[i]->callback(say_callback, (void*)input_field_array[i]);
            input_field_array[i]->when(FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED);
        }
        button = new Fl_Button(Fl::w() / 2 - button_width, Fl::h() - 100, button_width, button_height, "Submit"); 
        combobox = new Fl_Choice(Fl::w() / 2 - combobox_width, Fl::h() / 2 + input_field_height, combobox_width, combobox_height, "Group:");
        combobox->add("ИСП21-21");
        combobox->add("ПСС16-21");
        combobox->add("АПВ19-21");
    } end();
}
