/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "OpenGLRenderer.hpp"
#include "Vertex.hpp"
#include "Entity.hpp"
#include "Color.hpp"

#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

OpenGLRenderer::OpenGLRenderer(int argc, char** argv, const EntityContainer& entityContainer, const Camera& camera)
    : entityContainer(entityContainer), camera(camera) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    window = glfwCreateWindow(1200, 675, "hexGame", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLRenderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(camera.getProjectionMatrix().data);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(camera.getViewMatrix().data);

    for (const auto& entity : entityContainer.getEntities()) {
        glPushMatrix();
        glMultMatrixf(entity->getTransform().getMatrix().data);

        std::vector<Vertex> vertices = entity->getMesh().getVertices();
        std::vector<unsigned int> indices = entity->getMesh().getIndices();

        glBegin(GL_TRIANGLES);
        for (unsigned int i = 0; i < indices.size(); i++) {
            Vertex vertex = vertices[indices[i]];
            Color color = vertex.getColor();
            Vector3 position = vertex.getPosition();
            glColor3f(color.r, color.g, color.b);
            glVertex3f(position.x, position.y, position.z);
        }
        glEnd();

        glPopMatrix();
    }
}

double OpenGLRenderer::calcDeltaTime() {
    static double previousTime = glfwGetTime();
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    return deltaTime;
}
