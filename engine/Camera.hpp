#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Application.hpp"

class Camera {
private:
	wf::Uniform uniformData;

	glm::vec3 cameraPosition = glm::vec3(4.f, 3.f, 4.f);
	glm::vec3 cameraViewDir = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 head = glm::vec3(0, 1, 0);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) wf::WIDTH / (float) wf::HEIGHT, 0.1f, 100.f);
	glm::mat4 view = glm::lookAt(cameraPosition, cameraViewDir, head);
	glm::mat4 model = glm::mat4(1.0f);

public:
	Camera() {
		uniformData.model = this->model;
		uniformData.projection = this->projection;
		uniformData.view = this->view;
	}

	~Camera() = default;

	void setLookAt(glm::vec3 cameraPos, glm::vec3 cameraDir, glm::vec3 head) {
		this->view = glm::lookAt(cameraPos, cameraDir, head);
	}

	void setCameraPosition(glm::vec3 cameraPos) {
		this->view = glm::lookAt(cameraPos, this->cameraViewDir, this->head);
	}

	void setCameraDirection(glm::vec3 cameraDir) {
		this->view = glm::lookAt(this->cameraPosition, cameraDir, this->head);
	}

	wf::Uniform getUniform() const {
		return uniformData;
	}
};