#include <gtkmm.h>
#include <iostream>
#include <map>

class MyWindow : public Gtk::Window {
public:
    MyWindow();

protected:
    // Signal handlers
    void on_button_clicked();
    void on_menu_file_open();
    void on_show_text_button_clicked();
    void on_add_event_button_clicked();
    void on_calendar_day_selected();

    // Widgets
    Gtk::Box m_box;
    Gtk::Button m_button;
    Gtk::MenuBar m_menubar;
    Gtk::MenuItem m_menuitem_file;
    Gtk::Menu m_menu_file;
    Gtk::MenuItem m_menuitem_open;

    Gtk::Entry m_text_entry;
    Gtk::Button m_show_text_button;
    Gtk::Label m_text_label;

    Gtk::Calendar m_calendar;
    Gtk::Entry m_event_entry;
    Gtk::Button m_add_event_button;
    Gtk::Label m_event_label;

    // Event storage
    std::map<Glib::Date, std::string> m_events;
};

MyWindow::MyWindow() : m_button("Click Me"), m_menuitem_file("Fichier"), m_menuitem_open("Ouvrir"),
  m_show_text_button("Show Text"), m_add_event_button("Add Event") {
    set_title("GTKmm Example");
    set_border_width(10);

    // Set up menu
    m_menuitem_open.signal_activate().connect(sigc::mem_fun(*this, &MyWindow::on_menu_file_open));
    m_menu_file.append(m_menuitem_open);
    m_menuitem_file.set_submenu(m_menu_file);
    m_menubar.append(m_menuitem_file);

    // Set up layout
    m_box.set_orientation(Gtk::ORIENTATION_VERTICAL);
    m_box.pack_start(m_menubar, Gtk::PACK_SHRINK);
    m_box.pack_start(m_button, Gtk::PACK_SHRINK);
    m_box.pack_start(m_text_entry, Gtk::PACK_SHRINK);
    m_box.pack_start(m_show_text_button, Gtk::PACK_SHRINK);
    m_box.pack_start(m_text_label, Gtk::PACK_SHRINK);
    m_box.pack_start(m_calendar, Gtk::PACK_EXPAND_WIDGET);
    m_box.pack_start(m_event_entry, Gtk::PACK_SHRINK);
    m_box.pack_start(m_add_event_button, Gtk::PACK_SHRINK);
    m_box.pack_start(m_event_label, Gtk::PACK_SHRINK);
    add(m_box);

    // Connect signals
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked));
    m_show_text_button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_show_text_button_clicked));
    m_add_event_button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_add_event_button_clicked));
    m_calendar.signal_day_selected().connect(sigc::mem_fun(*this, &MyWindow::on_calendar_day_selected));

    // Show all widgets
    m_menuitem_file.show();
    m_menuitem_open.show();
    m_menubar.show();
    m_button.show();
    m_text_entry.show();
    m_show_text_button.show();
    m_text_label.show();
    m_calendar.show();
    m_event_entry.show();
    m_add_event_button.show();
    m_event_label.show();
    m_box.show();
}

void MyWindow::on_button_clicked() {
    std::cout << "Button clicked!" << std::endl;
}

void MyWindow::on_menu_file_open() {
    Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    // Add response buttons to the dialog:
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);

    int result = dialog.run();

    // Handle the response:
    switch(result) {
        case(Gtk::RESPONSE_OK): {
            std::string filename = dialog.get_filename();
            std::cout << "File selected: " << filename << std::endl;
            break;
        }
        case(Gtk::RESPONSE_CANCEL): {
            std::cout << "Cancel clicked." << std::endl;
            break;
        }
        default: {
            std::cout << "Unexpected button clicked." << std::endl;
            break;
        }
    }
}

void MyWindow::on_show_text_button_clicked() {
    std::string text = m_text_entry.get_text();
    m_text_label.set_text(text);
    std::cout << "Text entered: " << text << std::endl;
}

void MyWindow::on_add_event_button_clicked() {
    std::string event = m_event_entry.get_text();
    guint year, month, day;
    m_calendar.get_date(year, month, day);
    Glib::Date date(year, month + 1, day); // Gtk::Calendar uses month 0-11, Glib::Date uses 1-12

    m_events[date] = event;
    m_event_label.set_text("Event added for " + date.format_string("%Y-%m-%d"));
    std::cout << "Event added for " << date.format_string("%Y-%m-%d") << ": " << event << std::endl;
}

void MyWindow::on_calendar_day_selected() {
    guint year, month, day;
    m_calendar.get_date(year, month, day);
    Glib::Date date(year, month + 1, day);

    auto it = m_events.find(date);
    if (it != m_events.end()) {
        m_event_label.set_text("Event: " + it->second);
    } else {
        m_event_label.set_text("No event for this date.");
    }
}

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    MyWindow window;

    return app->run(window);
}
