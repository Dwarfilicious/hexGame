/* Author: Bas Zoeteman
 * Date of creation: 02-07-2024
 * FPSCounter class for counting frames per second
 * and to limit framerate. */

#pragma once

#include <GLFW/glfw3.h>
#include <string>

class FPSController {
private:
    GLFWwindow* window;
    double desiredFrameTime;
    unsigned int frameCount = 0;
    double lastTime = glfwGetTime();
    double fps = 0.0;

public:
    FPSController(GLFWwindow* window, double frameRateLimit) : window(window) {
        desiredFrameTime = 1.0 / frameRateLimit;
    }

    void calcFPS() {
        frameCount++;
        double currentTime = glfwGetTime();
        auto timeDiff = currentTime - lastTime;
        if (timeDiff >= 1.0) {
            fps = frameCount / timeDiff;
            frameCount = 0;
            lastTime = currentTime;
            std::string fpsTitle = "hexGame | FPS: " + std::to_string(fps);
            glfwSetWindowTitle(window, fpsTitle.c_str());
        }
    }

    void limitFPS(double start) {
        double end = glfwGetTime();
        double timeToWait = desiredFrameTime - (end - start);
        while (timeToWait > 0) {
            end = glfwGetTime();
            timeToWait = desiredFrameTime - (end - start);
        }
    }

    double getFPS() const {
        return fps;
    }
};
