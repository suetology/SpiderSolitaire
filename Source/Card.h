#pragma once

#include "Core/GameObject.h"
#include "Core/Window.h"
#include "Core/Events.h"

#include <functional>

#define Ace 1
#define Jack 11
#define Queen 12
#define King 13

#define IDLE 0
#define MOVING 1
#define PLACED 2

enum class CardSuit
{
	Diamonds,
	Clubs,
	Hearts,
	Spades
};

enum class CardState
{
	Hidden,
	Opened,
	Locked,
	InDeck
};

class Card : public GameObject
{
public:
	std::function<void()> reorderCallback;
	Card* child;
	Card* parent;

private:
	CardSuit suit;
	CardState state;
	int value;
	bool moving;
	glm::vec2 offset;

public:
	Card(CardSuit s, int v, CardState state)
		: suit(s), value(v), state(state), moving(false), offset(glm::vec2(0.0f)) {}

	int Move()
	{
		glm::vec2 position = Window::ScreenToWorldPoint(Events::GetMousePos());

		if (Events::GetMouseButtonDown(0) && this->GetComponent<BoxCollider>()->CheckCollision(position))
		{
			if (this->parent)
			{
				this->GetComponent<SpriteRenderer>()->orderInLayer = this->parent->GetComponent<SpriteRenderer>()->orderInLayer + 1;
			}
			else
			{
				this->GetComponent<SpriteRenderer>()->orderInLayer = 1;
			}
			offset = this->GetComponent<Transform>()->position - position;

			Card* current = this;
			while (current->child)
			{
				current->child->GetComponent<SpriteRenderer>()->orderInLayer = current->GetComponent<SpriteRenderer>()->orderInLayer + 1;
				current->child->offset = current->child->GetComponent<Transform>()->position - position;
				current = current->child;
			}
			moving = true;
			reorderCallback();
		}
		else if (moving && Events::GetMouseButtonUp(0))
		{
			if (this->parent)
			{
				this->GetComponent<SpriteRenderer>()->orderInLayer = this->parent->GetComponent<SpriteRenderer>()->orderInLayer + 1;
			}
			else
			{
				this->GetComponent<SpriteRenderer>()->orderInLayer = 0;
			}

			Card* current = this;
			while (current->child)
			{
				current->child->GetComponent<SpriteRenderer>()->orderInLayer = 0;
				current = current->child;
			}
			reorderCallback();

			moving = false;
			return PLACED;
		}

		if (moving)
		{
			MoveObject();

			Card* current = this;
			while (current->child)
			{
				current->child->MoveObject();
				current = current->child;
			}
			return MOVING;
		}
		return IDLE;
	}

	void SetChild(Card* other)
	{
		child = other;
		other->parent = this;

		Card* current = this;
		while (current->child)
		{
			current->child->GetComponent<Transform>()->position =
				glm::vec2(current->GetComponent<Transform>()->position.x, current->GetComponent<Transform>()->position.y - 0.25f * current->GetComponent<Transform>()->scale.y);
			current->child->GetComponent<SpriteRenderer>()->orderInLayer = current->GetComponent<SpriteRenderer>()->orderInLayer + 1;
			current = current->child;
		}
		reorderCallback();
	}

	void ReturnChild()
	{
		Card* current = this;
		while (current->child)
		{
			current->child->GetComponent<Transform>()->position =
				glm::vec2(current->GetComponent<Transform>()->position.x, current->GetComponent<Transform>()->position.y - 0.25f * current->GetComponent<Transform>()->scale.y);
			current->child->GetComponent<SpriteRenderer>()->orderInLayer = current->GetComponent<SpriteRenderer>()->orderInLayer + 1;
			current = current->child;
		}
		reorderCallback();
	}

	inline CardSuit GetSuit() const { return suit; }
	inline int GetValue() const { return value; }

private:
	void MoveObject()
	{
		glm::vec2 position = Window::ScreenToWorldPoint(Events::GetMousePos());
		this->GetComponent<Transform>()->position = position + offset;
	}
};


