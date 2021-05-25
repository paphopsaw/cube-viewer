#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

const float default_yaw = -90.0f;
const float default_pitch = 0.0f;
const float default_speed = 2.5f;
const float default_sensitivity = 0.1f;
const float default_zoom = 45.0f;

enum Camera_movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = default_yaw, float pitch = default_pitch);
	glm::mat4 getViewMatrix();
	void processKeyboard(Camera_movement direction, float deltaTime);
	void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
	void processMouseScroll(float yOffset);

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;
	float zoom;
	void updateCameraVector();
};

#endif