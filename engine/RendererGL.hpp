#pragma once

#include "Renderer.hpp"
#include "ShaderGL.hpp"
#include "Window.hpp"
#include "Model.hpp"
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <iostream>
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO: Take data from .obj
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

class RendererGL : public Renderer {
private:
	GLuint ubo;
	
	Model* model;
	std::vector<glm::vec3> Verticies;

	Shader shader;

	GLuint VertexArrayID;
	GLuint VertexBuffer;
public:
	void setSamples(int samples) {
		glfwWindowHint(GLFW_SAMPLES, samples);
	}

	void createVertexArray() override {		
		model->loadModel("C:/Users/askk/CLionProjects/Wolfram/extra/sphere.obj");
		Verticies = model->getVector();

		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);
	}

	void createVertexBuffer() override {
		//generate 1 buffer and put the resulted identifier through VertexBuffer reference
		glGenBuffers(1, &VertexBuffer);
		//Binding buffer
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		//passthrough the vertex buffer to OpenGL
		glBufferData(GL_ARRAY_BUFFER, Verticies.size() * sizeof(glm::vec3), Verticies.data(), GL_STATIC_DRAW);
	}

	void createUniformBuffer() {
		glGenBuffers(1, &this->ubo);

		glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);

		glBufferData(GL_UNIFORM_BUFFER, sizeof(wf::Uniform), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBufferBase(GL_UNIFORM_BUFFER, 0, this->ubo);
	}

	void updateUniformBuffer(Camera* camera) {
		wf::Uniform uniformData = camera->getUniform();

		glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);

		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(wf::Uniform), &uniformData);

		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void createShaders() {
		shader.loadFragment("C:/Users/askk/CLionProjects/Wolfram/shaders/shader.frag");
		shader.loadVertex("C:/Users/askk/CLionProjects/Wolfram/shaders/shader.vert");
		shader.attachShaders();
	}

	void loop(GLFWwindow* window) {
		//exit loop on escape key
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callbackGL);

		shader.bind();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
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
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

		shader.unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void init() override {}
};