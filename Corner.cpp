#include "Corner.hpp"

Corner::Corner(glm::vec3 startPos, int direction, float radius, int degree)
{
    this->radius = radius;
    this->degree = degree;

    start = glm::translate(glm::mat4(1.0), startPos);
    start = glm::rotate(start, glm::radians((float)direction), glm::vec3(0.0f, 0.0f, 1.0f));

	circumference = (radius * 2) * M_PI;
    degPerMeter = 360.0f / circumference;
}

int Corner::update(float& delta, IModel* model, int section)
{
	glm::mat4* modelMat = &model->getPos();
	
	float speed = model->getSpeed();
	float angle = speed * degPerMeter;
	
	if (degree < 0)
		angle *= -1;

	if (model->getTime() == 0.0f) {
		*modelMat = start;
	}

	if (model->getTime() * fabs(angle) < abs(degree)) {
		*modelMat = glm::translate(*modelMat, delta * speed * glm::vec3(-1.0, 0.0f, 0.0f));
		*modelMat = glm::rotate(*modelMat, delta * glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
		model->update(delta, *modelMat);
		return section;
	}
	else {
		model->resetTime();
		section += 1;
		return section;
	}
}
