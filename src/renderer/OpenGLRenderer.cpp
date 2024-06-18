/* Author: Bas Zoeteman
 * Date of creation: 21-05-2024 */

#include "OpenGLRenderer.hpp"
#include "Vertex.hpp"
#include "Entity.hpp"
#include "Color.hpp"
#include "GlobalVariables.hpp"

#include <GL/glut.h>

void globalDisplayCallback() {
    if (gRenderer) {
        gRenderer->render();
        glutSwapBuffers();
    }
}

OpenGLRenderer::OpenGLRenderer(int argc, char** argv, const World& world, const Camera& camera)
    : world(world), camera(camera) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 675);
    glutCreateWindow("hexGame");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(globalDisplayCallback);
}

void OpenGLRenderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    glLoadMatrixf(camera.getProjectionMatrix(windowWidth, windowHeight).data);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(camera.getViewMatrix().data);

    for (const auto& entity : world.getEntities()) {
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

float OpenGLRenderer::calcDeltaTime() {
    static int previousTime = glutGet(GLUT_ELAPSED_TIME);
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;
    return deltaTime;
}
