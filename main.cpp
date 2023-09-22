#include <iostream>
#include "engine/Window.hpp"
#include "engine/RendererGL.hpp"
#include "engine/ShaderGL.hpp"

int main() {
    Window::createForGL(4,6);

    RendererGL renderer;
    renderer.setSamples(4);
    renderer.createVertexArray();
    renderer.createVertexBuffer();

    Shader shader;
    shader.load("123", "123");

    renderer.loop(Window::window);
    return 0;
}
