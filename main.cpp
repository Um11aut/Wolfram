#include <iostream>
#include "engine/Window.hpp"
#include "engine/RendererGL.hpp"

int main() {
    Window::createGL();

    Renderer* render = new RendererGL();
    render->init();

    Window::loopGL();
    return 0;
}
