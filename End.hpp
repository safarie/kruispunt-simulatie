#pragma once

#include "ISection.hpp"

/// <summary>
/// interface for all road sections
/// </summary>
class End : public ISection
{
public:
	/// <summary>
	/// constuctor
	/// </summary>
	/// <param name="end">possition</param>
	/// <param name="direction">facing of the vehicle in degree</param>
	End(glm::vec3 end, float direction);

	/// <summary>
	/// update the given vehicle
	/// </summary>
	/// <param name="delta">time past since last frame</param>
	/// <param name="model">model(vehicle) to update</param>
	/// <param name="section">current section number</param>
	/// <returns>next section number</returns>
	int update(float& delta, IModel* model, int section);

private:

};