#pragma once

#include "ISection.hpp"

class End : public ISection
{
public:
	End(glm::vec3 end, float direction);
	int update(float& delta, IModel* model, int section);

private:

};