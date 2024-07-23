#include "DrawingArea.hpp"

DrawingArea::DrawingArea() : size_x(800), size_y(600) {
    set_size_request(this->size_x, this->size_y);
    srand(static_cast<unsigned>(time(0))); // Seed pour les valeurs aléatoires
}

DrawingArea::~DrawingArea() {
    // destructeur virtuel
}

void DrawingArea::add_circle() {
    double x = rand() % this->size_x;
    double y = rand() % this->size_y;
    double radius = (rand() % 50) + 10;
    Gdk::RGBA color;
    color.set_rgba(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX));
    shapes.push_back(std::make_shared<Circle>(x, y, radius, color));
    queue_draw();
}

void DrawingArea::add_polygon() {
    int sides = (rand() % 5) + 3; // Polygone avec entre 3 et 7 côtés
    double center_x = rand() % this->size_x;
    double center_y = rand() % this->size_y;
    std::vector<std::pair<double, double>> points;
    for (int i = 0; i < sides; ++i) {
        double angle = 2 * M_PI * i / sides;
        double radius = (rand() % 50) + 10;
        double x = center_x + radius * cos(angle);
        double y = center_y + radius * sin(angle);
        points.emplace_back(x, y);
    }
    Gdk::RGBA color;
    color.set_rgba(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX));
    shapes.push_back(std::make_shared<Polygon>(points, color));
    queue_draw();
}

bool DrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // Fond blanc
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->rectangle(0, 0, width, height);
    cr->fill();

    // Dessiner toutes les formes stockées
    for (const auto& shape : shapes) {
        shape->draw(cr);
    }

    return true;
}

void DrawingArea::add_rectangle() {
    double x = rand() % this->size_x;
    double y = rand() % this->size_y;
    double width = (rand() % 50) + 10;
    double height = (rand() % 50) + 10;
    Gdk::RGBA color;
    color.set_rgba(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX));
    shapes.push_back(std::make_shared<Rectangle>(x, y, width, height, color));
    queue_draw();
}

void DrawingArea::add_square() {
    double x = rand() % this->size_x;
    double y = rand() % this->size_y;
    double side = (rand() % 50) + 10;
    Gdk::RGBA color;
    color.set_rgba(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX));
    shapes.push_back(std::make_shared<Square>(x, y, side, color));
    queue_draw();
}

void DrawingArea::add_triangle() {
    double x = rand() % this->size_x;
    double y = rand() % this->size_y;
    double side = (rand() % 50) + 10;
    Gdk::RGBA color;
    color.set_rgba(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX));
    shapes.push_back(std::make_shared<Triangle>(x, y, side, color));
    queue_draw();
}

void DrawingArea::add_star() {
    double x = rand() % this->size_x;
    double y = rand() % this->size_y;
    double side = (rand() % 50) + 10;
    Gdk::RGBA color;
    color.set_rgba(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX));
    shapes.push_back(std::make_shared<Star>(x, y, side, color));
    queue_draw();
}

void DrawingArea::add_heart() {
    double x = rand() % this->size_x;
    double y = rand() % this->size_y;
    double side = (rand() % 50) + 10;
    Gdk::RGBA color;
    color.set_rgba(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX));
    shapes.push_back(std::make_shared<Heart>(x, y, side, color));
    queue_draw();
}