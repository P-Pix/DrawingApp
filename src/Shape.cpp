#include "Shape.hpp"

Circle::Circle(double x, double y, double radius, const Gdk::RGBA& color)
    : x(x), y(y), radius(radius) {
        this->color = color;
    }

void Circle::draw(const Cairo::RefPtr<Cairo::Context>& cr) const {
    cr->set_source_rgba(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
    cr->arc(x, y, radius, 0, 2 * M_PI);
    cr->fill();
}

std::ostream& Circle::to_string(std::ostream& os) const {
    return os << "Circle{" << this->x << ", " << this->y << ", " << this->radius << ", " << this->get_Color() << "}";
}

Polygon::Polygon(const std::vector<std::pair<double, double>>& points, const Gdk::RGBA& color)
    : points(points) {
        this->color = color;
    }

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

std::ostream& Polygon::to_string(std::ostream& os) const {
    os << "Polygon{";
    for (const auto& point : points) {
        os << "(" << point.first << ", " << point.second << "), ";
    }
    os << this->get_Color() << "}";
    return os;
}

std::string Shape::get_Color() const {
    std::string s = "[";
    s += std::to_string((int)(this->color.get_red()* 255)) + ", ";
    s += std::to_string((int)(this->color.get_green() * 255)) + ", ";
    s += std::to_string((int)(this->color.get_blue() * 255)) + "]";
    return s;
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