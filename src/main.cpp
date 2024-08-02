/* DrawingApp - A simple drawing application using gtkmm
 *
 * Copyright (C) 2024  The DrawingApp Authors
 *
 * This program is free software: you can redistribute it and/or modify
 */

/** @mainpage DrawingApp
 *
 * @section intro Introduction
 *
 * DrawingApp is a simple drawing application using gtkmm. It allows the user to
 * draw various shapes on a canvas. The user can choose the shape to draw from a 
 *
 * @section features Features
 * - Draw various shapes on a canvas
 * - Save the drawing to a file
 * - Load a drawing from a file
 * - Undo the last action
 * - Redo the last undone action
 * - Clear the canvas
 * - Change the color of the shapes
 * - Change the size of the shapes
 * - Change the background color of the canvas
 *
 * @section basics Basic Usage
 * @code
 * make init
 * make run
 * @endcode
 */

#include <gtkmm/application.h>
#include "MainWindow.hpp"

/**
 * \brief Main function
 */
int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    MainWindow window;
    return app->run(window);
}
