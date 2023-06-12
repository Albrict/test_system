#pragma once
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <cstdint>
#include <libpq-fe.h>
#include <string>

class ResultGroup : public Fl_Group {
    Fl_Box *result;
    Fl_Button *exit;

    PGconn &connection;
    const char &student_id;
    const char &test_name;

    std::string score_string;
public:
    ResultGroup(const char &p_student_id, const char &p_test_name, const uint32_t p_score, PGconn &p_connection);
private:
    static void submitResultsToDatabaseCallback(Fl_Widget *widget, void *data);
};
