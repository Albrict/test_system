#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <iostream>
#include <array>
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
        combobox_height = 20,
        
        button_padding = 100
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
    std::array<const char *, 3> button_label_array = {"Select test", "Results", "Submit" };

    const char *query_insert = "SELECT insert_student($1, $2, $3, $4);";
    constexpr int vector_size = 3;
}


RegistrationGrop::RegistrationGrop(PGconn &p_connection)
    : Fl_Group(0, 0, Fl::h(), Fl::w()),
    input_field_array(),
    button_vector(),
    test_name(),
    student_id(),
    connection(p_connection)
{
    array_of_callbacks[0] = selectTestCallback;
    array_of_callbacks[1] = getResultsCallback;
    array_of_callbacks[2] = writeToDatabaseCallback;
    begin();
    {
        // Create three input fields
        input_field_array.reserve(vector_size);
        for (int i = vector_size; i > 0; --i) 
            input_field_array.push_back(new Fl_Input(Fl::w() / 2 - input_field_width, Fl::h() / 2 - input_field_height * i, 
                                                input_field_width, input_field_height, labels_array[3 - i]));
        
        // Create buttons 
        button_vector.reserve(vector_size); 
        
        for (size_t i = vector_size; i > 0; --i) {
            Fl_Button &button = *new Fl_Button(Fl::w() / 2 - button_width, Fl::h() - button_padding * i, 
                                               button_width, button_height, button_label_array[vector_size - i]);
            button.callback(array_of_callbacks[vector_size - i], this);
            button_vector.push_back(&button);
        }

        // Combobox with group list from database
        combobox = new Fl_Choice(Fl::w() / 2 - combobox_width, Fl::h() / 2 + input_field_height, combobox_width, combobox_height, "Group:");
         
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
    RegistrationGrop &registration_group = *(RegistrationGrop*)data;
    if (registration_group.chooser) {
        if (registration_group.chooser->value())
            registration_group.test_name = registration_group.chooser->value();
        else
            fl_alert("Please, pick a test first");
    } else {
        fl_alert("Please, pick a test first");
    }
    // Get info from input fields and fill student_data vector 
    std::vector<const char*> student_data;
    student_data.reserve(4);
    for (const auto it : registration_group.input_field_array)
        student_data.push_back(it->value());
    student_data.push_back(registration_group.combobox->text());
    
    // Fill student struct, that needed for TestGroup
    // Execute query and send student_data to database
    PGresult *res = PQexecParams(&registration_group.connection, query_insert, 4, nullptr, student_data.data(),
                                 nullptr, nullptr, 0);
    if (PQresultStatus(res) == PGRES_FATAL_ERROR) {
        Fl::error(PQresultErrorMessage(res));
    } else {
        registration_group.student_id = PQgetvalue(res, 0, 0);
        GroupManager::getInstance().addGroup("test_group", 
                                             *new TestGroup(registration_group.test_name, 
                                                            registration_group.student_id, registration_group.connection));
        GroupManager::getInstance().deleteGroup("registration_group");
    }
    PQclear(res);
}

void RegistrationGrop::selectTestCallback(Fl_Widget *widget, void *data)
{
    RegistrationGrop &registration_group = *(RegistrationGrop*)data;
    if (registration_group.chooser == nullptr) {
        registration_group.chooser = new Fl_File_Chooser("..", "JSON files (*json)", FL_SINGLE, "Choose test");
        registration_group.chooser->show();
    } else {
        registration_group.chooser->show();
    }
}

void RegistrationGrop::getResultsCallback(Fl_Widget *widget, void *data)
{

}
