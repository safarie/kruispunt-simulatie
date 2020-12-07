#include "TrafficLight.hpp"

/// <summary>
/// contructor
/// </summary>
/// <param name="startPos">start position</param>
/// <param name="direction">facing direction of the vehicle in degree</param>
/// <param name="length">length of the check zone in meters</param>
/// <param name="trafficLight">traffic light ID</param>
/// <param name="ptr_trafficLights">ptr to list of traffic lights</param>
TrafficLight::TrafficLight(glm::vec3 startPos, float direction, float length, int trafficLight, std::vector<TrafficLichtInfo>* ptr_trafficLights)
{
	this->length = length;
	this->ID = trafficLight;
	this->trafficLights = ptr_trafficLights;

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
int TrafficLight::update(float& delta, IModel* model, int section)
{
	glm::mat4* modelMat = &model->getPos();

	if (model->getTime() == 0.0f) {
		*modelMat = start;
	}

	//std::cout << trafficLights->at(ID).state << std::endl;

	if (trafficLights->at(ID).state == 0) {
		trafficLights->at(ID).traffic = 1;		// testing
		model->stop();
		return section;
	}

	model->start();
	trafficLights->at(ID).traffic = 0;			// testing

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
