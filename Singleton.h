#pragma once

#include <iostream>

template <typename T>
class Singleton
{
public:
	static T* GetInstance() {
		if (instance == NULL) {
			instance = new T;
		}
		return instance;
	}
protected:
	Singleton() {};
	~Singleton() {};
private:
	static T* instance;
};

template <typename T>
T* Singleton<T>::instance = NULL;
