#include "MainWindow.hpp"

#include <iostream>

MainWindow::MainWindow()
    : m_VBox(Gtk::ORIENTATION_VERTICAL),
      m_MenuFormes("Formes"),
      m_Add_Polygon("Add Polygon"),
      m_Add_Rectangle("Add Rectangle"),
      m_Add_Circle("Add Circle"),
      m_Add_Square("Add Square"),
      m_Add_Triangle("Add Triangle"),
      m_Add_Star("Add Star"),
      m_Add_Heart("Add Heart"),
      m_Entry(),
      m_MenuFile("File"),
      m_Nouveau("New"),
      m_Ouvrir("Open"),
      m_Enregistrer("Save"),
      m_EnregistrerSous("Save As"),
      m_Quit("Quit") {

    set_title("Drawing Shapes");
    set_default_size(800, 600);
    set_position(Gtk::WIN_POS_CENTER);

    createFileMenuItems();
    createFormeMenuItems();

    m_VBox.pack_start(m_MenuBar, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_DrawingArea);

    add(m_VBox);
    show_all_children();
}

void MainWindow::createFormeMenuItems() {
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
  
  m_MenuFomresItems.append(m_Add_Polygon);
  m_MenuFomresItems.append(m_Add_Rectangle);
  m_MenuFomresItems.append(m_Add_Circle);
  m_MenuFomresItems.append(m_Add_Square);
  m_MenuFomresItems.append(m_Add_Triangle);
  m_MenuFomresItems.append(m_Add_Star);
  m_MenuFomresItems.append(m_Add_Heart);

  m_MenuFormes.set_submenu(m_MenuFomresItems);

  m_MenuBar.append(m_MenuFormes);
}

void MainWindow::createFileMenuItems() {
    m_Nouveau.signal_activate().connect([this] {
      this->m_DrawingArea.clear();
    });

    m_Ouvrir.signal_activate().connect([this] {
      Gtk::FileChooserDialog dialog("Open File", Gtk::FILE_CHOOSER_ACTION_OPEN);
      dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
      dialog.add_button("_Open", Gtk::RESPONSE_OK);
      dialog.set_transient_for(*this);
      dialog.set_current_folder(".");
      int result = dialog.run();
      if (result == Gtk::RESPONSE_OK) {
        this->m_FileName = dialog.get_filename();
      }
      if (!this->m_FileName.empty()) {
        std::cout << "Opening file " << this->m_FileName << std::endl;
        this->m_DrawingArea.read_file(this->m_FileName);
      }
    });

    m_Enregistrer.signal_activate().connect([this] {
      if (this->m_FileName.empty()) {
        Gtk::FileChooserDialog dialog("Save File", Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Save", Gtk::RESPONSE_OK);
        dialog.set_transient_for(*this);
        dialog.set_current_folder(".");
        int result = dialog.run();
        if (result == Gtk::RESPONSE_OK) {
          this->m_FileName = dialog.get_filename();
        }
      }
      if (!this->m_FileName.empty()) {
        std::cout << "Saving file as " << this->m_FileName << std::endl;
        this->m_DrawingArea.save_file(this->m_FileName);
      }
    });

    m_EnregistrerSous.signal_activate().connect([this] {
      Gtk::FileChooserDialog dialog("Save File", Gtk::FILE_CHOOSER_ACTION_SAVE);
      dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
      dialog.add_button("_Save", Gtk::RESPONSE_OK);
      dialog.set_transient_for(*this);
      dialog.set_current_folder(".");
      int result = dialog.run();
      if (result == Gtk::RESPONSE_OK) {
        this->m_FileName = dialog.get_filename();
      }
      if (!this->m_FileName.empty()) {
        std::cout << "Saving file as " << this->m_FileName << std::endl;
        this->m_DrawingArea.save_file(this->m_FileName);
      }
    });

    m_Quit.signal_activate().connect([this] {
        hide();
    });

    m_MenuFileItems.append(m_Nouveau);
    m_MenuFileItems.append(m_Ouvrir);
    m_MenuFileItems.append(m_Enregistrer);
    m_MenuFileItems.append(m_EnregistrerSous);
    m_MenuFileItems.append(m_Quit);

    m_MenuFile.set_submenu(m_MenuFileItems);

    m_MenuBar.append(m_MenuFile);
}

/**
 * \brief Callback appelé lorsqu'une forme est cliquée dans le menu
 * \param f Pointeur vers la méthode de DrawingArea à appeler
 */
void MainWindow::onFormeClicked(void (DrawingArea::*f)()) {
    std::cout << "onFormeClicked" << std::endl;
    (m_DrawingArea.*f)();
}