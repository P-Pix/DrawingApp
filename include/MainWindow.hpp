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
    void onFormeClicked(void (DrawingArea::*f)());
    void createFileMenuItems();
    void createFormeMenuItems();

    std::string m_FileName = "";

    Gtk::Box m_VBox;
    DrawingArea m_DrawingArea;
    Gtk::MenuBar m_MenuBar;

    Gtk::MenuItem m_MenuFormes;
    Gtk::Menu m_MenuFomresItems;
    Gtk::MenuItem m_Add_Polygon;
    Gtk::MenuItem m_Add_Rectangle;
    Gtk::MenuItem m_Add_Circle;
    Gtk::MenuItem m_Add_Square;
    Gtk::MenuItem m_Add_Triangle;
    Gtk::MenuItem m_Add_Star;
    Gtk::MenuItem m_Add_Heart;
    Gtk::Entry m_Entry;

    Gtk::MenuItem m_MenuFile;
    Gtk::Menu m_MenuFileItems;
    Gtk::MenuItem m_Nouveau;
    Gtk::MenuItem m_Ouvrir;
    Gtk::MenuItem m_Enregistrer;
    Gtk::MenuItem m_EnregistrerSous;
    Gtk::MenuItem m_Quit;
};
