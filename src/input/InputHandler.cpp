/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024 */

#include "InputHandler.hpp"

InputHandler* gHandler = nullptr;

void globalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    gHandler->handleKeyboard(window, key, scancode, action, mods);
}

InputHandler::InputHandler(Camera* camera, GLFWwindow* window) {
    responder = new InputResponder(camera);

    gHandler = this;
    glfwSetKeyCallback(window, globalKeyCallback);
}

void InputHandler::handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    responder->handleKeyboard(key, action, mods);
}

void InputHandler::update(float deltaTime) {
    responder->update(deltaTime);
}
