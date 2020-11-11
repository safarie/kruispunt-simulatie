#include "End.hpp"

End::End(glm::vec3 end, int direction)
{
	this->direction = direction;
	start = glm::translate(glm::mat4(1.0f), end);
}

int End::update(float& delta, IModel* model, int section)
{
	float reset = 0.0f;
	model->resetTime();
	model->update(reset, start);
	return -1;
}
