#pragma once
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <cstdint>
#include <libpq-fe.h>

class ResultGroup : public Fl_Group {
    Fl_Box *result;
    Fl_Button *exit;

    PGconn &connection;
    const char &student_id;
    const char &test_name;
public:
    ResultGroup(const char &student_id, const char &test_name, const uint32_t p_score, PGconn &p_connection);
};
