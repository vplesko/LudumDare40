#pragma once

#include <vector>
#include <algorithm>

template<class T>
class VectorWrapper {
	std::vector<T> vect;

	bool dealloc;

public:
	VectorWrapper(bool deallocateAsPointer) : dealloc(deallocateAsPointer) {}

	const std::vector<T>& getVector() const { return vect; }
	std::vector<T>& getVector() { return vect; }

	const T& operator[](std::size_t index) const { return vect[index]; }
	T& operator[](std::size_t index) { return vect[index]; }

	std::size_t getSize() const { return vect.size(); }
	
	void add(T elem) { vect.push_back(elem); }

	void remove(T elem, bool destruct);
	void remove(T elem) { remove(elem, dealloc); }

	void remove(std::size_t index, bool destruct);
	void remove(std::size_t index) { remove(index, dealloc); }

	~VectorWrapper();
};

template<class T>
void VectorWrapper<T>::remove(T elem, bool destruct) {
	vect.erase(std::remove(vect.begin(), vect.end(), elem), vect.end());
	if (destruct) delete elem;
}

template<class T>
void VectorWrapper<T>::remove(std::size_t index, bool destruct) {
	if (index >= vect.size()) return;
	
	if (destruct) delete vect[index];

	for (std::size_t i = index; i + 1 < vect.size(); ++i)
		vect[i] = vect[i + 1];

	vect.pop_back();
}

template<class T>
VectorWrapper<T>::~VectorWrapper() {
	if (dealloc) {
		for (std::size_t i = 0; i < vect.size(); ++i) delete vect[i];
	}
}