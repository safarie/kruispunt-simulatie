#include "End.hpp"

/// <summary>
/// constuctor
/// </summary>
/// <param name="end">possition</param>
/// <param name="direction">facing of the vehicle in degree</param>
End::End(glm::vec3 end, float direction)
{
	start = glm::translate(glm::mat4(1.0f), end);
}

/// <summary>
/// update the given vehicle
/// </summary>
/// <param name="delta">time past since last frame</param>
/// <param name="model">model(vehicle) to update</param>
/// <param name="section">current section number</param>
/// <returns>next section number</returns>
int End::update(float& delta, IModel* model, int section)
{
	model->update(delta, start);
	model->resetTime();
	model->deactivate();
	return -1;
}
