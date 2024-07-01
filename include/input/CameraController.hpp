/* Author: Bas Zoeteman
 * Date of creation: 28-06-2024
 * Contains a class CameraController that holds the functions
 * required for controlling the camera. */

#pragma once

#include "Camera.hpp"
#include "InputHandler.hpp"

#include <unordered_map>
#include <string>
#include <vector>

class CameraController {
private:
    Camera* camera;
    InputHandler* inputHandler;

    const std::unordered_map<std::string, std::vector<int>>& controls;
    const std::unordered_map<int, bool>& buttonStates;

    void cameraMovement(double deltaTime);

public:
    CameraController(Camera* camera, InputHandler* inputHandler);

    void update(double deltaTime);
};
