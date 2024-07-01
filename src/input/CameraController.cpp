/* Author: Bas Zoeteman
 * Date of creation: 28-06-2024 */

#include "CameraController.hpp"

CameraController::CameraController(Camera* camera, InputHandler* inputHandler)
: camera(camera), inputHandler(inputHandler),
  controls(inputHandler->getControls()), buttonStates(inputHandler->getButtonStates()) {}

void CameraController::cameraMovement(double deltaTime) {
    const Transform& cameraTransform = camera->getTransform();
    Vector3 cameraPosition = cameraTransform.position;
    Quaternion cameraRotation = cameraTransform.rotation;

    Vector3 cameraDirection = Vector3(0.0f, 0.0f, 0.0f);
    for (const auto& button : controls.at("move_up")) {
        if (buttonStates.at(button)) {
            cameraDirection += Vector3(0.0f, 1.0f, 0.0f);
        }
    }
    for (const auto& button : controls.at("move_down")) {
        if (buttonStates.at(button)) {
            cameraDirection += Vector3(0.0f, -1.0f, 0.0f);
        }
    }
    for (const auto& button : controls.at("move_left")) {
        if (buttonStates.at(button)) {
            cameraDirection += Vector3(-1.0f, 0.0f, 0.0f);
        }
    }
    for (const auto& button : controls.at("move_right")) {
        if (buttonStates.at(button)) {
            cameraDirection += Vector3(1.0f, 0.0f, 0.0f);
        }
    }

    if (cameraDirection.magnitude() > 0.0f) {
        cameraDirection.normalize();
        camera->move(cameraDirection * camera->getCameraVelocity() * deltaTime);
    }
}

void CameraController::update(double deltaTime) {
    cameraMovement(deltaTime);
}
