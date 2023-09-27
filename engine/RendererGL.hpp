#pragma once

#include "Renderer.hpp"
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <iostream>
#include <memory>

// TODO: Take data from .obj
static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 1.0f,
	   2.0f, -3.0f, -1.0f,
	   0.0f,  1.5f, 0.0f,
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
		glad_glGenVertexArrays(1, &VertexArrayID);
		glad_glBindVertexArray(VertexArrayID);
	}

	void createVertexBuffer() override {
		//generate 1 buffer and put the resulted identifier through VertexBuffer reference
		glad_glGenBuffers(1, &VertexBuffer);
		//Binding buffer
		glad_glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		//passthrough the vertex buffer to OpenGL
		glad_glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	}

	void loop(GLFWwindow* window) {
		//exit loop on escape key
		while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
			glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			

			glad_glEnableVertexAttribArray(0);
			glad_glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
			glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*) 0
			);
			glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glad_glDrawArrays(GL_TRIANGLES, 0, 3);
			glad_glDisableVertexAttribArray(0);

			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		glfwTerminate();
	}

	void init() override {}
};