/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024
 * Contains a class InputHandler that holds the functions
 * required for handling input. */

#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>

class InputHandler {
private:
    GLFWwindow* window;

    std::unordered_map<std::string, std::vector<int>> controls;
    std::unordered_map<int, bool> buttonStates;

public:
    InputHandler(GLFWwindow* window);

    void handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
    void handleCursorPos(GLFWwindow* window, double xpos, double ypos);
    void handleScroll(GLFWwindow* window, double xoffset, double yoffset);

    GLFWwindow* getWindow() const { return window; }
    void getWindowSize(int& width, int& height) const;

    const std::unordered_map<std::string, std::vector<int>>& getControls() const { return controls; }
    const std::unordered_map<int, bool>& getButtonStates() const { return buttonStates; }
};
