/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024
 * Contains a class InputResponder that holds the functions
 * that dictate how a response is made to input. */

#pragma once

#include "Camera.hpp"

#include <unordered_map>
#include <string>
#include <vector>

class InputResponder {
private:
    Camera* camera;
    std::unordered_map<std::string, std::vector<int>> keybinds;
    std::unordered_map<int, bool> keyStates;

public:
    InputResponder(Camera* camera);

    void handleKeyboard(int key, int action, int mods);
    void handleMouse(int button, int state, int x, int y);

    void update(float deltaTime);
};