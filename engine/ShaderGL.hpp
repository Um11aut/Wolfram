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
};