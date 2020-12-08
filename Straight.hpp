#pragma once

#include "ISection.hpp"

class Straight : public ISection
{
public:
	/// <summary>
	/// constuctor
	/// </summary>
	/// <param name="startPos">start position</param>
	/// <param name="direction">facing direction of the vehicle in degree</param>
	/// <param name="length">lenght of the section in meters</param>
	Straight(glm::vec3 startPos, float direction, float length);

	/// <summary>
	/// update the given vehicle
	/// </summary>
	/// <param name="delta">time past since last frame</param>
	/// <param name="model">model(vehicle) to update</param>
	/// <param name="section">current section number</param>
	/// <returns>next section number</returns>
	int update(float& delta, IModel* model, int section);

private:
	float length;
};