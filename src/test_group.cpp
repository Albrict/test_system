#include "test_group.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <fstream>

using json = nlohmann::json;
namespace {
    enum {
        left_padding = 100,
        spacing = 30,
        button_width = 50,
        button_height = 50
    };
};

TestGroup::TestGroup(const Student p_student)
    : Fl_Group(0, 0, Fl::h(), Fl::w()),
    test_title(nullptr),
    question_box(nullptr),
    questions_vector(), 
    radio_buttons_vector(),
    test_title_string(),
    student(p_student),
    data(),
    current_question(0)
{
    loadJSONAndInitializeVectors();
    begin();
    {
        test_title = new Fl_Box(Fl::w() / 2, 20, test_title_string.size(), 20, test_title_string.c_str()); 

        question_box = new Fl_Box(50, 100, Fl::w() - 100, 300, questions_vector[current_question].question_text.c_str());
        question_box->box(FL_BORDER_BOX);
        
        Fl_Radio_Round_Button &button = *new Fl_Radio_Round_Button(left_padding, question_box->h() + spacing * 0 + 100, button_width, button_width,
                                                                   questions_vector[current_question].answer.c_str());
        for (size_t i = 0; i < questions_vector[current_question].false_answers.size(); ++i) {
            Fl_Radio_Round_Button &button = *new Fl_Radio_Round_Button(left_padding, question_box->h() + spacing * (i + 1) + 100, button_width, button_height,
                                                                      questions_vector[current_question].false_answers[i].c_str());
            button.box(FL_NO_BOX);
            radio_buttons_vector.push_back(&button);
        }
    }
    end(); 
}

void TestGroup::loadJSONAndInitializeVectors()
{
    std::ifstream f("../tests/test.json");
    json data = json::parse(f);
    test_title_string = data["title"].get<std::string>();

    for (auto &element : data["test_array"]) {
        std::string question_text = element["question"]["text"].get<std::string>();
        std::string question_answer = element["question"]["answer"].get<std::string>();
        std::vector<std::string> false_answers_vector = element["question"]["variants"].get<std::vector<std::string>>();
    
        Question question(question_text, question_answer, false_answers_vector);
        questions_vector.push_back(question);
    }
}
