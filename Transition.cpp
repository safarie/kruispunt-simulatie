#include "Transition.hpp"

/// <summary>
/// contructor
/// </summary>
/// <param name="trans1">first route to transtiton to</param>
Transition::Transition(Route* trans1)
{
    this->transition1 = trans1;
    this->split = false;
}

/// <summary>
/// constructor overload
/// </summary>
/// <param name="trans1">first route to transtiton to</param>
/// <param name="trans2">second route to transtiton to</param>
Transition::Transition(Route* trans1, Route* trans2)
{
    this->transition1 = trans1;
    this->transition2 = trans2;
    this->split = true;
}

/// <summary>
/// constructor overload
/// </summary>
/// <param name="trans1">first route to transtiton to</param>
/// <param name="trans2">second route to transtiton to</param>
/// <param name="trans3">third route to transtiton to</param>
Transition::Transition(Route* trans1, Route* trans2, Route* trans3)
{
    this->transition1 = trans1;
    this->transition2 = trans2;
    this->transition3 = trans3;
    this->split = true;
}

/// <summary>
/// update the given vehicle
/// </summary>
/// <param name="delta">time past since last frame</param>
/// <param name="model">model(vehicle) to update</param>
/// <param name="section">current section number</param>
/// <returns>next section number</returns>
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

/// <summary>
/// randomizer
/// </summary>
/// <returns>random int between 1, 12</returns>
int Transition::random()
{
    std::uniform_real_distribution<float> distribution(1.0f, 12.0f);
    std::random_device rd;
    std::default_random_engine generator(rd());
    return distribution(generator);
}
