#include "Camera.hpp"

void Camera::InitCamera()
{
	view = defaultView;
}

void Camera::Update(float& delta)
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

	if (scrolling()) {
		eye.z += mouse.yScroll;
		view = glm::lookAt(eye, center, up);
	}

	if (mouseMovement()) {
		// mouse movement
	}

	if (keys.space)
		view = defaultView;
}

bool Camera::keyboardInput()
{
	return keys.up || keys.down || keys.left || keys.right;
}

bool Camera::mouseMovement()
{
	return false;
}

bool Camera::scrolling()
{
	return mouse.xScroll != 0 || mouse.yScroll != 0;
}