/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024 */

#include "math.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Transform.hpp"
#include "InputResponder.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <GLFW/glfw3.h>

std::unordered_map<std::string, int> glfwKeyMap = {
    {"GLFW_KEY_SPACE", GLFW_KEY_SPACE},
    {"GLFW_KEY_APOSTROPHE", GLFW_KEY_APOSTROPHE},
    {"GLFW_KEY_COMMA", GLFW_KEY_COMMA},
    {"GLFW_KEY_MINUS", GLFW_KEY_MINUS},
    {"GLFW_KEY_PERIOD", GLFW_KEY_PERIOD},
    {"GLFW_KEY_SLASH", GLFW_KEY_SLASH},
    {"GLFW_KEY_0", GLFW_KEY_0},
    {"GLFW_KEY_1", GLFW_KEY_1},
    {"GLFW_KEY_2", GLFW_KEY_2},
    {"GLFW_KEY_3", GLFW_KEY_3},
    {"GLFW_KEY_4", GLFW_KEY_4},
    {"GLFW_KEY_5", GLFW_KEY_5},
    {"GLFW_KEY_6", GLFW_KEY_6},
    {"GLFW_KEY_7", GLFW_KEY_7},
    {"GLFW_KEY_8", GLFW_KEY_8},
    {"GLFW_KEY_9", GLFW_KEY_9},
    {"GLFW_KEY_SEMICOLON", GLFW_KEY_SEMICOLON},
    {"GLFW_KEY_EQUAL", GLFW_KEY_EQUAL},
    {"GLFW_KEY_A", GLFW_KEY_A},
    {"GLFW_KEY_B", GLFW_KEY_B},
    {"GLFW_KEY_C", GLFW_KEY_C},
    {"GLFW_KEY_D", GLFW_KEY_D},
    {"GLFW_KEY_E", GLFW_KEY_E},
    {"GLFW_KEY_F", GLFW_KEY_F},
    {"GLFW_KEY_G", GLFW_KEY_G},
    {"GLFW_KEY_H", GLFW_KEY_H},
    {"GLFW_KEY_I", GLFW_KEY_I},
    {"GLFW_KEY_J", GLFW_KEY_J},
    {"GLFW_KEY_K", GLFW_KEY_K},
    {"GLFW_KEY_L", GLFW_KEY_L},
    {"GLFW_KEY_M", GLFW_KEY_M},
    {"GLFW_KEY_N", GLFW_KEY_N},
    {"GLFW_KEY_O", GLFW_KEY_O},
    {"GLFW_KEY_P", GLFW_KEY_P},
    {"GLFW_KEY_Q", GLFW_KEY_Q},
    {"GLFW_KEY_R", GLFW_KEY_R},
    {"GLFW_KEY_S", GLFW_KEY_S},
    {"GLFW_KEY_T", GLFW_KEY_T},
    {"GLFW_KEY_U", GLFW_KEY_U},
    {"GLFW_KEY_V", GLFW_KEY_V},
    {"GLFW_KEY_W", GLFW_KEY_W},
    {"GLFW_KEY_X", GLFW_KEY_X},
    {"GLFW_KEY_Y", GLFW_KEY_Y},
    {"GLFW_KEY_Z", GLFW_KEY_Z},
    {"GLFW_KEY_LEFT_BRACKET", GLFW_KEY_LEFT_BRACKET},
    {"GLFW_KEY_BACKSLASH", GLFW_KEY_BACKSLASH},
    {"GLFW_KEY_RIGHT_BRACKET", GLFW_KEY_RIGHT_BRACKET},
    {"GLFW_KEY_GRAVE_ACCENT", GLFW_KEY_GRAVE_ACCENT},
    {"GLFW_KEY_WORLD_1", GLFW_KEY_WORLD_1},
    {"GLFW_KEY_WORLD_2", GLFW_KEY_WORLD_2},
    {"GLFW_KEY_ESCAPE", GLFW_KEY_ESCAPE},
    {"GLFW_KEY_ENTER", GLFW_KEY_ENTER},
    {"GLFW_KEY_TAB", GLFW_KEY_TAB},
    {"GLFW_KEY_BACKSPACE", GLFW_KEY_BACKSPACE},
    {"GLFW_KEY_INSERT", GLFW_KEY_INSERT},
    {"GLFW_KEY_DELETE", GLFW_KEY_DELETE},
    {"GLFW_KEY_RIGHT", GLFW_KEY_RIGHT},
    {"GLFW_KEY_LEFT", GLFW_KEY_LEFT},
    {"GLFW_KEY_DOWN", GLFW_KEY_DOWN},
    {"GLFW_KEY_UP", GLFW_KEY_UP},
    {"GLFW_KEY_PAGE_UP", GLFW_KEY_PAGE_UP},
    {"GLFW_KEY_PAGE_DOWN", GLFW_KEY_PAGE_DOWN},
    {"GLFW_KEY_HOME", GLFW_KEY_HOME},
    {"GLFW_KEY_END", GLFW_KEY_END},
    {"GLFW_KEY_CAPS_LOCK", GLFW_KEY_CAPS_LOCK},
    {"GLFW_KEY_SCROLL_LOCK", GLFW_KEY_SCROLL_LOCK},
    {"GLFW_KEY_NUM_LOCK", GLFW_KEY_NUM_LOCK},
    {"GLFW_KEY_PRINT_SCREEN", GLFW_KEY_PRINT_SCREEN},
    {"GLFW_KEY_PAUSE", GLFW_KEY_PAUSE},
    {"GLFW_KEY_F1", GLFW_KEY_F1},
    {"GLFW_KEY_F2", GLFW_KEY_F2},
    {"GLFW_KEY_F3", GLFW_KEY_F3},
    {"GLFW_KEY_F4", GLFW_KEY_F4},
    {"GLFW_KEY_F5", GLFW_KEY_F5},
    {"GLFW_KEY_F6", GLFW_KEY_F6},
    {"GLFW_KEY_F7", GLFW_KEY_F7},
    {"GLFW_KEY_F8", GLFW_KEY_F8},
    {"GLFW_KEY_F9", GLFW_KEY_F9},
    {"GLFW_KEY_F10", GLFW_KEY_F10},
    {"GLFW_KEY_F11", GLFW_KEY_F11},
    {"GLFW_KEY_F12", GLFW_KEY_F12},
    {"GLFW_KEY_F13", GLFW_KEY_F13},
    {"GLFW_KEY_F14", GLFW_KEY_F14},
    {"GLFW_KEY_F15", GLFW_KEY_F15},
    {"GLFW_KEY_F16", GLFW_KEY_F16},
    {"GLFW_KEY_F17", GLFW_KEY_F17},
    {"GLFW_KEY_F18", GLFW_KEY_F18},
    {"GLFW_KEY_F19", GLFW_KEY_F19},
    {"GLFW_KEY_F20", GLFW_KEY_F20},
    {"GLFW_KEY_F21", GLFW_KEY_F21},
    {"GLFW_KEY_F22", GLFW_KEY_F22},
    {"GLFW_KEY_F23", GLFW_KEY_F23},
    {"GLFW_KEY_F24", GLFW_KEY_F24},
    {"GLFW_KEY_F25", GLFW_KEY_F25},
    {"GLFW_KEY_KP_0", GLFW_KEY_KP_0},
    {"GLFW_KEY_KP_1", GLFW_KEY_KP_1},
    {"GLFW_KEY_KP_2", GLFW_KEY_KP_2},
    {"GLFW_KEY_KP_3", GLFW_KEY_KP_3},
    {"GLFW_KEY_KP_4", GLFW_KEY_KP_4},
    {"GLFW_KEY_KP_5", GLFW_KEY_KP_5},
    {"GLFW_KEY_KP_6", GLFW_KEY_KP_6},
    {"GLFW_KEY_KP_7", GLFW_KEY_KP_7},
    {"GLFW_KEY_KP_8", GLFW_KEY_KP_8},
    {"GLFW_KEY_KP_9", GLFW_KEY_KP_9},
    {"GLFW_KEY_KP_DECIMAL", GLFW_KEY_KP_DECIMAL},
    {"GLFW_KEY_KP_DIVIDE", GLFW_KEY_KP_DIVIDE},
    {"GLFW_KEY_KP_MULTIPLY", GLFW_KEY_KP_MULTIPLY},
    {"GLFW_KEY_KP_SUBTRACT", GLFW_KEY_KP_SUBTRACT},
    {"GLFW_KEY_KP_ADD", GLFW_KEY_KP_ADD},
    {"GLFW_KEY_KP_ENTER", GLFW_KEY_KP_ENTER},
    {"GLFW_KEY_KP_EQUAL", GLFW_KEY_KP_EQUAL},
    {"GLFW_KEY_LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT},
    {"GLFW_KEY_LEFT_CONTROL", GLFW_KEY_LEFT_CONTROL},
    {"GLFW_KEY_LEFT_ALT", GLFW_KEY_LEFT_ALT},
    {"GLFW_KEY_LEFT_SUPER", GLFW_KEY_LEFT_SUPER},
    {"GLFW_KEY_RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT},
    {"GLFW_KEY_RIGHT_CONTROL", GLFW_KEY_RIGHT_CONTROL},
    {"GLFW_KEY_RIGHT_ALT", GLFW_KEY_RIGHT_ALT},
    {"GLFW_KEY_RIGHT_SUPER", GLFW_KEY_RIGHT_SUPER},
    {"GLFW_KEY_MENU", GLFW_KEY_MENU}
};

std::unordered_map<std::string, std::vector<int>> loadKeybinds() {
    std::unordered_map<std::string, std::vector<int>> keybinds;

    std::string filename = "controls.json";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return keybinds;
    }

    nlohmann::json json;
    file >> json;

    for (const auto& keybind : json.items()) {
        std::string action = keybind.key();
        std::vector<int> keys;
        for (const auto& value : keybind.value()) {
            std::string keyString = value.get<std::string>();
            if (glfwKeyMap.find(keyString) != glfwKeyMap.end()) {
                keys.push_back(glfwKeyMap[keyString]);
            } else {
                std::cerr << "Unknown key: " << keyString << std::endl;
            }
        }
        keybinds[action] = keys;
    }

    return keybinds;
}

InputResponder::InputResponder(Camera* camera) {
    this->camera = camera;
    keybinds = loadKeybinds();
    for (auto& keybind : keybinds) {
        for (auto& key : keybind.second) {
            keyStates[key] = false;
        }
    }
}

void InputResponder::handleKeyboard(int key, int action, int mods) {
    if (keyStates.find(key) != keyStates.end()) {
        keyStates[key] = (action == GLFW_PRESS || action == GLFW_REPEAT);
    }
}

void InputResponder::handleMouse(int button, int state, int x, int y) {
    const Transform& cameraTransform = camera->getTransform();
    Vector3 cameraPosition = cameraTransform.position;
    Quaternion cameraRotation = cameraTransform.rotation;
}

void InputResponder::update(float deltaTime) {
    const Transform& cameraTransform = camera->getTransform();
    Vector3 cameraPosition = cameraTransform.position;
    Quaternion cameraRotation = cameraTransform.rotation;

    Vector3 cameraDirection = Vector3(0.0f, 0.0f, 0.0f);
    for (const auto& key : keybinds["move_up"]) {
        if (keyStates[key]) {
            cameraDirection += Vector3(0.0f, 1.0f, 0.0f);
        }
    }
    for (const auto& key : keybinds["move_down"]) {
        if (keyStates[key]) {
            cameraDirection += Vector3(0.0f, -1.0f, 0.0f);
        }
    }
    for (const auto& key : keybinds["move_left"]) {
        if (keyStates[key]) {
            cameraDirection += Vector3(-1.0f, 0.0f, 0.0f);
        }
    }
    for (const auto& key : keybinds["move_right"]) {
        if (keyStates[key]) {
            cameraDirection += Vector3(1.0f, 0.0f, 0.0f);
        }
    }

    if (cameraDirection.magnitude() > 0.0f) {
        cameraDirection.normalize();
        camera->move(cameraDirection * camera->getCameraVelocity() * deltaTime);
    }
}
