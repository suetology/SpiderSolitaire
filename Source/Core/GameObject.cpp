#include "GameObject.h"
	
GameObject::GameObject()
{
	transform = nullptr;
	spriteRenderer = nullptr;
}

GameObject::~GameObject()
{
	if (transform != nullptr)
		delete transform;
	if (spriteRenderer != nullptr)
		delete spriteRenderer;
}

void GameObject::Render()
{
	if (spriteRenderer != nullptr && transform != nullptr)
	{
		spriteRenderer->Render(transform);
	}
}

void GameObject::AddComponent(Transform * t)
{
	transform = t;
}

void GameObject::AddComponent(SpriteRenderer * sr)
{
	spriteRenderer = sr;
}

Transform* GameObject::GetComponent(Transform * v)
{
	delete v;
	return transform;
}
SpriteRenderer* GameObject::GetComponent(SpriteRenderer * v)
{
	delete v;
	return spriteRenderer;
}