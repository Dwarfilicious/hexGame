/* Author: Bas Zoeteman
 * Date of creation: 28-06-2024 */

#include "CameraController.hpp"

CameraController::CameraController(Camera* camera, InputHandler* inputHandler)
: camera(camera), inputHandler(inputHandler),
  keybinds(inputHandler->getKeybinds()), keyStates(inputHandler->getKeyStates()) {}

void CameraController::update(double deltaTime) {
    const Transform& cameraTransform = camera->getTransform();
    Vector3 cameraPosition = cameraTransform.position;
    Quaternion cameraRotation = cameraTransform.rotation;

    Vector3 cameraDirection = Vector3(0.0f, 0.0f, 0.0f);
    for (const auto& key : keybinds.at("move_up")) {
        if (keyStates.at(key)) {
            cameraDirection += Vector3(0.0f, 1.0f, 0.0f);
        }
    }
    for (const auto& key : keybinds.at("move_down")) {
        if (keyStates.at(key)) {
            cameraDirection += Vector3(0.0f, -1.0f, 0.0f);
        }
    }
    for (const auto& key : keybinds.at("move_left")) {
        if (keyStates.at(key)) {
            cameraDirection += Vector3(-1.0f, 0.0f, 0.0f);
        }
    }
    for (const auto& key : keybinds.at("move_right")) {
        if (keyStates.at(key)) {
            cameraDirection += Vector3(1.0f, 0.0f, 0.0f);
        }
    }

    if (cameraDirection.magnitude() > 0.0f) {
        cameraDirection.normalize();
        camera->move(cameraDirection * camera->getCameraVelocity() * deltaTime);
    }
}
