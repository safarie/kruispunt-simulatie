#pragma once

#include "ISection.hpp"
#include "Route.hpp"
#include <random>

class Transition : public ISection
{
public:
	Transition(glm::vec3 startPos, float direction, Route* trans1);
	Transition(glm::vec3 startPos, float direction, Route* trans1, Route* trans2);
	int update(float& delta, IModel* model, int section);
	int Random();
	
private:
	bool split = false;
	bool test = false;
	Route* transition1 = nullptr;
	Route* transition2 = nullptr;
};