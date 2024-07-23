#include "MainWindow.hpp"

MainWindow::MainWindow()
    : m_VBox(Gtk::ORIENTATION_VERTICAL),
      m_Menu("Formes"),
      m_Add_Polygon("Add Polygon"),
      m_Add_Rectangle("Add Rectangle"),
      m_Add_Circle("Add Circle"),
      m_Add_Square("Add Square"),
      m_Add_Triangle("Add Triangle"),
      m_Add_Star("Add Star"),
      m_Add_Heart("Add Heart"),
      m_Entry() {

    set_title("Drawing Shapes");
    set_default_size(800, 600);
    set_position(Gtk::WIN_POS_CENTER);

    /*
    m_Add_Polygon.signal_activate().connect(sigc::mem_fun(this->m_DrawingArea, &DrawingArea::add_polygon));
    m_Add_Rectangle.signal_activate().connect(sigc::mem_fun(this->m_DrawingArea, &DrawingArea::add_rectangle));
    m_Add_Circle.signal_activate().connect(sigc::mem_fun(this->m_DrawingArea, &DrawingArea::add_circle));
    m_Add_Square.signal_activate().connect(sigc::mem_fun(this->m_DrawingArea, &DrawingArea::add_square));
    m_Add_Triangle.signal_activate().connect(sigc::mem_fun(this->m_DrawingArea, &DrawingArea::add_triangle));
    m_Add_Star.signal_activate().connect(sigc::mem_fun(this->m_DrawingArea, &DrawingArea::add_star));
    m_Add_Heart.signal_activate().connect(sigc::mem_fun(this->m_DrawingArea, &DrawingArea::add_heart));
     */

    m_Add_Polygon.signal_activate().connect([this]{MainWindow::onFormeClicked(&DrawingArea::add_polygon);});
    m_Add_Rectangle.signal_activate().connect([this]{MainWindow::onFormeClicked(&DrawingArea::add_rectangle);});
    m_Add_Circle.signal_activate().connect([this]{MainWindow::onFormeClicked(&DrawingArea::add_circle);});
    m_Add_Square.signal_activate().connect([this]{MainWindow::onFormeClicked(&DrawingArea::add_square);});
    m_Add_Triangle.signal_activate().connect([this]{MainWindow::onFormeClicked(&DrawingArea::add_triangle);});
    m_Add_Star.signal_activate().connect([this]{MainWindow::onFormeClicked(&DrawingArea::add_star);});
    m_Add_Heart.signal_activate().connect([this]{MainWindow::onFormeClicked(&DrawingArea::add_heart);});
   
    m_MenuItems.append(m_Add_Polygon);
    m_MenuItems.append(m_Add_Rectangle);
    m_MenuItems.append(m_Add_Circle);
    m_MenuItems.append(m_Add_Square);
    m_MenuItems.append(m_Add_Triangle);
    m_MenuItems.append(m_Add_Star);
    m_MenuItems.append(m_Add_Heart);

    m_Menu.set_submenu(m_MenuItems);

    m_MenuBar.append(m_Menu);

    m_VBox.pack_start(m_MenuBar, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_DrawingArea);

    add(m_VBox);
    show_all_children();
}

/**
 * \brief Callback appelé lorsqu'une forme est cliquée dans le menu
 * \param f Pointeur vers la méthode de DrawingArea à appeler
 */
void MainWindow::onFormeClicked(void (DrawingArea::*f)()) {
    std::cout << "onFormeClicked" << std::endl;
    (m_DrawingArea.*f)();
}