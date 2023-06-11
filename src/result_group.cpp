#include "result_group.hpp"
#include <FL/Fl.H>
#include <string>

// Fix constructor
ResultGroup::ResultGroup(const uint32_t p_score, PGconn &p_connection)
    : Fl_Group(0, 0, Fl::h(), Fl::w()),
     result(nullptr),
     exit(nullptr), 
     connection(p_connection)
{
    begin();
    {
        std::string score_string = std::to_string(p_score);
        std::string *result_string = new std::string("Your result is: " + score_string);
        result = new Fl_Box(Fl::w() / 2, Fl::h() / 2, 100, 30, result_string->c_str());
        exit = new Fl_Button(Fl::w() / 2, Fl::h() / 2 + 100, 100, 40, "Submit and exit");
    }
    end();
}
