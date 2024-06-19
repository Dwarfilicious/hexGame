/* Author: Bas Zoeteman
 * Date of creation: 19-06-2024 */

#include "EntityContainer.hpp"
#include "Entity.hpp"

void EntityContainer::addEntity(std::unique_ptr<Entity> entity) {
    entities.push_back(std::move(entity));
}

const std::vector<std::unique_ptr<Entity>>& EntityContainer::getEntities() const {
    return entities;
}
