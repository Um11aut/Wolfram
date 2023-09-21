#include "Renderer.hpp"
#include <iostream>

class RendererGL : public Renderer {
public:
	void init() {
		std::cout << "Initializing OpenGL" << std::endl;
	}
};