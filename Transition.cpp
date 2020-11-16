#include "Transition.hpp"

Transition::Transition(glm::vec3 startPos, float direction, Route* trans1)
{
    this->transition1 = trans1;
    this->split = false;

    start = glm::translate(glm::mat4(1.0), startPos);
    start = glm::rotate(start, glm::radians(direction), glm::vec3(0.0f, 0.0f, 1.0f));
}

Transition::Transition(glm::vec3 startPos, float direction, Route* trans1, Route* trans2)
{
    this->transition1 = trans1;
    this->transition2 = trans2;
    this->split = true;

    start = glm::translate(glm::mat4(1.0), startPos);
    start = glm::rotate(start, glm::radians(direction), glm::vec3(0.0f, 0.0f, 1.0f));
}

int Transition::update(float& delta, IModel* model, int section)
{
    if (!split) {
        transition1->addModel(model->getID());
        return -1;
    }
    else {
        Random() < 6 ? transition1->addModel(model->getID()) : transition2->addModel(model->getID());
        return -1;
    }
}

int Transition::Random()
{
    std::uniform_real_distribution<float> distribution(1.0f, 10.0f);
    std::random_device rd;
    std::default_random_engine generator(rd());
    return distribution(generator);
}
