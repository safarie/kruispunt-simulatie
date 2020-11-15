#include "Transition.hpp"

Transition::Transition(glm::vec3 startPos, int direction, Route* trans1)
{
    this->transition1 = trans1;
    this->split = false;

    start = glm::translate(glm::mat4(1.0), startPos);
    start = glm::rotate(start, glm::radians((float)direction), glm::vec3(0.0f, 0.0f, 1.0f));
}

Transition::Transition(glm::vec3 startPos, int direction, Route* trans1, Route* trans2)
{
    this->transition1 = trans1;
    this->transition2 = trans2;
    this->split = true;

    start = glm::translate(glm::mat4(1.0), startPos);
    start = glm::rotate(start, glm::radians((float)direction), glm::vec3(0.0f, 0.0f, 1.0f));
}

int Transition::update(float& delta, IModel* model, int section)
{
    if (split)
        return Transition2(model);
    
    if (!split)
        return Transition1(model);
}

int Transition::Transition1(IModel* model)
{
    transition1->addModel(model->getID());
    return -1;
}

int Transition::Transition2(IModel* model)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 10);
    int rand = distribution(generator);
    std::cout << rand << std::endl;
    rand < 6 ? transition1->addModel(model->getID()) : transition2->addModel(model->getID());
    return -1;
}
