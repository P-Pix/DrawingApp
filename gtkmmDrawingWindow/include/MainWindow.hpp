#include <gtkmm.h>
#include <iostream>

#include "DrawingArea.hpp"

class MainWindow : public Gtk::Window {
public:
    MainWindow();

private:
    void onFormeClicked(void (DrawingArea::*f)());

    Gtk::Box m_VBox;
    DrawingArea m_DrawingArea;
    Gtk::MenuBar m_MenuBar;
    Gtk::MenuItem m_Menu;
    Gtk::Menu m_MenuItems;

    Gtk::MenuItem m_Add_Polygon;
    Gtk::MenuItem m_Add_Rectangle;
    Gtk::MenuItem m_Add_Circle;
    Gtk::MenuItem m_Add_Square;
    Gtk::MenuItem m_Add_Triangle;
    Gtk::MenuItem m_Add_Star;
    Gtk::MenuItem m_Add_Heart;

    Gtk::Entry m_Entry;
};
