#pragma once

#include "IModel.hpp"

#include <vector>

/// <summary>
/// road section interface
/// </summary>
class ISection
{
public:
	/// <summary>
	/// update the given vehicle
	/// </summary>
	/// <param name="delta">time past since last frame</param>
	/// <param name="model">model(vehicle) to update</param>
	/// <param name="section">current section number</param>
	/// <returns>next section number</returns>
	virtual int update(float& delta, IModel* model, int section) = 0;

protected:
	glm::mat4 start;
};