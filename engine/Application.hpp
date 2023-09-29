#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_NONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace wf {
	GLFWwindow* window;

	int WIDTH = 800, HEIGHT = 600;

	GLuint ProgramID;

	struct Uniform final {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
	};
}