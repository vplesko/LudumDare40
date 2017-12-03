#pragma once

#include <vector>

class Observer;

class Observed {
	std::vector<Observer*> observers;

public:

	void add(Observer *O);

	void notify();

	virtual ~Observed() {}
};