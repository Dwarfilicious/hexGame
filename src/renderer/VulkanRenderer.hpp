/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Version of the renderer using Vulkan.
 * Left on hold to focus on simpler OpenGL. */

#pragma once

#include "World.hpp"
#include "Camera.hpp"

#include <vulkan/vulkan.h>

class VulkanRenderer {
public:
    void Initialize();

    void Render(const World& world, const Camera& camera);
    // void RenderUI(const GameState& gameState) override;

private:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;

    bool IsDeviceSuitable(VkPhysicalDevice device);
    int FindQueueFamilies(VkPhysicalDevice device);
    void CreateLogicalDevice();
};
