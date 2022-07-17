#pragma once

#include <glm/glm.hpp>

class Transform
{
public:
	glm::vec2 position;
	glm::vec2 rotation;
	glm::vec2 scale;

	Transform();
};

