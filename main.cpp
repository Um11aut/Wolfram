#include <iostream>
#include <cassert>
#include "engine/Window.hpp"
#include "engine/RendererGL.hpp"
#include "engine/ShaderGL.hpp"
#include "engine/Camera.hpp"

int main() {
    Window::createForGL(4,6);

    RendererGL renderer;
    Shader shader;

    renderer.setSamples(4);
    renderer.createVertexArray();
    renderer.createVertexBuffer();

    shader.loadVertex("C:/Users/askk/CLionProjects/Wolfram/shaders/shader.vert");
    shader.loadFragment("C:/Users/askk/CLionProjects/Wolfram/shaders/shader.frag");
    shader.loadToGL();

    Camera camera;
    camera.toGL();

    assert(wf::ProgramID, 1);

    renderer.loop(wf::window);

    return 0;
}
