#pragma once

#include "ISection.hpp"
#include "Route.hpp"
#include <random>
#include <iostream>

class Transition : public ISection
{
public:
	Transition(glm::vec3 startPos, int direction, Route* trans1);
	Transition(glm::vec3 startPos, int direction, Route* trans1, Route* trans2);
	int update(float& delta, IModel* model, int section);
	
	int Transition1(IModel* model);
	int Transition2(IModel* model);

private:
	bool split = false;
	bool test = false;
	Route* transition1 = nullptr;
	Route* transition2 = nullptr;
};