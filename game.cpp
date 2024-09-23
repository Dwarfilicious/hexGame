/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Main executable for the game */

#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "OpenGLRenderer.hpp"
#include "InputHandler.hpp"
#include "CameraController.hpp"
#include "WorldController.hpp"
#include "diagnostics/FPSController.hpp"

#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
    World world = World::pangaeaMap(60, 38);

    Vector3 cameraPosition(0.0f, 0.0f, 10.0f);
    Quaternion cameraRotation(1.0f, 0.0f, 0.0f, 0.0f);
    Camera camera(Transform(cameraPosition, cameraRotation));

    OpenGLRenderer renderer(argc, argv, world.getEntityContainer(), camera);

    InputHandler inputHandler(renderer.getWindow());
    CameraController cameraController(&camera, &inputHandler);
    WorldController worldController(&world, &camera, &inputHandler);

    double frameRateLimit = 240.0;
    FPSController fpsController(renderer.getWindow(), frameRateLimit);

    while (!glfwWindowShouldClose(renderer.getWindow())) {
        double start = glfwGetTime();

        inputHandler.resetButtonActions();
        glfwPollEvents();

        double deltaTime = renderer.calcDeltaTime();
        cameraController.update(deltaTime);
        worldController.update(deltaTime);

        renderer.render();
        glfwSwapBuffers(renderer.getWindow());

        fpsController.calcFPS();
        fpsController.limitFPS(start);
    }

    return 0;
}
