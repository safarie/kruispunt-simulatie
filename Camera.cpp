#include "Camera.hpp"

void Camera::initCamera()
{
	view = defaultView;
}

void Camera::update(float& delta)
{
	float speed = delta * 50.0f;

	if (keyboardInput()) {

		if (keys.up) {
			eye.y -= speed;
			center.y -= speed;
		}

		if (keys.down) {
			eye.y += speed;
			center.y += speed;
		}

		if (keys.left) {
			eye.x += speed;
			center.x += speed;
		}

		if (keys.right) {
			eye.x -= speed;
			center.x -= speed;
		}

		view = glm::lookAt(eye, center, up);
	}

	if (mouse.leftClick) {

		xAxis = (dragStartX - mouse.xPos) / 2;
		yAxis = (dragStartY - mouse.yPos);

		float radius = 50.0f;
		angle = std::fmodf(rotation + xAxis, 360.0f);

		center.x = eye.x + (radius * std::sinf(glm::radians(angle)));
		center.y = eye.y + (radius * -std::cosf(glm::radians(angle)));

		center.z = centerHeight + yAxis;

		view = glm::lookAt(eye, center, up);
	}

	if (!mouse.leftClick) {
		centerHeight = center.z;
		rotation = angle;
	}
	
	if (keys.space)
		view = defaultView;

	if (cameraHeight != eye.z) {
		eye.z = cameraHeight;
		view = glm::lookAt(eye, center, up);
	}
}

bool Camera::keyboardInput()
{
	return keys.up || keys.down || keys.left || keys.right;
}