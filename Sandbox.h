#include <iostream>

#include "Application.h"

class Sandbox : public Application
{
public:
	void Start() override
	{
		std::cout << "sandbox" << std::endl;
	}

	void Update() override
	{
	}
};