/* Author: Bas Zoeteman
 * Date of creation: 23-05-2024 */

#include "InputHandler.hpp"

#include <GL/glut.h>

InputHandler* gInputHandler = nullptr;

void globalHandleKeyboard(unsigned char key, int x, int y) {
    if (gInputHandler) {
        gInputHandler->handleKeyboard(key, x, y);
    }
}

void globalHandleMouse(int button, int state, int x, int y) {
    if (gInputHandler) {
        gInputHandler->handleMouse(button, state, x, y);
    }
}

InputHandler::InputHandler(Camera* camera) {
    responder = new InputResponder(camera);

    gInputHandler = this;
    glutKeyboardFunc(globalHandleKeyboard);
    glutMouseFunc(globalHandleMouse);
}

void InputHandler::handleKeyboard(unsigned char key, int x, int y) {
    responder->handleKeyboard(key, x, y);
}

void InputHandler::handleMouse(int button, int state, int x, int y) {
    responder->handleMouse(button, state, x, y);
}
