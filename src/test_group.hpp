#pragma once
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <libpq-fe.h>
#include "json.hpp"

class TestGroup : public Fl_Group {
    struct Question {
        std::string question_text;
        std::vector<std::string> answers;

        size_t right_answer;
        Question(const std::string &p_question_text, const std::vector<std::string> &p_answers, const size_t p_right_answer)
            : question_text(p_question_text), answers(p_answers), right_answer(p_right_answer){}
    };

    Fl_Box *test_title = nullptr;
    Fl_Box *question_box = nullptr;
    Fl_Button *submit = nullptr;     

    std::vector<Question> questions_vector;
    std::vector<Fl_Radio_Round_Button*> radio_buttons_vector;
    std::string test_title_string;
    std::string test_name;
    std::string test_subject;
    std::string student_id;


    size_t current_question = 0;
    uint32_t score = 0;

    nlohmann::json data;
    PGconn &connection;
public:
    TestGroup(const std::string &p_test_name, const std::string &p_student_id, PGconn &p_connection);
private:
    void loadJSONAndInitializeVectors();
    void createQuestion();
    static void answerCallback(Fl_Widget *widget, void *data);
};
