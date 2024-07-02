/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024 */

#include "InputHandler.hpp"
#include "ControlsMap.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

std::unordered_map<std::string, std::vector<int>> loadControls() {
    std::unordered_map<std::string, std::vector<int>> controls;

    std::string filename = "controls.json";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return controls;
    }

    nlohmann::json json;
    file >> json;

    for (const auto& buttons : json.items()) {
        std::string action = buttons.key();
        std::vector<int> buttonsList;
        for (const auto& value : buttons.value()) {
            std::string buttonString = value.get<std::string>();
            if (glfwControlsMap.find(buttonString) != glfwControlsMap.end()) {
                buttonsList.push_back(glfwControlsMap[buttonString]);
            } else {
                std::cerr << "Unknown key: " << buttonString << std::endl;
            }
        }
        controls[action] = buttonsList;
    }

    return controls;
}

InputHandler* gHandler = nullptr;

void globalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    gHandler->handleKeyboard(window, key, scancode, action, mods);
}

void globalMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    gHandler->handleMouseButton(window, button, action, mods);
}

void globalCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    gHandler->handleCursorPos(window, xpos, ypos);
}

void globalScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    gHandler->handleScroll(window, xoffset, yoffset);
}

InputHandler::InputHandler(GLFWwindow* window) : window(window) {
    controls = loadControls();
    for (auto& buttons : controls) {
        for (auto& button : buttons.second) {
            buttonStates[button] = false;
            buttonActions[button] = ButtonAction::NONE;
        }
    }
    buttonStates[GLFW_MOUSE_BUTTON_LEFT] = false;
    buttonStates[GLFW_MOUSE_BUTTON_RIGHT] = false;
    buttonStates[GLFW_KEY_ESCAPE] = false;
    buttonActions[GLFW_MOUSE_BUTTON_LEFT] = ButtonAction::NONE;
    buttonActions[GLFW_MOUSE_BUTTON_RIGHT] = ButtonAction::NONE;
    buttonActions[GLFW_KEY_ESCAPE] = ButtonAction::NONE;

    gHandler = this;
    glfwSetKeyCallback(window, globalKeyCallback);
    glfwSetMouseButtonCallback(window, globalMouseButtonCallback);
    glfwSetCursorPosCallback(window, globalCursorPosCallback);
    glfwSetScrollCallback(window, globalScrollCallback);
}

void InputHandler::handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (buttonStates.find(key) != buttonStates.end()) {
        buttonStates[key] = (action == GLFW_PRESS || action == GLFW_REPEAT);
        buttonActions[key] = static_cast<ButtonAction>(action);
    }
}

void InputHandler::handleMouseButton(GLFWwindow* window, int button, int action, int mods) {
    if (buttonStates.find(button) != buttonStates.end()) {
        buttonStates[button] = (action == GLFW_PRESS);
        buttonActions[button] = static_cast<ButtonAction>(action);
    }
}

void InputHandler::handleCursorPos(GLFWwindow* window, double xpos, double ypos) {
    // Do nothing
}

void InputHandler::handleScroll(GLFWwindow* window, double xoffset, double yoffset) {
    // Do nothing
}

void InputHandler::resetButtonActions() {
    for (auto& button : buttonActions) {
        button.second = ButtonAction::NONE;
    }
}

void InputHandler::getWindowSize(int& width, int& height) const {
    glfwGetWindowSize(window, &width, &height);
}
