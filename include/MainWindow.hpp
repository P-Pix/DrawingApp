#include <gtkmm.h>

#include "DrawingArea.hpp"

/**
 * \brief The MainWindow class\n
 * Classe représentant la fenêtre principale de l'application
 */
class MainWindow : public Gtk::Window {
public:
    MainWindow();

private:
    void on_Forme_Clicked(void (DrawingArea::*f)());
    void create_File_Menu_Items();
    void create_Forme_Menu_Items();

    std::string m_FileName = "";

    Gtk::Box m_VBox;
    DrawingArea m_DrawingArea;
    Gtk::MenuBar m_MenuBar;

    Gtk::MenuItem m_MenuFormes;
    Gtk::Menu m_Menu_Formes_Items;
    Gtk::MenuItem m_Add_Polygon;
    Gtk::MenuItem m_Add_Rectangle;
    Gtk::MenuItem m_Add_Circle;
    Gtk::MenuItem m_Add_Square;
    Gtk::MenuItem m_Add_Triangle;
    Gtk::MenuItem m_Add_Star;
    Gtk::MenuItem m_Add_Heart;
    Gtk::SeparatorMenuItem m_Separator;
    Gtk::MenuItem m_Add_Manual_Circle;
    Gtk::MenuItem m_Add_Manual_Polygon;

    Gtk::MenuItem m_MenuFile;
    Gtk::Menu m_MenuFileItems;
    Gtk::MenuItem m_Nouveau;
    Gtk::MenuItem m_Ouvrir;
    Gtk::MenuItem m_Enregistrer;
    Gtk::MenuItem m_EnregistrerSous;
    Gtk::MenuItem m_Quit;
};
