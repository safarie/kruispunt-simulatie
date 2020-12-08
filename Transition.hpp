#pragma once

#include "ISection.hpp"
#include "Route.hpp"
#include <random>

class Transition : public ISection
{
public:
	/// <summary>
	/// contructor
	/// </summary>
	/// <param name="trans1">first route to transtiton to</param>
	Transition(Route* trans1);

	/// <summary>
	/// constructor overload
	/// </summary>
	/// <param name="trans1">first route to transtiton to</param>
	/// <param name="trans2">second route to transtiton to</param>
	Transition(Route* trans1, Route* trans2);

	/// <summary>
	/// constructor overload
	/// </summary>
	/// <param name="trans1">first route to transtiton to</param>
	/// <param name="trans2">second route to transtiton to</param>
	/// <param name="trans3">third route to transtiton to</param>
	Transition(Route* trans1, Route* trans2, Route* trans3);

	/// <summary>
	/// update the given vehicle
	/// </summary>
	/// <param name="delta">time past since last frame</param>
	/// <param name="model">model(vehicle) to update</param>
	/// <param name="section">current section number</param>
	/// <returns>next section number</returns>
	int update(float& delta, IModel* model, int section);

	/// <summary>
	/// randomizer
	/// </summary>
	/// <returns>random int between 1, 12</returns>
	int random();
	
private:
	bool split = false;
	bool test = false;
	Route* transition1 = nullptr;
	Route* transition2 = nullptr;
	Route* transition3 = nullptr;
};