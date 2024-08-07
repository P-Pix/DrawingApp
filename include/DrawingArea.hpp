#ifndef DRAWINGAREA_HPP
#define DRAWINGAREA_HPP

#include <gtkmm/drawingarea.h>
#include <fstream>
#include "Shape.hpp"

enum ShapeType : int {
    CIRCLE,
    POLYGON
};

class DrawingArea : public Gtk::DrawingArea {
public:
    DrawingArea();
    virtual ~DrawingArea();

    void clear();
    void read_file(const std::string& filename);
    void save_file(const std::string& filename);

    void open_picture(const std::string& filename);

    void add_circle();
    void add_polygon();
    void add_rectangle();
    void add_square();
    void add_triangle();
    void add_star();
    void add_heart();

    void add_Manual_Circle();
    void add_Manual_Polygon();

protected:
    // Surcharge du signal draw
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_button_press_event(GdkEventButton* event) override;
    bool on_key_press_event(GdkEventKey* event) override;

private:
    std::vector<std::shared_ptr<Shape>> shapes;
    unsigned int size_x, size_y;

    bool create_Shape_mode = false;
    std::vector<std::pair<double, double>> coordinates_create_Shape_mode;
    int type_Shape;
    void add_Manual(int type_Shape);
};
#endif // DRAWINGAREA_HPP
