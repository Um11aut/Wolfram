#include <GLFW/glfw3.h>
#include "Camera.hpp"

class Renderer {
public:
	virtual void createVertexArray() = 0;
	virtual void createVertexBuffer() = 0;
	virtual void init() = 0;
};