#pragma once
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>

#include <libpq-fe.h>
#include <vector>

class RegistrationGrop: public Fl_Group {
    std::vector<Fl_Input*> input_field_array;
    
    Fl_Button *button;
    Fl_Choice *combobox;

    PGconn &connection;
public:
    RegistrationGrop(PGconn &p_connection);
private:
    static void writeToDatabaseCallback(Fl_Widget *widget, void *data);
};
