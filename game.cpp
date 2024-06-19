/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Main executable for the game */

#include "World.hpp"
#include "Camera.hpp"
#include "OpenGLRenderer.hpp"
#include "InputHandler.hpp"

#include <cmath>
#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
    World world(80, 60, 1.0f);

    Vector3 cameraPosition(0.0f, 0.0f, 10.0f);
    Quaternion cameraRotation(1.0f, 0.0f, 0.0f, 0.0f);
    Camera camera(Transform(cameraPosition, cameraRotation));

    OpenGLRenderer renderer(argc, argv, world, camera);

    InputHandler inputHandler(&camera, renderer.getWindow());

    const std::chrono::milliseconds desiredFrameTime(1000 / 240);
    while (!glfwWindowShouldClose(renderer.getWindow())) {
        auto start = std::chrono::steady_clock::now();

        float deltaTime = renderer.calcDeltaTime();
        inputHandler.update(deltaTime);
        renderer.render();
        glfwPollEvents();
        glfwSwapBuffers(renderer.getWindow());

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (elapsed < desiredFrameTime) {
            std::this_thread::sleep_for(desiredFrameTime - elapsed);
        }
    }

    return 0;
}
