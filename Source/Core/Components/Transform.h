#pragma once

#include <glm/glm.hpp>

class Transform
{
public:
	glm::vec2 position;
	glm::vec2 rotation;
	glm::vec2 scale;

	Transform(glm::vec2 p = glm::vec2(0.0f),
			  glm::vec2 r = glm::vec2(0.0f),
			  glm::vec2 s = glm::vec2(1.0f));
};

