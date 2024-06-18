/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024 */

#include "math.hpp"
#include "InputResponder.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Transform.hpp"

InputResponder::InputResponder(Camera* camera) {
    this->camera = camera;
    keyStates['w'] = false;
    keyStates['s'] = false;
    keyStates['a'] = false;
    keyStates['d'] = false;
}

void InputResponder::handleKeyboard(unsigned char key, int x, int y) {
    keyStates[key] = true;
}

void InputResponder::handleKeyboardUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

void InputResponder::handleMouse(int button, int state, int x, int y) {
    const Transform& cameraTransform = camera->getTransform();
    Vector3 cameraPosition = cameraTransform.position;
    Quaternion cameraRotation = cameraTransform.rotation;
}

#include <iostream>

void InputResponder::update(float deltaTime) {
    const Transform& cameraTransform = camera->getTransform();
    Vector3 cameraPosition = cameraTransform.position;
    Quaternion cameraRotation = cameraTransform.rotation;

    Vector3 cameraDirection = Vector3(0.0f, 0.0f, 0.0f);
    if (keyStates['w']) {
        cameraDirection += Vector3(0.0f, 1.0f, 0.0f);
    }
    if (keyStates['s']) {
        cameraDirection += Vector3(0.0f, -1.0f, 0.0f);
    }
    if (keyStates['a']) {
        cameraDirection += Vector3(-1.0f, 0.0f, 0.0f);
    }
    if (keyStates['d']) {
        cameraDirection += Vector3(1.0f, 0.0f, 0.0f);
    }

    if (cameraDirection.magnitude() > 0.0f) {
        cameraDirection.normalize();
        camera->move(cameraDirection * camera->getCameraVelocity() * deltaTime);
    }

    std::cout << cameraPosition.x << " " << cameraPosition.y << " " << cameraPosition.z << std::endl;
}
