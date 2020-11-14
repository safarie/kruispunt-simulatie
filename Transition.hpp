#pragma once

#include "ISection.hpp"
#include "Route.hpp"

class Transition : public ISection
{
public:
	Transition(glm::vec3 startPos, int direction, Route* trans1);
	Transition(glm::vec3 startPos, int direction, Route* trans1, Route* trans2);
	int update(float& delta, IModel* model, int section);
	
	int Transition1(float& delta, IModel* model, int section);
	int Transition2(float& delta, IModel* model, int section);

private:
	bool split = false;
	Route* transition1 = nullptr;
	Route* transition2 = nullptr;
};