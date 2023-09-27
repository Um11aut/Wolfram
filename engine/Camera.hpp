#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Application.hpp"

class Camera {
private:
	glm::vec3 cameraPosition = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 cameraViewDir = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 head = glm::vec3(0, 1, 0);

	glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)wf::WIDTH / (float)wf::HEIGHT, 0.1f, 100.f);
	glm::mat4 view = glm::lookAt(cameraPosition, cameraViewDir, glm::vec3(0, 1, 0));
	glm::mat4 model = glm::mat4(1.f);

	glm::mat4 mvp;
public:
	void setLookAt(glm::vec3 cameraPos, glm::vec3 cameraDir, glm::vec3 head) {
		this->view = glm::lookAt(cameraPos, cameraDir, head);
		update();
	}

	void setCameraPosition(glm::vec3 cameraPos) {
		this->view = glm::lookAt(cameraPos, this->cameraViewDir, this->head);
		update();
	}

	void setCameraDirection(glm::vec3 cameraDir) {
		this->view = glm::lookAt(this->cameraPosition, cameraDir, this->head);
		update();
	}

	void update() {
		this->mvp = this->projection * this->view * this->model;
	}

	void toGL(GLuint& programID) {
		GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	}

	glm::mat4 getMatrix() const {
		return mvp;
	}
};