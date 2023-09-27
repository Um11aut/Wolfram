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
			std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(ShaderId, InfoLogLength, NULL, &ShaderErrorMessage[0]);
			std::cerr << ShaderErrorMessage[0] << std::endl;
			throw std::runtime_error("Error while compiling shader");
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
			std::cout << "Shaders checked successfully!" << std::endl;
		}
	}
public:
	Shader() {
		wf::ProgramID = glCreateProgram();
	}

	void loadVertex(const char* vertex_file_path) {
		GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);

		std::string VertexShaderCode;
		readShader(vertex_file_path, VertexShaderCode);

		GLint Result = GL_FALSE;
		int InfoLogLength;

		compileShader(VertexShaderCode, VertexShaderId);
		checkShader(Result, InfoLogLength, VertexShaderId);

		glAttachShader(wf::ProgramID, VertexShaderId);
		glLinkProgram(wf::ProgramID);

		checkProgram(wf::ProgramID, Result, InfoLogLength);

		glDetachShader(wf::ProgramID, VertexShaderId);

		glDeleteShader(VertexShaderId);
	}

	void loadFragment(const char* fragment_file_path) {
		GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		std::string FragmentShaderCode;
		readShader(fragment_file_path, FragmentShaderCode);

		GLint Result = GL_FALSE;
		int InfoLogLength;

		compileShader(FragmentShaderCode, FragmentShaderId);
		checkShader(Result, InfoLogLength, FragmentShaderId);

		glAttachShader(wf::ProgramID, FragmentShaderId);
		glLinkProgram(wf::ProgramID);

		checkProgram(wf::ProgramID, Result, InfoLogLength);

		glDetachShader(wf::ProgramID, FragmentShaderId);

		glDeleteShader(FragmentShaderId);
	}

	void loadToGL() {
		glUseProgram(wf::ProgramID);
	}
};