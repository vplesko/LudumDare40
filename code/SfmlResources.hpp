#pragma once

#include <unordered_map>

template <class T> class SfmlResources {
	typedef std::unordered_map<std::string, T*> SfmlResMap;

	SfmlResMap container;

public:

	const T& get(std::string path);

	void clear();

	~SfmlResources();

	struct ErrNotFound {
		std::string path;

		ErrNotFound(const std::string &Path) : path(Path) {}
	};
};

template <class T> const T& SfmlResources<T>::get(std::string path) {
	try {
		return *container.at(path);
	} catch (const std::out_of_range&) {
		std::pair<std::string, T*> elem;
		
		elem.first = path;
		elem.second = new T();
		if (!elem.second->loadFromFile(path)) {
			delete elem.second;
			
			throw SfmlResources::ErrNotFound(path);
		}
		
		std::pair<typename SfmlResMap::const_iterator, bool> loc = container.insert(elem);
		if (!loc.second) {
			delete elem.second;
			
			throw SfmlResources::ErrNotFound(path);
		}
		
		return *loc.first->second;
	}
}
	
template <class T> void SfmlResources<T>::clear() {
	for (typename SfmlResMap::iterator iter = container.begin(); iter != container.end(); ++iter)
		delete iter->second;
	
	container.clear();
}

template <class T> SfmlResources<T>::~SfmlResources() {
	clear();
}
