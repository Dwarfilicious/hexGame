/* Author: Bas Zoeteman
 * Date of creation: 28-06-2024
 * Contains a class WorldController, which holds the functions
 * required for interacting with the world. */

#pragma once

#include "InputHandler.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Tile.hpp"
#include "Vector3.hpp"

#include <unordered_map>
#include <string>
#include <vector>

class WorldController {
private:
    InputHandler* inputHandler;
    World* world;
    Camera* camera;

    Tile* selectedTile;

    const std::unordered_map<std::string, std::vector<int>>& controls;
    const std::unordered_map<int, bool>& buttonStates;

    Vector3 screenToWorld(const Vector3& mousePosition) const;
    void selectTile();

public:
    WorldController(World* world, Camera* camera, InputHandler* inputHandler);

    void update(double deltaTime);
};
