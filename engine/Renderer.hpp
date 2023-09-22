#include <GLFW/glfw3.h>

class Renderer {
public:
	virtual void createVertexArray() = 0;
	virtual void createVertexBuffer() = 0;
	virtual void init() = 0;
};