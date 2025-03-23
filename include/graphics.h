#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Plane.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "settings.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// callback functions
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// initialize
GLFWwindow *init_glfw();
bool        init_glad();
void        init_scene(Scene &scene);

// render
void render_loop(GLFWwindow *window);

#endif