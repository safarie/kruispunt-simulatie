#pragma once

#include <memory>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

struct Keys {
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool space = false;
};

struct Mouse
{
	bool rightClick = false;
	bool leftClick = false;
	double xPos = 0.0;
	double yPos = 0.0;
	double xScroll = 0.0;
	double yScroll = 0.0;
};

class Camera
{
public:
	Keys keys;
	Mouse mouse;
	glm::mat4 view;

	void InitCamera();
	void Update(float& delta);
	bool keyboardInput();
	bool mouseMovement();
	bool scrolling();

private:
	glm::vec3 eye = glm::vec3(0.0f, 50.0f, 200.0f);
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 defaultView = glm::lookAt(eye, center, up);
};