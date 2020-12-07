#include "Straight.hpp"

/// <summary>
/// constuctor
/// </summary>
/// <param name="startPos">start position</param>
/// <param name="direction">facing direction of the vehicle in degree</param>
/// <param name="length">lenght of the section in meters</param>
Straight::Straight(glm::vec3 startPos, float direction, float length)
{
	this->length = length;

	start = glm::translate(glm::mat4(1.0), startPos);
	start = glm::rotate(start, glm::radians(direction), glm::vec3(0.0f, 0.0f, 1.0f));
}

/// <summary>
/// update the given vehicle
/// </summary>
/// <param name="delta">time past since last frame</param>
/// <param name="model">model(vehicle) to update</param>
/// <param name="section">current section number</param>
/// <returns>next section number</returns>
int Straight::update(float& delta, IModel* model, int section)
{
	glm::mat4* modelMat = &model->getPos();

	if (model->getTime() == 0.0f) {
		*modelMat = start;
	}

	if (model->getTime() * model->getSpeed() < length) {
		*modelMat = glm::translate(*modelMat, delta * model->getSpeed() * glm::vec3(-1.0f, 0.0f, 0.0f));
		model->update(delta, *modelMat);
		return section;
	}
	else {
		model->resetTime();
		section += 1;
		return section;
	}
}
