#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <iostream>
#include <array>
#include <libpq-fe.h>

#include "registration_group.hpp"

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

    const char *query = "INSERT INTO Students (student_name, group_id) "
                        " VALUES ($1, $2)";
}


RegistrationGrop::RegistrationGrop(PGconn &p_connection)
    : Fl_Group(0, 0, Fl::h(), Fl::w()),
    input_field_array(),
    button(nullptr),
    combobox(nullptr),
    connection(p_connection)
{
    PGresult *result = nullptr;
    result = PQexec(&connection, "SELECT * FROM groups");
     
    begin();
    {
        input_field_array.reserve(3);
        for (int i = 3; i > 0; --i) 
            input_field_array.push_back(new Fl_Input(Fl::w() / 2 - input_field_width, Fl::h() / 2 - input_field_height * i, 
                                                input_field_width, input_field_height, labels_array[3 - i]));

        button = new Fl_Button(Fl::w() / 2 - button_width, Fl::h() - 100, button_width, button_height, "Submit");
        button->callback(say_callback, this);
        combobox = new Fl_Choice(Fl::w() / 2 - combobox_width, Fl::h() / 2 + input_field_height, combobox_width, combobox_height, "Group:");
        
        // Adding group names to combobox
        for (int i = 0; i < PQntuples(result); ++i) 
            combobox->add(PQgetvalue(result, i, 1));
        PQclear(result);
    } end();
}

void RegistrationGrop::say_callback(Fl_Widget *widget, void *data)
{
    const char *name = nullptr;
    RegistrationGrop *registration_group = (RegistrationGrop*)data;

    for (const auto it : registration_group->input_field_array) {
        name = it->value();
    }
    const char *params[3];
    params[0] = name;
    params[1] = "1";
    
    PGresult *res = PQexecParams(&registration_group->connection, query, 2, nullptr, params,
                                 NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
        Fl::error(PQresultErrorMessage(res));
    PQclear(res);

}
