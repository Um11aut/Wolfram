#pragma once

#include "Renderer.hpp"
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO: Take data from .obj
static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
};

class RendererGL : public Renderer {
private:
	GLuint VertexArrayID;
	GLuint VertexBuffer;
public:
	void setSamples(int samples) {
		glfwWindowHint(GLFW_SAMPLES, samples);
	}

	void createVertexArray() override {		
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);
	}

	void createVertexBuffer() override {
		//generate 1 buffer and put the resulted identifier through VertexBuffer reference
		glGenBuffers(1, &VertexBuffer);
		//Binding buffer
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		//passthrough the vertex buffer to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	}

	void loop(GLFWwindow* window) {
		//exit loop on escape key
		while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
			glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
			glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*) 0
			);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableVertexAttribArray(0);

			glDisableVertexAttribArray(0);


			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		glfwTerminate();
	}

	void init() override {}
};