#pragma once
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <cstdint>
#include <libpq-fe.h>
#include <string>

class ResultGroup : public Fl_Group {
    Fl_Box *result = nullptr;
    Fl_Button *exit = nullptr;

    PGconn &connection;
    std::string student_id;
    std::string test_name;
    std::string subject; 
    std::string score_string;
public:
    ResultGroup(const std::string &p_student_id, const std::string &p_test_name, const std::string p_subject, 
                const uint32_t p_score, PGconn &p_connection);
private:
    static void submitResultsToDatabaseCallback(Fl_Widget *widget, void *data);
};
