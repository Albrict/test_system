#pragma once
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>

#include <libpq-fe.h>
#include <string>
#include <vector>

class RegistrationGrop: public Fl_Group {
    std::vector<Fl_Input*> input_field_array;
    std::vector<Fl_Button*> button_vector;
    
    std::string test_name;
    std::string student_id;
    
    Fl_File_Chooser *chooser = nullptr;
    Fl_Choice *combobox = nullptr;
    PGconn &connection;

    uint32_t width, height;
    
    // C-style array of function pointers. Need to replace with safe one?
    void(*array_of_callbacks[3])(Fl_Widget*, void *data) = { nullptr, nullptr, nullptr };
public:
    RegistrationGrop(PGconn &p_connection);
private:
    static void writeToDatabaseCallback(Fl_Widget *widget, void *data);
    static void selectTestCallback(Fl_Widget *widget, void *data);
    static void getResultsCallback(Fl_Widget *widget, void *data);
};
