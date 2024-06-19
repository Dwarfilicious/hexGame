/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024
 * Contains a class InputHandler that holds the functions
 * required for handling input. Makes use of the InputResponder
 * to respond to the received input. */

#pragma once

#include "InputResponder.hpp"
#include "Camera.hpp"

#include <GLFW/glfw3.h>

class InputHandler {
private:
    InputResponder* responder;

public:
    InputHandler(Camera* camera, GLFWwindow* window);

    void handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    void handleMouse(int button, int state, int x, int y);

    void update(float deltaTime);
};
