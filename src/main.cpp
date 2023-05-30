#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "registration_state.hpp"
#include "group_manager.hpp"

namespace {

    Fl_Double_Window *win = nullptr;

    void init()
    {
        win = new Fl_Double_Window(1024, 768, "Testing System");
        GroupManager::getInstance().newGroup(*new RegistrationState);
        win->fullscreen();
        win->show();
    }
} 

int main (int argc, char *argv[]) 
{
    init();
    return (Fl::run());
}
