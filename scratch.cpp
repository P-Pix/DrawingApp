#include <gtkmm.h>
#include <iostream>

class Block : public Gtk::Frame {
public:
    Block(const Glib::ustring& label);
    virtual ~Block();

protected:
    // Signal handlers for drag and drop
    bool on_button_press_event(GdkEventButton* event) override;
    bool on_motion_notify_event(GdkEventMotion* event) override;
    bool on_button_release_event(GdkEventButton* event) override;

    bool m_Dragging;
    double m_OffsetX, m_OffsetY;
};

Block::Block(const Glib::ustring& label) : Gtk::Frame(label), m_Dragging(false) {
    set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    set_margin_start(5);
    set_margin_end(5);
    set_margin_top(5);
    set_margin_bottom(5);
    add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::POINTER_MOTION_MASK);
}

Block::~Block() {}

bool Block::on_button_press_event(GdkEventButton* event) {
    if (event->button == 1) { // Left mouse button
        m_Dragging = true;
        m_OffsetX = event->x;
        m_OffsetY = event->y;
        return true;
    }
    return false;
}

bool Block::on_motion_notify_event(GdkEventMotion* event) {
    if (m_Dragging) {
        auto parent = get_parent();
        if (parent) {
            auto container = dynamic_cast<Gtk::Fixed*>(parent);
            if (container) {
                container->move(*this, event->x_root - m_OffsetX, event->y_root - m_OffsetY);
            }
        }
        return true;
    }
    return false;
}

bool Block::on_button_release_event(GdkEventButton* event) {
    if (event->button == 1) { // Left mouse button
        m_Dragging = false;
        return true;
    }
    return false;
}

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();

protected:
    // Signal handlers
    void on_add_block_button_clicked();

    // Member widgets
    Gtk::Box m_VBox;
    Gtk::Button m_AddBlockButton;
    Gtk::Fixed m_Canvas;
};

MainWindow::MainWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_AddBlockButton("Add Block") {
    // Set the title and border of the window
    set_title("Scratch-like Editor");
    set_border_width(10);

    // Add the VBox to the main window
    add(m_VBox);

    // Add the AddBlockButton to the VBox
    m_VBox.pack_start(m_AddBlockButton, Gtk::PACK_SHRINK);

    // Connect the button signal to the handler
    m_AddBlockButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_add_block_button_clicked));

    // Add the Canvas to the VBox
    m_VBox.pack_start(m_Canvas);

    // Set the Canvas size
    m_Canvas.set_size_request(800, 600);

    // Show all children of the window
    show_all_children();
}

MainWindow::~MainWindow() {}

void MainWindow::on_add_block_button_clicked() {
    // Create a new block and add it to the Canvas
    auto block = Gtk::make_managed<Block>("New Block");
    m_Canvas.put(*block, 10, 10); // Initial position
    block->show();
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    MainWindow window;

    // Shows the window and returns when it is closed
    return app->run(window);
}
