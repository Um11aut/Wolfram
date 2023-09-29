#pragma once

#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_NONE
#include <glad/gl.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <string>
#include <memory>
#include <vector>

#include "Application.hpp"

class Shader {
private:
	GLuint ubo;

	GLuint _programID = glCreateProgram();

	GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	void readShader(const char* file_path, std::string& ShaderCode) {
		std::ifstream ShaderStream(file_path, std::ios::in);

		if (!ShaderStream.is_open()) {
			std::cerr << "Error while opening Shader File " << file_path << ": " << strerror(errno) << std::endl;
			return;
		}

		std::stringstream sstr;
		sstr << ShaderStream.rdbuf();
		ShaderCode = sstr.str();
		ShaderStream.close();

	}

	void compileShader(std::string& ShaderCode, GLuint& ShaderId) {
		char const* ShaderSourcePointer = ShaderCode.c_str();
		glShaderSource(ShaderId, 1, &ShaderSourcePointer, NULL);
		glCompileShader(ShaderId);
	}

	void checkShader(GLint& Result, int& InfoLogLength, GLuint& ShaderId) {
		glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);

		if (InfoLogLength > 0) {
			std::string info_log(static_cast<size_t>(InfoLogLength) + 1, static_cast<char>(0));
			glGetShaderInfoLog(ShaderId, static_cast<int32_t>(info_log.size()), nullptr, info_log.data());
			std::cerr << info_log;
		}
		else {
			std::cout << "Shader compiled successfully!" << std::endl;
		}
	}

	void checkProgram(GLuint& ProgramID, GLint& Result, int& InfoLogLength) {
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			std::cerr << ProgramErrorMessage[0] << std::endl;
		}
		else {
			std::cout << "Shader checked successfully!" << std::endl;
		}
	}
public:

	void loadVertex(const char* vertex_file_path) {

		std::string VertexShaderCode;
		readShader(vertex_file_path, VertexShaderCode);

		GLint Result = GL_FALSE;
		int InfoLogLength;

		compileShader(VertexShaderCode, VertexShaderId);
		checkShader(Result, InfoLogLength, VertexShaderId);
	}

	void loadFragment(const char* fragment_file_path) {

		std::string FragmentShaderCode;
		readShader(fragment_file_path, FragmentShaderCode);

		GLint Result = GL_FALSE;
		int InfoLogLength;

		compileShader(FragmentShaderCode, FragmentShaderId);
		checkShader(Result, InfoLogLength, FragmentShaderId);
	}

	void attachShaders() {
		glAttachShader(_programID, VertexShaderId);
		glAttachShader(_programID, FragmentShaderId);
		glLinkProgram(_programID);

		// Check the program
		GLint Result = GL_FALSE;
		int InfoLogLength;
		checkProgram(_programID, Result, InfoLogLength);

		glDetachShader(_programID, VertexShaderId);
		glDetachShader(_programID, FragmentShaderId);

		glDeleteShader(VertexShaderId);
		glDeleteShader(FragmentShaderId);
	}

	void bind() {
		glUseProgram(_programID);
	}

	void unbind() {
		glUseProgram(0);
	}

	void createUniformBuffer() {
		glGenBuffers(1, &this->ubo);

		if (this->ubo == 0) {
			std::cerr << "Failed to create uniform buffer object." << std::endl;
			// Handle error appropriately
			return;
		}

		glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);

		if (glGetError() != GL_NO_ERROR) {
			std::cerr << "Failed to bind uniform buffer object." << std::endl;
			// Handle error appropriately
			glBindBuffer(GL_UNIFORM_BUFFER, 0); // Unbind the buffer on error
			return;
		}
		
		glBufferData(GL_UNIFORM_BUFFER, sizeof(wf::Uniform), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBufferBase(GL_UNIFORM_BUFFER, 0, this->ubo);
	}

	void updateUniformBuffer(Camera* camera) {
		if (this->ubo == 0) {
			std::cerr << "Error: Uniform buffer object not initialized." << std::endl;
			// Handle error appropriately
			return;
		}

		wf::Uniform uniformData = camera->getUniform();

		glBindBuffer(GL_UNIFORM_BUFFER, this->ubo);

		GLenum bindError = glGetError();
		if (bindError != GL_NO_ERROR) {
			std::cerr << "Error binding uniform buffer: " << bindError << std::endl;
			// Handle error appropriately
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			return;
		}

		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(wf::Uniform), &uniformData);

		GLenum subDataError = glGetError();
		if (subDataError != GL_NO_ERROR) {
			std::cerr << "Error updating uniform buffer data: " << subDataError << std::endl;
			// Handle error appropriately
		}

		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
};