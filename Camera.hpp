#pragma once

#include <math.h>
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
};

class Camera
{
public:
	Keys keys;
	Mouse mouse;
	glm::mat4 view;

	float cameraHeight = 200;
	float centerHeight, rotation, angle;
	float dragStartX = 0.0f;
	float dragStartY = 0.0f;

	void initCamera();
	void update(float& delta);
	bool keyboardInput();

private:
	glm::vec3 eye = glm::vec3(0.0f, 50.0f, cameraHeight);
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 defaultView = glm::lookAt(eye, center, up);

	float xAxis, yAxis;
};