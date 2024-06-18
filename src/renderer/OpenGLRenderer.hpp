/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Version of the renderer using OpenGL. */

#pragma once

#include "World.hpp"
#include "Camera.hpp"

class OpenGLRenderer {
private:
    const World& world;
    const Camera& camera;

public:
    OpenGLRenderer(int argc, char** argv, const World& world, const Camera& camera);

    void render();
    float calcDeltaTime();
};
