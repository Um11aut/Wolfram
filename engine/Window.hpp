#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Window {
	GLFWwindow* window;

	void createGL() {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(800, 600, "Wolfram [OpenGL]", NULL, NULL);
		if (!window) {
			std::cerr << "Failed to create GLFW window" << std::endl;
		}
		glfwMakeContextCurrent(window);

		int version = gladLoadGL(glfwGetProcAddress);
		std::cout << "Loaded OpenGL ";
		std::cout << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
	}

	void loopGL() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		glfwTerminate();
	}

	// TODO: implement
	void createVK(GLFWwindow* window) {}
};