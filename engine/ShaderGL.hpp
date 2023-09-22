#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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
		glad_glShaderSource(ShaderId, 1, &ShaderSourcePointer, NULL);
		glad_glCompileShader(ShaderId);
	}

	void checkShader(GLint& Result, int& InfoLogLength, GLuint& ShaderId) {
		glad_glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &Result);
		glad_glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);

		if (InfoLogLength > 0) {
			std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
			glad_glGetShaderInfoLog(ShaderId, InfoLogLength, NULL, &ShaderErrorMessage[0]);
			std::cout << ShaderErrorMessage[0] << std::endl;
		}
		else {
			std::cout << "Shader compiled successfully!" << std::endl;
		}
	}

	void checkProgram(GLuint& ProgramID, GLint& Result, int& InfoLogLength) {
		glad_glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glad_glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glad_glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			std::cout << ProgramErrorMessage[0] << std::endl;
		}
		else {
			std::cout << "Shader compiled successfully!" << std::endl;
		}
	}
public:
	GLuint load(const char* vertex_file_path, const char* fragment_file_path) {
		GLuint VertexShaderId = glad_glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderId = glad_glCreateShader(GL_FRAGMENT_SHADER);

		std::string VertexShaderCode;
		readShader(vertex_file_path, VertexShaderCode);

		std::string FragmentShaderCode;
		readShader(fragment_file_path, FragmentShaderCode);

		GLint Result = GL_FALSE;
		int InfoLogLength;

		std::cout << "Compiling shader... " << vertex_file_path << std::endl;
		compileShader(VertexShaderCode, VertexShaderId);
		checkShader(Result, InfoLogLength, VertexShaderId);

		std::cout << "Compiling shader... " << fragment_file_path << std::endl;
		compileShader(FragmentShaderCode, FragmentShaderId);
		checkShader(Result, InfoLogLength, FragmentShaderId);

		std::cout << "Linking Program" << std::endl;
		GLuint ProgramID = glad_glCreateProgram();
		glad_glAttachShader(ProgramID, VertexShaderId);
		glad_glAttachShader(ProgramID, FragmentShaderId);
		glad_glLinkProgram(ProgramID);

		checkProgram(ProgramID, Result, InfoLogLength);

		glad_glDetachShader(ProgramID, VertexShaderId);
		glad_glDetachShader(ProgramID, FragmentShaderId);

		glad_glDeleteShader(VertexShaderId);
		glad_glDeleteShader(FragmentShaderId);

		return ProgramID;
	}

	GLuint loadVertex(const char* vertex_file_path) {}
	GLuint loadFragment(const char* fragment_file_path) {}
};