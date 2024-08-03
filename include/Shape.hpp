#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <gdkmm/rgba.h>
#include <cairomm/context.h>
#include <vector>
#include <iostream>

/**
 *  \brief The Shape class\n
 *  Classe abstraite représentant une forme géométrique
 */
class Shape {
public:
    /**
     * \brief Destructeur virtuel\n
     * Destructeur virtuel pour permettre la destruction des objets dérivés
     */
    virtual ~Shape() {}

    /**
     * \brief Méthode de dessin\n
     * Méthode virtuelle pure permettant de dessiner la forme
     * \param cr Référence vers le contexte Cairo
     */
    virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const = 0;

    /**
     * \brief fonction servant de reférentiel pour l'écriture du Shape
     */
    virtual std::ostream& to_string(std::ostream& os) const = 0;

    /**
     * \brief Permet d'optenir les valeurs RGB du Shape en (uint8, uint8, uint8)
     * \return en string les valeur RGB du Shape (uint8, uint8, uint8)
     */
    std::string get_Color() const;

    /**
     * \brief Fonction servant à l'affichage de la Shape\n
     * Sert également pour la fonction d'écriture dans le fichier pour la sauvegarde de DrawingArea.hpp
     */
    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        return shape.to_string(os);
    }

protected:
    Gdk::RGBA color;
};

class Circle : public Shape {
public:
    Circle(double x, double y, double radius, const Gdk::RGBA& color);
    void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override;
    std::ostream& to_string(std::ostream& os) const override;

private:
    double x, y, radius;
};

/**
 *  \brief The Polygon class\n
 *  Classe représentant un polygone\n
 *  Un polygone est défini par une liste de points\n
 */
class Polygon : public Shape {
public:
    Polygon(const std::vector<std::pair<double, double>>& points, const Gdk::RGBA& color);
    void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override;
    std::ostream& to_string(std::ostream& os) const override;

private:
    std::vector<std::pair<double, double>> points;
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