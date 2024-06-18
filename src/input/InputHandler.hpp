/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024
 * Contains a class InputHandler that holds the functions
 * required for handling input. Makes use of the InputResponder
 * to respond to the received input. */

#pragma once

#include "InputResponder.hpp"
#include "Camera.hpp"

class InputHandler {
private:
    InputResponder* responder;

public:
    InputHandler(Camera* camera);

    void handleKeyboard(unsigned char key, int x, int y);
    void handleKeyboardUp(unsigned char key, int x, int y);

    void handleMouse(int button, int state, int x, int y);

    void update(float deltaTime);
};
