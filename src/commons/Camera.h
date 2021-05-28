#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

const float default_speed = 2.5f;
const float default_sensitivity = 0.5f;
const float default_zoom = -10.0f;
const float default_declination = 0.0f;


class Camera {
public:
	Camera();
	glm::mat4 getViewMatrix();
	void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
	void processMouseMovementMiddle(float xOffset, float yOffset);
	void processMouseScroll(float yOffset);

private:
	glm::vec3 origin;

	float movementSpeed;
	float mouseSensitivity;
	float zoom;
	float declination;
	float azimuth;

};

#endif