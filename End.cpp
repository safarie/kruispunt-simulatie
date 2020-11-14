#include "End.hpp"

End::End(glm::vec3 end, int direction)
{
	this->direction = direction;
	start = glm::translate(glm::mat4(1.0f), end);
}

int End::update(float& delta, IModel* model, int section)
{
	model->update(delta, start);
	model->resetTime();
	return -1;
}
