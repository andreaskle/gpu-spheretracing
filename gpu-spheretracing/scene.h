#ifndef SCENE_H
#define SCENE_H
#include <iostream>

#include "camera.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

class Scene {
   public:
    ~Scene();
    void Init(int width, int height);
    void Render(float dt);

    void ToggleWireframe();

   private:
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
    GLuint shaderProgram = 0;
    GLuint emptyLayout = 0;

    Camera camera;
    bool wireFrame = false;
};
#endif
