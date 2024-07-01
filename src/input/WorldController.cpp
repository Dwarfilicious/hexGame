/* Author: Bas Zoeteman
 * Date of creation: 28-06-2024 */

#include "WorldController.hpp"

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix4.hpp"
#include "math.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

WorldController::WorldController(World* world, Camera* camera, InputHandler* inputHandler)
: world(world), camera(camera), inputHandler(inputHandler),
  controls(inputHandler->getControls()), buttonStates(inputHandler->getButtonStates()) {}

// at some point, ray casting needs to be moved to be part of the engine
Vector3 rayCastFromCameraToXYPlane(Camera* camera, InputHandler* inputHandler) {
    // Step 1: Get Mouse Position
    double mouseX, mouseY;
    glfwGetCursorPos(inputHandler->getWindow(), &mouseX, &mouseY);

    // Step 2: Convert to NDC
    int screenWidth, screenHeight;
    inputHandler->getWindowSize(screenWidth, screenHeight);
    double ndcX = (2.0 * mouseX) / screenWidth - 1.0;
    double ndcY = 1.0 - (2.0 * mouseY) / screenHeight;

    // Step 3 & 4: Convert to Clip Coordinates and then to Eye Coordinates
    Vector4 clipCoords(ndcX, ndcY, -1.0, 1.0);
    Matrix4 inverseProjectionMatrix = Matrix4::inverse(camera->getProjectionMatrix());
    Vector4 eyeCoords = inverseProjectionMatrix * clipCoords;
    eyeCoords.z = -1.0; eyeCoords.w = 0.0;

    // Step 5: Convert to World Coordinates
    Matrix4 inverseViewMatrix = Matrix4::inverse(camera->getViewMatrix());
    Vector4 rayWorld = inverseViewMatrix * eyeCoords;
    Vector3 rayDirection(rayWorld.x, rayWorld.y, rayWorld.z);
    rayDirection.normalize();

    // Step 6: Ray-Plane Intersection
    Vector3 cameraPosition = camera->getTransform().position;
    float t = -cameraPosition.z / rayDirection.z; // Assuming camera is above the x,y-plane and looking downwards
    Vector3 intersectionPoint = cameraPosition + rayDirection * t;

    return intersectionPoint;
}

void WorldController::selectTile() {
    if (buttonStates.at(GLFW_MOUSE_BUTTON_LEFT)) {
        Vector3 worldPosition = rayCastFromCameraToXYPlane(camera, inputHandler);
        selectedTile = world->getTileAt(worldPosition);
    }
    else {
        selectedTile = nullptr;
    }
}

void WorldController::update(double deltaTime) {
    selectTile();
    if (selectedTile != nullptr) {
        selectedTile->setColor(Color(1.0f, 0.0f, 0.0f));
    }
}
