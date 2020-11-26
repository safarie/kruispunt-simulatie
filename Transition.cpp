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

Transition::Transition(Route* trans1, Route* trans2, Route* trans3)
{
    this->transition1 = trans1;
    this->transition2 = trans2;
    this->transition3 = trans3;
    this->split = true;
}

int Transition::update(float& delta, IModel* model, int section)
{
    if (!split) {
        transition1->addModel(model->getID());
        return -1;
    }
    else if (split && transition3 == nullptr)
    {
        random() < 7 ? transition1->addModel(model->getID()) : transition2->addModel(model->getID());
        return -1;
    }
    else {
        int rand = random();
        if (rand < 5)
            transition1->addModel(model->getID());
        else if (rand > 4 && rand < 9)
            transition2->addModel(model->getID());
        else
            transition3->addModel(model->getID());

        return -1;
    }
}

int Transition::random()
{
    std::uniform_real_distribution<float> distribution(1.0f, 12.0f);
    std::random_device rd;
    std::default_random_engine generator(rd());
    return distribution(generator);
}
