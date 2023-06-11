#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <libpq-fe.h>

#include "group_manager.hpp"
#include "registration_group.hpp"

namespace {

    Fl_Double_Window *win = nullptr;
    PGconn *connection = nullptr;
    
    void main_window_callback(Fl_Widget *widget, void* data)
    {
        Fl_Double_Window *main_window = (Fl_Double_Window*)widget;
        main_window->hide();
        PQfinish(connection);
    }

    void die()
    {
        PQfinish(connection);
        exit(EXIT_FAILURE);
    }

    void init()
    {
        // Connect to database
        connection = PQconnectdb("host=localhost port=5432 dbname=test_db user=postgres");
        
        if (PQstatus(connection) != CONNECTION_OK) {
            Fl::fatal(PQerrorMessage(connection));
            die();
        }
        // Init GUI
        win = new Fl_Double_Window(1024, 768, "Testing System");
        win->callback(main_window_callback);

        GroupManager::getInstance().addGroup("registration_group", *new RegistrationGrop(*connection));
        win->fullscreen();
        win->show();
    }
} 

int main (int argc, char *argv[]) 
{
    init();
    return (Fl::run());
}
