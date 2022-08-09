#pragma once

#include "Components/Transform.h"
#include "Components/SpriteRenderer.h"
#include "Components/BoxCollider.h"

class GameObject
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	BoxCollider* boxCollider;

public:
	GameObject();
	~GameObject();

	void Render();

	template <class T>
	T* GetComponent()
	{
		T* temp = nullptr;
		return GetComponent(temp);
	}

	void AddComponent(Transform* t);
	void AddComponent(SpriteRenderer* sr);
	void AddComponent(BoxCollider* bc);

private:
	Transform* GetComponent(Transform* v);
	SpriteRenderer* GetComponent(SpriteRenderer* v);
	BoxCollider* GetComponent(BoxCollider* v);
};
