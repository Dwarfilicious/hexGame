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
#include "Color.hpp"

#include <unordered_map>
#include <string>
#include <vector>

class WorldController {
private:
    InputHandler* inputHandler;
    World* world;
    Camera* camera;

    Tile* hoveredTile = nullptr;
    Tile* selectedTile = nullptr;
    Color selectedTileColor = Color(1.0f, 1.0f, 1.0f);

    const std::unordered_map<std::string, std::vector<int>>& controls;
    const std::unordered_map<int, ButtonAction>& buttonActions;

    Tile* getTile();

public:
    WorldController(World* world, Camera* camera, InputHandler* inputHandler);

    void update(double deltaTime);
};
