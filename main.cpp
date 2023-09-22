#include <iostream>
#include "engine/Window.hpp"
#include "engine/RendererGL.hpp"
#include "engine/ShaderGL.hpp"

int main() {
    Window::createForGL(4,6);

    RendererGL* renderer = new RendererGL();

    renderer->setSamples(4);
    renderer->createVertexArray();
    renderer->createVertexBuffer();

    Shader* shd = new Shader();
    GLuint programID = shd->loadVertex("C:/Users/askk/CLionProjects/Wolfram/shaders/shader.vert");
    programID = shd->loadFragment("C:/Users/askk/CLionProjects/Wolfram/shaders/shader.frag");

    renderer->loop(Window::window, programID);

    delete shd;
    delete renderer;

    return 0;
}
