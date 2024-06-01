/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024
 * Contains a class InputResponder that holds the functions
 * that dictate how a response is made to input. */

#pragma once

#include "Camera.hpp"

class InputResponder {
private:
    Camera* camera;

public:
    InputResponder(Camera* camera);

    void handleKeyboard(unsigned char key, int x, int y);
    void handleMouse(int button, int state, int x, int y);
};
