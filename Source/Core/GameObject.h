#pragma once

#include "Components/Transform.h"
#include "Components/SpriteRenderer.h"

#include <iostream>

class GameObject
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

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

private:
	Transform* GetComponent(Transform* v);
	SpriteRenderer* GetComponent(SpriteRenderer* v);
};
