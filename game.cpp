/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024
 * Main executable for the game */

#include "World.hpp"
#include "Camera.hpp"
#include "OpenGLRenderer.hpp"
#include "InputHandler.hpp"
#include "GlobalVariables.hpp"

#include <cmath>
#include <GL/glut.h>

OpenGLRenderer* gRenderer = nullptr;
InputHandler* gInputHandler = nullptr;

void timerFunc(int value) {
    if (gRenderer) {
        float deltaTime = gRenderer->calcDeltaTime();
        gInputHandler->update(deltaTime);
        glutPostRedisplay();
    }

    glutTimerFunc(1000 / 240, timerFunc, 0);
}

int main(int argc, char** argv) {
    World world(80, 60, 1.0f);

    Vector3 cameraPosition(0.0f, 0.0f, 10.0f);
    Quaternion cameraRotation(1.0f, 0.0f, 0.0f, 0.0f);
    Camera camera(Transform(cameraPosition, cameraRotation));

    OpenGLRenderer renderer(argc, argv, world, camera);
    gRenderer = &renderer;

    InputHandler inputHandler(&camera);
    gRenderer = &renderer;

    glutTimerFunc(1000 / 240, timerFunc, 0);
    glutMainLoop();

    return 0;
}
