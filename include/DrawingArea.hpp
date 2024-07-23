#ifndef DRAWINGAREA_HPP
#define DRAWINGAREA_HPP

#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Shape.hpp"
#include <gtkmm/drawingarea.h>

class DrawingArea : public Gtk::DrawingArea {
public:
    DrawingArea();
    virtual ~DrawingArea();

    void add_circle();
    void add_polygon();
    void add_rectangle();
    void add_square();
    void add_triangle();
    void add_star();
    void add_heart();

protected:
    // Surcharge du signal draw
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
    std::vector<std::shared_ptr<Shape>> shapes;
    int size_x, size_y;
};

#endif // DRAWINGAREA_HPP
