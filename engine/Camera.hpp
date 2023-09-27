#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Application.hpp"

class Camera {
private:
	GLuint MatrixID;

	glm::vec3 cameraPosition = glm::vec3(50.f, 50.f, 10.f);
	glm::vec3 cameraViewDir = glm::vec3(15.f, 15.f, 15.f);
	glm::vec3 head = glm::vec3(0, 0, 0);

	glm::mat4 projection = glm::perspective(glm::radians(100.f), (float)wf::WIDTH / (float)wf::HEIGHT, 0.1f, 100.f);
	glm::mat4 view = glm::lookAt(cameraPosition, cameraViewDir, head);
	glm::mat4 model = glm::mat4(1.f);

	glm::mat4 mvp;


	void update() {
		this->mvp = this->projection * this->view * this->model;
	}
public:
	Camera() {
		update();
		this->MatrixID = glGetUniformLocation(wf::ProgramID, "MVP");
	}

	~Camera() = default;

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

	void toGL() {
		update();
		std::cout << MatrixID << std::endl;
		glProgramUniformMatrix4fv(wf::ProgramID, MatrixID, 1, false, &mvp[0][0]);
	}
};