#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <fstream>

#include "test_group.hpp"
#include "group_manager.hpp"
#include "result_group.hpp"

using json = nlohmann::json;
namespace {
    enum {
        left_padding = 100,
        spacing = 30,
        button_width = 50,
        button_height = 50
    };
    const std::string submit_str = "Submit";
};

TestGroup::TestGroup(const char &p_student_id, PGconn &p_connection)
    : Fl_Group(0, 0, Fl::h(), Fl::w()),
    test_title(nullptr),
    question_box(nullptr),
    submit(nullptr),
    questions_vector(), 
    radio_buttons_vector(),
    test_title_string(),
    data(),
    current_question(0),
    score(0),
    connection(p_connection),
    student_id(p_student_id)
{
    loadJSONAndInitializeVectors();
    createQuestion();
    begin();
    {
        test_title = new Fl_Box(Fl::w() / 2, 20, test_title_string.size(), 20, test_title_string.c_str()); 
        submit = new Fl_Button(Fl::w() / 2 - submit_str.size(), Fl::h() - 100, 100, 20, submit_str.c_str());
        submit->callback(answerCallback, this);
    }
    end();
}

void TestGroup::loadJSONAndInitializeVectors()
{
    std::ifstream f("../tests/test.json");
    json data = json::parse(f);
    test_title_string = data["title"].get<std::string>();
    
    // Fill question vectors and find answer index
    for (const auto &element : data["test_array"]) {
        std::string question_text = element["question"]["text"].get<std::string>();
        std::string right_answer = element["question"]["answer"].get<std::string>();
        std::vector<std::string> answers = element["question"]["variants"].get<std::vector<std::string>>();
       
        size_t i = 0;
        for (; i < answers.size(); i++) {
            if (right_answer == answers[i])
                break; 
        }
        Question question(question_text, answers, i);
        questions_vector.push_back(question);
    }
}

void TestGroup::createQuestion()
{
    hide();
    // Delete all widgets, if there any
    if (question_box)
        this->remove(question_box);
    if (!radio_buttons_vector.empty()) {
        for (size_t i = 0; i < radio_buttons_vector.size(); ++i) {
            this->remove(radio_buttons_vector[i]);
            delete radio_buttons_vector[i];
        }
        radio_buttons_vector.clear();
    }

    begin();
    {
        question_box = new Fl_Box(50, 100, Fl::w() - 100, 300, questions_vector.at(current_question).question_text.c_str());
        question_box->box(FL_BORDER_BOX);

        for (size_t i = 0; i < questions_vector.at(current_question).answers.size(); ++i) {
            std::string &answer = questions_vector.at(current_question).answers.at(i);
            Fl_Radio_Round_Button &button = *new Fl_Radio_Round_Button(left_padding, question_box->h() + spacing * (i + 1) + 100,                                                                       button_width, button_height, answer.c_str());
            radio_buttons_vector.push_back(&button);
        }
    }
    end(); 
    redraw();
    show();
}

void TestGroup::answerCallback(Fl_Widget *widget, void *data)
{
    TestGroup &test_group = *(TestGroup*)data;
    for (size_t i = 0; i < test_group.radio_buttons_vector.size(); ++i) {
        if (test_group.radio_buttons_vector[i]->value()) {
            if (i == test_group.questions_vector[test_group.current_question].right_answer) {
                printf("%s\n", "Right answer!");
                test_group.score += 20;
            }
            test_group.current_question++;
            if (test_group.current_question >= test_group.questions_vector.size()) {
                GroupManager::getInstance().addGroup("result_group", *new ResultGroup(test_group.student_id, *test_group.test_title_string.c_str(), 
                                                                                      test_group.score, test_group.connection));
                GroupManager::getInstance().deleteGroup("test_group");
                break;
            } else {
                test_group.createQuestion(); 
            }
        }
    }
}
