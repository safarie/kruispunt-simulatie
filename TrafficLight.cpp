#include "TrafficLight.hpp"

TrafficLight::TrafficLight(glm::vec3 startPos, int direction, float length, int trafficLight, std::vector<TrafficLichtInfo>* ptr_trafficLights)
{
	this->length = length;
	this->ID = trafficLight;
	this->trafficLights = ptr_trafficLights;

	start = glm::translate(glm::mat4(1.0), startPos);
	start = glm::rotate(start, glm::radians((float)direction), glm::vec3(0.0f, 0.0f, 1.0f));
}

int TrafficLight::update(float& delta, IModel* model, int section)
{
	glm::mat4* modelMat = &model->getPos();

	if (model->getTime() == 0.0f) {
		*modelMat = start;
	}

	//std::cout << trafficLights->at(ID).state << std::endl;

	if (trafficLights->at(ID).state == 0) {
		model->stop();
		return section;
	}

	model->start();

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
