/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024 */

#include "InputHandler.hpp"
#include "KeybindsMap.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

std::unordered_map<std::string, std::vector<int>> loadKeybinds() {
    std::unordered_map<std::string, std::vector<int>> keybinds;

    std::string filename = "controls.json";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return keybinds;
    }

    nlohmann::json json;
    file >> json;

    for (const auto& keybind : json.items()) {
        std::string action = keybind.key();
        std::vector<int> keys;
        for (const auto& value : keybind.value()) {
            std::string keyString = value.get<std::string>();
            if (glfwKeyMap.find(keyString) != glfwKeyMap.end()) {
                keys.push_back(glfwKeyMap[keyString]);
            } else {
                std::cerr << "Unknown key: " << keyString << std::endl;
            }
        }
        keybinds[action] = keys;
    }

    return keybinds;
}

InputHandler* gHandler = nullptr;

void globalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    gHandler->handleKeyboard(window, key, scancode, action, mods);
}

InputHandler::InputHandler(GLFWwindow* window) {
    keybinds = loadKeybinds();
    for (auto& keybind : keybinds) {
        for (auto& key : keybind.second) {
            keyStates[key] = false;
        }
    }
    gHandler = this;
    glfwSetKeyCallback(window, globalKeyCallback);
}

void InputHandler::handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (keyStates.find(key) != keyStates.end()) {
        keyStates[key] = (action == GLFW_PRESS || action == GLFW_REPEAT);
    }
}
