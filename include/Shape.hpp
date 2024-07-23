#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <gdkmm/rgba.h>
#include <cairomm/context.h>
#include <vector>

/**
 *  \brief The Shape class
 *  Classe abstraite représentant une forme géométrique
 */
class Shape {
public:
    /**
     * \brief Destructeur virtuel
     * Destructeur virtuel pour permettre la destruction des objets dérivés
     */
    virtual ~Shape() {}
    virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const = 0;
};

class Circle : public Shape {
public:
    Circle(double x, double y, double radius, const Gdk::RGBA& color);
    void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override;

private:
    double x, y, radius;
    Gdk::RGBA color;
};

class Polygon : public Shape {
public:
    Polygon(const std::vector<std::pair<double, double>>& points, const Gdk::RGBA& color);
    void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override;

private:
    std::vector<std::pair<double, double>> points;
    Gdk::RGBA color;
};

class Rectangle : public Polygon {
public:
    Rectangle(double x, double y, double width, double height, const Gdk::RGBA& color);
};

class Square : public Rectangle {
public:
    Square(double x, double y, double side, const Gdk::RGBA& color);
};

class Triangle : public Polygon {
public:
    Triangle(double x, double y, double side, const Gdk::RGBA& color);
};

class Heart : public Polygon {
public:
    Heart(double x, double y, double side, const Gdk::RGBA& color);
};

class Star : public Polygon {
public:
    Star(double x, double y, double side, const Gdk::RGBA& color);
};

#endif // SHAPE_HPP
