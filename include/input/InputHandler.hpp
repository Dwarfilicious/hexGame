/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024
 * Contains a class InputHandler that holds the functions
 * required for handling input. Makes use of the InputResponder
 * to respond to the received input. */

#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>

class InputHandler {
private:
    std::unordered_map<std::string, std::vector<int>> keybinds;
    std::unordered_map<int, bool> keyStates;

public:
    InputHandler(GLFWwindow* window);

    void handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    void handleMouse(int button, int state, int x, int y);

    const std::unordered_map<std::string, std::vector<int>>& getKeybinds() const { return keybinds; }
    const std::unordered_map<int, bool>& getKeyStates() const { return keyStates; }
};
