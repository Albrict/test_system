#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <iostream>
#include <array>
#include <string>
#include <libpq-fe.h>

#include "group_manager.hpp"
#include "test_group.hpp"
#include "registration_group.hpp"

namespace  {
    enum {
        input_field_width = 100,
        input_field_height = 20,
                              
        button_width = 100,
        button_height = 30,
                              
        combobox_width = 100,
        combobox_height = 20         
    };

    enum {
        first_name_input_field = 1,
        second_name_input_field,
        middle_name_input_field
    };
    
    enum {
        first_name = 0,
        second_name,
        middle_name,
        group_name
    };
    std::array<const char *, 3> labels_array = { "First name:", "Second name:", "Middle name:" };

const char *query_insert = "INSERT INTO students(first_name, second_name, middle_name, group_id) "
                            "SELECT "
                            "$1::varchar, $2::varchar, $3::varchar, $4::varchar "
                            "WHERE "
                                "NOT EXISTS ( "
                                "SELECT * FROM students "
                                "WHERE "
                                "first_name = $1 AND "
                                "second_name = $2 AND "
                                "middle_name = $3 AND "
                                "group_id = $4);";

const char *query_select = "SELECT student_id FROM students "
                            "WHERE "
                            "first_name = $1 AND "
                            "second_name = $2 AND "
                            "middle_name = $3 AND "
                            "group_id = $4; ";
}


RegistrationGrop::RegistrationGrop(PGconn &p_connection)
    : Fl_Group(0, 0, Fl::h(), Fl::w()),
    input_field_array(),
    button(nullptr),
    combobox(nullptr),
    connection(p_connection)
{
    begin();
    {
        // Create three input fields
        input_field_array.reserve(3);
        for (int i = 3; i > 0; --i) 
            input_field_array.push_back(new Fl_Input(Fl::w() / 2 - input_field_width, Fl::h() / 2 - input_field_height * i, 
                                                input_field_width, input_field_height, labels_array[3 - i]));
        
        // Submit button
        button = new Fl_Button(Fl::w() / 2 - button_width, Fl::h() - 100, button_width, button_height, "Submit");
        button->callback(writeToDatabaseCallback, this);
        combobox = new Fl_Choice(Fl::w() / 2 - combobox_width, Fl::h() / 2 + input_field_height, combobox_width, combobox_height, "Group:");
        
        // Combobox with group list from database
        PGresult *result = nullptr;
        result = PQexec(&connection, "SELECT * FROM groups");
        for (int i = 0; i < PQntuples(result); ++i) 
            combobox->add(PQgetvalue(result, i, 0));
        PQclear(result);
    } 
    end();
}

void RegistrationGrop::writeToDatabaseCallback(Fl_Widget *widget, void *data)
{
    std::vector<const char*> student_data;
    RegistrationGrop *registration_group = (RegistrationGrop*)data;
    // Get info from input fields and fill student_data vector 
    student_data.reserve(4);
    for (const auto it : registration_group->input_field_array)
        student_data.push_back(it->value());
    student_data.push_back(registration_group->combobox->text());
    
    // Fill student struct, that needed for TestGroup
    // Execute query and send student_data to database
    PGresult *res = PQexecParams(&registration_group->connection, query_insert, 4, nullptr, student_data.data(),
                                 nullptr, nullptr, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        Fl::error(PQresultErrorMessage(res));
    } else {
        res = PQexecParams(&registration_group->connection, query_select, 4, nullptr, student_data.data(),
                     nullptr, nullptr, 0); 
        std::string *student_id = new std::string(PQgetvalue(res, 0, 0));
        GroupManager::getInstance().addGroup("test_group", *new TestGroup(*student_id->c_str(), registration_group->connection));
        GroupManager::getInstance().deleteGroup("registration_group");
    }
    PQclear(res);
}
