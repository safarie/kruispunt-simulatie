#include "Transition.hpp"

Transition::Transition(Route* trans1)
{
    this->transition1 = trans1;
    this->split = false;
}

Transition::Transition(Route* trans1, Route* trans2)
{
    this->transition1 = trans1;
    this->transition2 = trans2;
    this->split = true;
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
