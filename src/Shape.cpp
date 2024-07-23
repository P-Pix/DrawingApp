#include "Shape.hpp"

Circle::Circle(double x, double y, double radius, const Gdk::RGBA& color)
    : x(x), y(y), radius(radius), color(color) {}

void Circle::draw(const Cairo::RefPtr<Cairo::Context>& cr) const {
    cr->set_source_rgba(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
    cr->arc(x, y, radius, 0, 2 * M_PI);
    cr->fill();
}

Polygon::Polygon(const std::vector<std::pair<double, double>>& points, const Gdk::RGBA& color)
    : points(points), color(color) {}

void Polygon::draw(const Cairo::RefPtr<Cairo::Context>& cr) const {
    if (points.empty()) return;
    
    cr->set_source_rgba(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
    cr->move_to(points[0].first, points[0].second);
    for (const auto& point : points) {
        cr->line_to(point.first, point.second);
    }
    cr->close_path();
    cr->fill();
}

Rectangle::Rectangle(double x, double y, double width, double height, const Gdk::RGBA& color)
    : Polygon({{x, y}, {x + width, y}, {x + width, y + height}, {x, y + height}}, color) {

    }

Square::Square(double x, double y, double side, const Gdk::RGBA& color)
    : Rectangle(x, y, side, side, color) {

    }

Triangle::Triangle(double x, double y, double side, const Gdk::RGBA& color)
    : Polygon({{x, y}, {x + side, y}, {x + side / 2, y + side * sqrt(3) / 2}}, color) {

    }

Heart::Heart(double x, double y, double side, const Gdk::RGBA& color)
    : Polygon({{x + side / 2, y + side / 4}, {x + side, y}, {x + side, y + side / 2}, {x + side / 2, y + side}, {x, y + side / 2}}, color) {

    }

Star::Star(double x, double y, double side, const Gdk::RGBA& color)
    : Polygon({{x + side / 2, y}, {x + 3 * side / 4, y + side / 3}, {x + side, y + side / 3}, {x + 5 * side / 6, y + 2 * side / 3}, {x + side, y + side}, {x + side / 2, y + 5 * side / 6}, {x, y + side}, {x + side / 6, y + 2 * side / 3}, {x, y + side / 3}, {x + side / 4, y + side / 3}}, color) {

    }