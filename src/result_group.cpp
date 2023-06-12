#include "result_group.hpp"
#include <FL/Fl.H>
#include <vector>

namespace {
    const char *query = "INSERT INTO tests(test_name, score, student_id, subject_id)"
                        "VALUES($1, $2, $3, $4)";
    const int array_size = 4;
}

ResultGroup::ResultGroup(const char &p_student_id, const char &p_test_name, const uint32_t p_score, PGconn &p_connection)
    : Fl_Group(0, 0, Fl::h(), Fl::w()),
    result(nullptr),
    exit(nullptr), 
    connection(p_connection),
    student_id(p_student_id),
    test_name(p_test_name),
    score_string()
{
    begin();
    {
        score_string = std::to_string(p_score);
        std::string *result_string = new std::string("Your result is: " + score_string);
        result = new Fl_Box(Fl::w() / 2, Fl::h() / 2, 100, 30, result_string->c_str());
        exit = new Fl_Button(Fl::w() / 2, Fl::h() / 2 + 100, 100, 40, "Submit and exit");
        exit->callback(submitResultsToDatabaseCallback, this);
    }
    end();
}

void ResultGroup::submitResultsToDatabaseCallback(Fl_Widget *widget, void *data)
{
    ResultGroup &result_group = *(ResultGroup*)data;
    std::vector<const char*> test_data;
    test_data.reserve(4);

    test_data.push_back(&result_group.test_name);
    test_data.push_back(result_group.score_string.c_str());
    test_data.push_back(&result_group.student_id);
    test_data.push_back("3");

//    const char *data_array[array_size] {&result_group.test_name, result_group.score_string.c_str(), &result_group.student_id, "4"};
    PGresult *res = PQexecParams(&result_group.connection, query, 4, nullptr, test_data.data(), nullptr, nullptr, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
        Fl::error(PQresultErrorMessage(res));
    PQclear(res);
}
