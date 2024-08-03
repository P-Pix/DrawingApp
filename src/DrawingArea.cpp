#include "DrawingArea.hpp"

DrawingArea::DrawingArea() : size_x(800), size_y(600) {
    set_size_request(this->size_x, this->size_y);
    srand(static_cast<unsigned>(time(nullptr))); // Seed pour les valeurs aléatoires
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

void DrawingArea::clear() {
    shapes.clear();
    queue_draw();
}

void DrawingArea::read_file(const std::string& filename) {
    this->clear();
    /*

    Polygon((364, 530), (404, 530), (404, 572), (364, 572), (140, 192, 94))
    Polygon((226, 551), (280, 551), (280, 571), (226, 571), (120, 111, 163))
    Circle(692, 422, 19, (78, 176, 4))
    Polygon((318, 588), (330, 604), (342, 604), (334, 620), (342, 636), (318, 628), (294, 636), (302, 620), (294, 604), (306, 604), (243, 111, 3))
    Polygon((319.5, 442.25), (348, 428), (348, 456.5), (319.5, 485), (291, 456.5), (189, 197, 5))
    
    */
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }
    std::cout << "Lecture du fichier " << filename << std::endl;
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find('{');
        if (pos == std::string::npos) {
            continue;
        }
        std::string type = line.substr(0, pos);
        if (type == "Circle") {
            // Circle{692, 422, 19, [78, 176, 4]}
            int x, y, radius, r, g, b;
            Gdk::RGBA color;
            sscanf(line.c_str(), "Circle{%d, %d, %d, [%d, %d, %d]}", &x, &y, &radius, &r, &g, &b);
            color.set_rgba(r / 255.0, g / 255.0, b / 255.0);
            shapes.push_back(std::make_shared<Circle>(x, y, radius, color));
        } else if (type == "Polygon") {
            // Polygon{(319.5, 442.25), (348, 428), (348, 456.5), (319.5, 485), (291, 456.5), [189, 197, 5]}
            std::vector<std::pair<double, double>> points;
            int x, y, r, g, b;
            Gdk::RGBA color;
            size_t start = pos + 1;
            size_t end = line.find('}', start);
            std::string points_str = line.substr(start, end - start);
            size_t pos = points_str.find('(');
            while (pos != std::string::npos) {
                size_t end = points_str.find(')', pos);
                std::string point_str = points_str.substr(pos + 1, end - pos - 1);
                sscanf(point_str.c_str(), "%d, %d", &x, &y);
                points.emplace_back(x, y);
                pos = points_str.find('(', end);
            }
            sscanf(line.c_str(), "Polygon{%*[^[][%d, %d, %d]}", &r, &g, &b);
            color.set_rgba(r / 255.0, g / 255.0, b / 255.0);
            shapes.push_back(std::make_shared<Polygon>(points, color));
        } else {
            std::cout << "Type inconnue : " << line << std::endl;
        }
    }
    file.close();
    queue_draw();
}

void DrawingArea::save_file(const std::string& filename) {
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }
    for (const auto& shape : shapes) {
        file << *shape.get() << std::endl;
    }
    file.close();
}