#include "BoxCollider.h"

BoxCollider::BoxCollider(Transform* transform, SpriteRenderer* spriteRenderer)
{
    pos = (glm::vec2*)&transform->position;
    width = transform->scale.x * spriteRenderer->GetCurrentSprite()->GetSpriteRatio();
    height = transform->scale.y;
}

bool BoxCollider::CheckCollision(glm::vec2 point)
{
    int count = 0;

    glm::vec2 borders[] = { glm::vec2(pos->x - width / 2, pos->y - height / 2),
                            glm::vec2(pos->x - width / 2, pos->y + height / 2),
                            glm::vec2(pos->x + width / 2, pos->y + height / 2),
                            glm::vec2(pos->x + width / 2, pos->y - height / 2) };
    for (int i = 0; i < 4; i++)
    {
        if (RaycastIntersectSide(borders[i], borders[(i + 1) % 4], point))
        {
            count++;
        }
    }
    return count % 2 != 0;
}

bool BoxCollider::RaycastIntersectSide(glm::vec2 borderPointA, glm::vec2 borderPointB, glm::vec2 point)
{
    if (borderPointA.y > borderPointB.y)
    {
        return RaycastIntersectSide(borderPointB, borderPointA, point);
    }
    if (point.y > borderPointB.y || point.y < borderPointA.y)
    {
        return false;
    }
    if (point.y < borderPointB.y && point.y > borderPointA.y)
    {
        if (point.x > glm::max(borderPointA.x, borderPointB.x))
        {
            return false;
        }
        if (point.x < glm::min(borderPointA.x, borderPointB.x))
        {
            return true;
        }
    }
    float angleAB = (borderPointB.y - borderPointA.y) / (borderPointB.x - borderPointA.x);
    float angleAP = (point.y - borderPointA.y) / (point.x - borderPointA.x);
    if (angleAP > angleAB)
    {
        return true;
    }
    else
    {
        return false;
    }
}
