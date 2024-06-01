/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024 */

#include "math.hpp"
#include "InputResponder.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Transform.hpp"

InputResponder::InputResponder(Camera* camera) {
    this->camera = camera;
}

#include <iostream>

void InputResponder::handleKeyboard(unsigned char key, int x, int y) {
    const Transform& cameraTransform = camera->getTransform();
    Vector3 cameraPosition = cameraTransform.position;
    Quaternion cameraRotation = cameraTransform.rotation;

    switch (key) {
        case 'w':
            cameraPosition += cameraRotation * Vector3(0.0f, 1.0f, 0.0f);
            break;
        case 's':
            cameraPosition += cameraRotation * Vector3(0.0f, -1.0f, 0.0f);
            break;
        case 'a':
            cameraPosition += cameraRotation * Vector3(-1.0f, 0.0f, 0.0f);
            break;
        case 'd':
            cameraPosition += cameraRotation * Vector3(1.0f, 0.0f, 0.0f);
            break;
    }

    camera->setTransform(Transform(cameraPosition, cameraRotation));
}

void InputResponder::handleMouse(int button, int state, int x, int y) {
    const Transform& cameraTransform = camera->getTransform();
    Vector3 cameraPosition = cameraTransform.position;
    Quaternion cameraRotation = cameraTransform.rotation;
}
