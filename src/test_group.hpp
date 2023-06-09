#pragma once
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <nlohmann/json.hpp>

struct Student {
    const char *first_name;
    const char *second_name;
    const char *middle_name;
    const char *group_name;
    const char *id;
};

class TestGroup : public Fl_Group {
    struct Question {
        std::string question_text;
        std::string answer;
        std::vector<std::string> false_answers;

        Question(const std::string &p_question_text, const std::string &p_answer, const std::vector<std::string> &p_false_answers)
            : question_text(p_question_text), answer(p_answer), false_answers(p_false_answers) {}
    };

    Fl_Box *test_title;
    Fl_Box *question_box;
    
    std::vector<Question> questions_vector;
    std::vector<Fl_Radio_Round_Button*> radio_buttons_vector;
    std::string test_title_string;

    Student student;
    nlohmann::json data;

    uint32_t current_question;
public:
    TestGroup(const Student p_student);
private:
    void loadJSONAndInitializeVectors();
};
