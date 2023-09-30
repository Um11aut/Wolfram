#include <iostream>
#include <cassert>
#include "engine/Window.hpp"
#include "engine/RendererGL.hpp"
#include "engine/ShaderGL.hpp"
#include "engine/Debugger.hpp"

int main() {
    Window::createForGL(4, 6);

    RendererGL renderer;
    Debugger debugger;
    Camera camera = Camera();
    
    debugger.init();

    renderer.setSamples(8);
    
    renderer.createVertexArray();
    renderer.createVertexBuffer();
    
    renderer.createShaders();
    renderer.createUniformBuffer();

    camera.setCameraDirection({ 1.0f, 1.0f, 1.0f });


    while (!glfwWindowShouldClose(wf::window) && glfwGetKey(wf::window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        if (glfwGetKey(wf::window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.updateViewMatrix();
        }
        if (glfwGetKey(wf::window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.updateViewMatrix();
        }
        renderer.updateUniformBuffer(&camera);
        renderer.loop(wf::window);
    }
    glfwTerminate();

    return 0;
}
