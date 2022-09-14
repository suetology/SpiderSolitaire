#pragma once

#include "Core/GameObject.h"
#include "Core/Window.h"
#include "Core/Events.h"
#include "Deck.h"

#include <functional>

#define Ace 1
#define Jack 11
#define Queen 12
#define King 13	

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
	InDeck,
	Gone
};

class Card : public GameObject
{
public:
	Card* child;
	Card* parent;
	Card* locker;
	Card* locked;

	CardState state;
	glm::vec2 homePosition;

private:
	CardSuit suit;
	int value;
	bool moving;
	glm::vec2 offset;

public:
	Card(CardSuit s, int v)
		: suit(s), value(v), state(CardState::InDeck), moving(false), offset(glm::vec2(0.0f)), homePosition(glm::vec2(0.0f)) {}

	bool Move()
	{ 
		glm::vec2 position = Window::ScreenToWorldPoint(Events::GetMousePos());

		if (this->state == CardState::Opened && Events::GetMouseButtonDown(0) && this->GetComponent<BoxCollider>()->CheckCollision(position))
		{	
			TakeCard();
		}
		else if (moving && Events::GetMouseButtonUp(0))
		{
			PlaceCard();
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
		}

		return moving;
	}

	inline CardSuit GetSuit() const { return suit; }
	inline int GetValue() const { return value; }

private:
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
		SortCards();
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
		SortCards();
	}

	void ReturnCard()
	{
		this->GetComponent<Transform>()->position = homePosition;

		Card* current = this;
		while (current->child)
		{
			current->child->GetComponent<Transform>()->position =
				glm::vec2(current->GetComponent<Transform>()->position.x, current->GetComponent<Transform>()->position.y - 0.25f * current->GetComponent<Transform>()->scale.y);
			current->child->GetComponent<SpriteRenderer>()->orderInLayer = current->GetComponent<SpriteRenderer>()->orderInLayer + 1;
			current = current->child;
		}
		SortCards();
	}

	void TakeCard()
	{
		glm::vec2 position = Window::ScreenToWorldPoint(Events::GetMousePos());

		{
			Card* current = this;
			while (current)
			{
				if (current->locker)
				{
					return;
				}
				current = current->child;
			}
		}

		offset = this->GetComponent<Transform>()->position - position;
		this->GetComponent<SpriteRenderer>()->sortingLayer = SortingLayer::Taken;

		Card* current = this;
		while (current->child)
		{
			current->child->GetComponent<SpriteRenderer>()->sortingLayer = SortingLayer::Taken;
			current->child->GetComponent<SpriteRenderer>()->orderInLayer = current->GetComponent<SpriteRenderer>()->orderInLayer + 1;
			current->child->offset = current->child->GetComponent<Transform>()->position - position;
			current = current->child;
		}
		moving = true;
		SortCards();
	}

	void PlaceCard()
	{
		this->GetComponent<SpriteRenderer>()->sortingLayer = SortingLayer::Open;	

		Card* current = this;
		while (current->child)
		{
			current->child->GetComponent<SpriteRenderer>()->sortingLayer = SortingLayer::Open;
			current->child->GetComponent<SpriteRenderer>()->orderInLayer = 0;
			current = current->child;
		}
		moving = false;

		CheckCardCollision();

		SortCards();
	}

	void CheckCardCollision()
	{
		Card* parent = nullptr;

		for (int j = Deck::cards.size() - 1; j >= 0; j--)
		{
			if (Deck::cards[j] == this)
			{
				continue;
			}

			if (Deck::cards[j] != this->child &&
				Deck::cards[j]->GetComponent<BoxCollider>()->CheckCollision(this->GetComponent<Transform>()->position) &&
				Deck::cards[j]->state == CardState::Opened && 
				Deck::cards[j]->GetValue() == this->GetValue() + 1)
			{
				if (this->parent)
				{
					this->parent->child = nullptr;
					this->parent = nullptr;
				}

				Deck::cards[j]->SetChild(this);

				if (this->CheckSet())
				{
					this->CollectSet();
				}

				if (this->locked)
				{
					this->locked->UnlockCard();
				}
				break;
			}
			else if (Deck::cards[j]->child == this)
			{
				parent = Deck::cards[j];
			}

			if (j == 0)
			{
				parent ? parent->ReturnChild() : ReturnCard();
			}
		}
	}

	void UnlockCard()
	{
		this->state = CardState::Opened;
		this->GetComponent<SpriteRenderer>()->SetFrontSprite();
		this->locker->locked = nullptr;
		this->locker = nullptr;
	}

	void MoveObject()
	{
		glm::vec2 position = Window::ScreenToWorldPoint(Events::GetMousePos());
		this->GetComponent<Transform>()->position = position + offset;
	}

	void SortCards()
	{
		std::vector<Card*> taken;
		std::vector<Card*> placed;

		for (int i = 0; i < Deck::cards.size(); i++)
		{
			Deck::cards[i]->GetComponent<SpriteRenderer>()->sortingLayer == SortingLayer::Taken ?
				taken.push_back(Deck::cards[i]) : placed.push_back(Deck::cards[i]);	
		}

		if (taken.size() > 0)
		{
			for (int i = 0; i < taken.size() - 1; i++)
			{
				for (int j = i + 1; j < taken.size(); j++)
				{
					if (taken[i]->GetComponent<SpriteRenderer>()->orderInLayer >
						taken[j]->GetComponent<SpriteRenderer>()->orderInLayer)
					{
						Card* temp = taken[i];
						taken[i] = taken[j];
						taken[j] = temp;
					}
				}
			}
		}

		if (placed.size() > 0)
		{
			for (int i = 0; i < placed.size() - 1; i++)
			{
				for (int j = i + 1; j < placed.size(); j++)
				{
					if (placed[i]->GetComponent<SpriteRenderer>()->orderInLayer >
						placed[j]->GetComponent<SpriteRenderer>()->orderInLayer)
					{
						Card* temp = placed[i];
						placed[i] = placed[j];
						placed[j] = temp;
					}
				}
			}
		}

		Deck::cards.clear();
		Deck::cards.insert(Deck::cards.end(), placed.begin(), placed.end());
		Deck::cards.insert(Deck::cards.end(), taken.begin(), taken.end());
	}

	bool CheckSet()
	{
		int i = 1;

		Card* current = this;
		while (current->child)
		{
			i++;
			current = current->child;
		}
		current = this;
		while (current->parent)
		{
			i++;
			current = current->parent;
		}

		return i == 13;
	}

	void CollectSet()
	{
		Card* current = this;
		while (current->child)
		{
			current->state = CardState::Gone;
			current->homePosition = glm::vec2(-100.0f, 0.0f);
			current->GetComponent<Transform>()->position = glm::vec2(-100.0f, 0.0f);
			current = current->child;
		}
		current = this;
		while (current->parent)
		{
			current->state = CardState::Gone;
			current->homePosition = glm::vec2(-100.0f, 0.0f);
			current->GetComponent<Transform>()->position = glm::vec2(-100.0f, 0.0f);
			current = current->parent;
		}
		current->state = CardState::Gone;
		current->homePosition = glm::vec2(-100.0f, 0.0f);
		current->GetComponent<Transform>()->position = glm::vec2(-100.0f, 0.0f);

		if (current->locked)
		{
			current->locked->UnlockCard();
		}
	}
};


