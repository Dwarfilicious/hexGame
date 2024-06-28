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

#include <cmath>
#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
    World world(30, 25, 1.0f);

    Vector3 cameraPosition(0.0f, 0.0f, 10.0f);
    Quaternion cameraRotation(1.0f, 0.0f, 0.0f, 0.0f);
    Camera camera(Transform(cameraPosition, cameraRotation));

    OpenGLRenderer renderer(argc, argv, world.getEntityContainer(), camera);

    InputHandler inputHandler(renderer.getWindow());
    CameraController cameraController(&camera, &inputHandler);

    const double desiredFrameTime = 1.0 / 240.0;
    unsigned int frameCount = 0;
    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(renderer.getWindow())) {
        double start = glfwGetTime();

        glfwPollEvents();
        double deltaTime = renderer.calcDeltaTime();
        cameraController.update(deltaTime);
        renderer.render();
        glfwSwapBuffers(renderer.getWindow());

        frameCount++;
        double currentTime = glfwGetTime();
        auto timeDiff = currentTime - lastTime;
        if (timeDiff >= 1.0) {
            double fps = frameCount / timeDiff;
            frameCount = 0;
            lastTime = currentTime;
            std::string fpsTitle = "hexGame | FPS: " + std::to_string(fps);
            glfwSetWindowTitle(renderer.getWindow(), fpsTitle.c_str());
        }

        double end = glfwGetTime();
        double timeToWait = desiredFrameTime - (end - start);
        while (timeToWait > 0) {
            end = glfwGetTime();
            timeToWait = desiredFrameTime - (end - start);
        }
    }

    return 0;
}
