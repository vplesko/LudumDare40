#include "Observed.hpp"
#include "Observer.hpp"

void Observed::add(Observer *O) {
	observers.push_back(O);
}

void Observed::notify() {
	for (std::size_t i = 0; i < observers.size(); ++i)
		observers[i]->notify(this);
}