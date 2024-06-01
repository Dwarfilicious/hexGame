/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Contains a test to check whether the rendering
 * is working correctly. */

#include "World.hpp"
#include "Camera.hpp"
#include "OpenGLRenderer.hpp"
#include "InputHandler.hpp"

#include <cmath>

int main(int argc, char** argv) {
    World world(80, 60, 1.0f);

    Vector3 cameraPosition(0.0f, 0.0f, 10.0f);
    Quaternion cameraRotation(1.0f, 0.0f, 0.0f, 0.0f);
    Camera camera(Transform(cameraPosition, cameraRotation));

    OpenGLRenderer renderer(argc, argv, world, camera);

    InputHandler inputHandler(&camera);

    renderer.run();

    return 0;
}
