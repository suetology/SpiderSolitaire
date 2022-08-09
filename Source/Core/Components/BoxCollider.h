#pragma once

#include <glm/glm.hpp>

#include "Transform.h"
#include "SpriteRenderer.h"

class BoxCollider
{
public:
	glm::vec2* pos;
	float width, height;

	BoxCollider(Transform* transform, SpriteRenderer* spriteRenderer);

	bool CheckCollision(glm::vec2 point);

private:
	bool RaycastIntersectSide(glm::vec2 borderPointA, glm::vec2 borderPointB, glm::vec2 point);
};

