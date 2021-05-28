#include "Camera.h"


Camera::Camera()
	: movementSpeed(default_speed), mouseSensitivity(default_sensitivity), zoom(default_zoom)
	, declination(default_declination) {
		origin = glm::vec3(0.0f);

}

glm::mat4 Camera::getViewMatrix() {
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::vec3 up = glm::vec3(0.0f, cos(glm::radians(declination)), sin(glm::radians(declination)));

	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, zoom));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(azimuth), up);
	viewMatrix = glm::rotate(viewMatrix, glm::radians(declination), glm::vec3(1.0f, 0.0f, 0.0f));
	return viewMatrix;
}


void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	azimuth -= xOffset;
	declination -= yOffset;
	if (constrainPitch) {
		if (declination > 89.0f)
			declination = 89.0f;
		else if (declination < -89.0f)
			declination = -89.0f;
	}
}

void Camera::processMouseMovementMiddle(float xOffset, float yOffset) {
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;
}

void Camera::processMouseScroll(float yOffset) {
	zoom -= yOffset;
}


