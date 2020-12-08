#pragma once

#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

/// <summary>
/// struct with bools to check if a key is pressed
/// </summary>
struct Keys {
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool space = false;
};

/// <summary>
/// struct with mouse info
/// </summary>
struct Mouse
{
	bool rightClick = false;
	bool leftClick = false;
	double xPos = 0.0;
	double yPos = 0.0;
};

/// <summary>
/// camera class
/// </summary>
class Camera
{
public:
	Keys keys;
	Mouse mouse;
	glm::mat4 view;

	float dragStartX = 0.0f; 
	float dragStartY = 0.0f; 
	float cameraHeight = 200;

	/// <summary>
	/// set the default camera position
	/// </summary>
	void initCamera();
	
	/// <summary>
	/// update the camera data
	/// </summary>
	/// <param name="delta">time past since last update</param>
	void update(float& delta);
	
	/// <summary>
	/// check if any of the keys(wasd) is pressed
	/// </summary>
	/// <returns></returns>
	bool keyboardInput();

private:
	glm::vec3 eye = glm::vec3(0.0f, 50.0f, cameraHeight);
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 defaultView = glm::lookAt(eye, center, up);

	float xAxis = 0.0f; 
	float yAxis = 0.0f;
	float centerHeight = 0.0f; 
	float angle = 0.0f; 
	float rotation = 0.0f;
};