#include <iostream>
#include <cassert>
#include "engine/Window.hpp"
#include "engine/RendererGL.hpp"
#include "engine/ShaderGL.hpp"


void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    // Handle or print the debug information
    std::cerr << "OpenGL Debug Message:" << std::endl;
    std::cerr << "ID: " << id << std::endl;
    std::cerr << "Message: " << message << std::endl;
}


int main() {
    Window::createForGL(4,6);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    RendererGL renderer;
    Camera camera = Camera();

    renderer.setSamples(8);
    
    renderer.createVertexArray();
    renderer.createVertexBuffer();
    
    renderer.createShaders();

    renderer.loop(wf::window, &camera);
    
    glfwTerminate();

    return 0;
}
