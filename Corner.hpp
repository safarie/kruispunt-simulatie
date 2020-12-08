#pragma once

#define _USE_MATH_DEFINES

#include "ISection.hpp"

#include <math.h>

/// <summary>
/// road corner section
/// </summary>
class Corner : public ISection
{
public:
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="startPos">start position of the corner</param>
	/// <param name="direction">facing of the vehicle in degree</param>
	/// <param name="radius">radius of the corner</param>
	/// <param name="degree">degree of the corner</param>
	Corner(glm::vec3 startPos, float direction, float radius, float degree);
	
	/// <summary>
	/// update the given vehicle
	/// </summary>
	/// <param name="delta">time past since last frame</param>
	/// <param name="model">model(vehicle) to update</param>
	/// <param name="section">current section number</param>
	/// <returns>next section number</returns>
	int update(float& delta, IModel* model, int section);

private:
	float radius;
	float degree;
	float circumference;
	float degPerMeter;
};