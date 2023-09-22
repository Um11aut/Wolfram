#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <optional>

class Shader {
private:
	std::optional<GLuint> VertexShaderId;
	std::optional<GLuint> FragmentShaderId;

	void readVertexShader(const char* vertex_file_path, std::string& VertexShaderCode) {

		std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);

		if (VertexShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << VertexShaderStream.rdbuf();
			VertexShaderCode = sstr.str();
			VertexShaderStream.close();
		}
		else {
			throw std::runtime_error("Error while loading Shader File!");
		}

	}

	void checkVertexShader() {}
	void checkFragmentShader() {}
public:
	GLuint load(const char* vertex_file_path, const char* fragment_file_path) {
		VertexShaderId = glad_glCreateShader(GL_VERTEX_SHADER);
		FragmentShaderId = glad_glCreateShader(GL_FRAGMENT_SHADER);

		std::string VertexShaderCode;
		readVertexShader(vertex_file_path, VertexShaderCode);
	}

	GLuint loadVertex(const char* vertex_file_path) {}
	GLuint loadFragment(const char* fragment_file_path) {}
};