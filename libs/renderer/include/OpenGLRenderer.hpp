/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Version of the renderer using OpenGL. */

#pragma once

#include "EntityContainer.hpp"
#include "Camera.hpp"

#include <GLFW/glfw3.h>

class OpenGLRenderer {
private:
    const EntityContainer& entityContainer;
    const Camera& camera;
    GLFWwindow* window;

public:
    OpenGLRenderer(int argc, char** argv, const EntityContainer& entityContainer, const Camera& camera);

    GLFWwindow* getWindow() const { return window; }

    void render();
    float calcDeltaTime();
};
