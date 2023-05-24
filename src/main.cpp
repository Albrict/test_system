#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

static void say_callback(Fl_Widget *w, void *user)
{
    ((Fl_Input*)user)->take_focus();
}

static void clear_callback(Fl_Widget *w, void *user)
{
    ((Fl_Input*)user)->value("");
    ((Fl_Input*)user)->take_focus();
}

int main (int argc, char *argv[]) 
{
    
    return 0;
}
