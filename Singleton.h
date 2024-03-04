#pragma once

#include <iostream>

template <typename T>
class Singleton
{
public:
	static T* GetInstance() {
		if (instance == NULL) {
			instance = new Singleton<T>();
		}
		return instance;
	}
protected:
	Singleton() {};

	static T* instance;
};

