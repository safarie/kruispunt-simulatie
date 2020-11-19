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

	if (mouseMovement()) {

		differentsX += (prevXpos - mouse.xPos) / 2;

		float radius = 50.0f;
		float angle = std::fmodf(differentsX, 360.0f);

		center.x = eye.x + (radius * std::sinf(glm::radians(angle)));
		center.y = eye.y + (radius * -std::cosf(glm::radians(angle)));

		prevXpos = mouse.xPos;
		prevYpos = mouse.yPos;

		view = glm::lookAt(eye, center, up);
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

bool Camera::mouseMovement()
{
	return mouse.leftClick;
}