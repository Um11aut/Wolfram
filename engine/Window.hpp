#pragma once
#include "Application.hpp"

namespace Window {
	int WIDTH = 800, HEIGHT = 600;

	void createForGL(int maj_version, int min_version) {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj_version);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min_version);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		wf::window = glfwCreateWindow(WIDTH, HEIGHT, "Wolfram [OpenGL]", NULL, NULL);
		if (!wf::window) {
			std::cerr << "Failed to create GLFW window" << std::endl;
		}
		glfwMakeContextCurrent(wf::window);

		int version = gladLoadGL(glfwGetProcAddress);
		std::cout << "Loaded OpenGL ";
		std::cout << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
		glfwSetInputMode(wf::window, GLFW_STICKY_KEYS, GL_TRUE);
	}

	void framebuffer_size_callbackGL(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	// TODO: implement
	void createForVk(GLFWwindow* window) {}
	void loopForVk(GLFWwindow* window) {}
};