/* Author: Bas Zoeteman
 * Date of creation: 28-06-2024 */

#include "WorldController.hpp"

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix4.hpp"
#include "math.hpp"

#include <GLFW/glfw3.h>

WorldController::WorldController(World* world, Camera* camera, InputHandler* inputHandler)
: world(world), camera(camera), inputHandler(inputHandler),
  controls(inputHandler->getControls()), buttonActions(inputHandler->getButtonActions()) {}

Tile* WorldController::getTile() {
    Vector3 ndc = inputHandler->getNDCFromCursorPos();

    Ray ray = camera->ndcToRay(ndc);
    Vector3 worldPosition = ray.rayCastToXYPlane(0.0f);

    return world->getTileAt(worldPosition);
}

void WorldController::update(double deltaTime) {
    hoveredTile = getTile();
    if (hoveredTile != nullptr && buttonActions.at(GLFW_MOUSE_BUTTON_LEFT) == ButtonAction::PRESS) {
        if (selectedTile != nullptr) {
            selectedTile->setColor(selectedTileColor);
        }

        if (selectedTile == hoveredTile) {
            selectedTile = nullptr;
            return;
        }

        selectedTile = hoveredTile;
        selectedTileColor = selectedTile->getColor();
        selectedTile->setColor(Color(1.0f, 0.0f, 0.0f));
    }
}
