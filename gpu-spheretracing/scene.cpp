#include "scene.h"

#include "glm/gtc/type_ptr.hpp"
#include "opengl/utils.h"

Scene::~Scene() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &emptyLayout);
}
void Scene::Init(int width, int height) {
    vertexShader = CreateShaderFromFile(GL_VERTEX_SHADER, "gpu-spheretracing/shaders/vertex.glsl");
    fragmentShader = CreateShaderFromFile(GL_FRAGMENT_SHADER, "gpu-spheretracing/shaders/fragment.glsl");
    shaderProgram = CreateProgram({vertexShader, fragmentShader});
    glGenVertexArrays(1, &emptyLayout);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    camera.Perspective(width, height);
}

void Scene::Render(float dt) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glm::mat4 mvpMatrix = glm::inverse(camera.GetViewProjMatrix());
    glm::vec3 cameraPos = camera.GetPosition();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "invViewProj"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));
    glUniform3fv(glGetUniformLocation(shaderProgram, "cameraPos"), 1, glm::value_ptr(cameraPos));
    glBindVertexArray(emptyLayout);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glUseProgram(0);
    glBindVertexArray(0);
}

void Scene::ToggleWireframe() {
    wireFrame = !wireFrame;
    glPolygonMode(GL_FRONT_AND_BACK, wireFrame ? GL_LINE : GL_FILL);
}