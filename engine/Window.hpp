#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Window {
	GLFWwindow* window;

	void createForGL(int maj_version, int min_version) {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj_version);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min_version);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(800, 600, "Wolfram [OpenGL]", NULL, NULL);
		if (!window) {
			std::cerr << "Failed to create GLFW window" << std::endl;
		}
		glfwMakeContextCurrent(window);

		int version = gladLoadGL(glfwGetProcAddress);
		std::cout << "Loaded OpenGL ";
		std::cout << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	}

	// TODO: implement
	void createForVk(GLFWwindow* window) {}
	void loopForVk(GLFWwindow* window) {}
};