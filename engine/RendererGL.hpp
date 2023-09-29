#pragma once

#include "Renderer.hpp"
#include "ShaderGL.hpp"
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
	Shader shader;

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

	void createShaders() {
		shader.loadFragment("C:/Users/askk/CLionProjects/Wolfram/shaders/shader.frag");
		shader.loadVertex("C:/Users/askk/CLionProjects/Wolfram/shaders/shader.vert");
		shader.attachShaders();
		
		shader.createUniformBuffer();
	}

	void loop(GLFWwindow* window, Camera* cam) {
		while (!glfwWindowShouldClose(wf::window) && glfwGetKey(wf::window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
			//exit loop on escape key
			glClear(GL_COLOR_BUFFER_BIT);

			shader.bind();

			shader.updateUniformBuffer(cam);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
			glVertexAttribPointer(
				0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

			glDisableVertexAttribArray(0);

			shader.unbind();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}

	void init() override {}
};