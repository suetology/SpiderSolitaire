#pragma once

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Events.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/Texture.h"
#include "OpenGL/Shader.h"
#include "stb_image/stb_image.h"
#include "GameBoard.h"
#include "Card.h"
#include "Deck.h"

#define CARD_COUNT 104
#define OPENED_CARDS 10
#define HIDDEN_CARDS 44
#define CARDS_IN_DECK 50

class Game
{
public:
	Shader* shader;
	Texture* cardsTexture;
	Texture* backTexture;

	GameBoard* gameBoard;

	void Start()
	{
		cardsTexture = new Texture("Cards.png", 13, 4);
		backTexture = new Texture("CardBack.png");

		shader = load_shader("basic.vertex", "basic.fragment");
		
		gameBoard = new GameBoard();

		Deck::cards.reserve(CARD_COUNT);

		Sprite* cardBackSprite = new Sprite(backTexture);

		for (int i = 0; i < CARD_COUNT; i++)
		{
			int cardValue = i % 13 + 1;
			Deck::cards.push_back(new Card(CardSuit::Clubs, cardValue));

			Sprite* cardFrontSprite = new Sprite(cardsTexture, cardValue);

			SpriteRenderer* spriteRenderer = new SpriteRenderer(SortingLayer::Hidden, shader, cardFrontSprite, cardBackSprite, cardFrontSprite);
			Transform* transform = new Transform(glm::vec2(0.0f));
			BoxCollider* boxCollider = new BoxCollider(transform, spriteRenderer);

			Deck::cards[i]->AddComponent(transform);
			Deck::cards[i]->AddComponent(spriteRenderer);
			Deck::cards[i]->AddComponent(boxCollider);
		}
		Deck::Shuffle();

		for (int j = 0; j < CARDS_IN_DECK; j++)
		{
			Deck::cardsInDeck[j]->homePosition = gameBoard->GetDeckPile();
			Deck::cardsInDeck[j]->GetComponent<Transform>()->position = gameBoard->GetDeckPile();
			Deck::cardsInDeck[j]->state = CardState::InDeck;
			Deck::cardsInDeck[j]->GetComponent<SpriteRenderer>()->SetBackSprite();
		}

		int i = 0;
		for (int j = 0; j < HIDDEN_CARDS; j++)
		{
			glm::vec2 pos = glm::vec2(gameBoard->GetCardPiles()[j % 10].x, gameBoard->GetCardPiles()[j % 10].y - 0.1f * (j / 10));
			Deck::cards[i + j]->homePosition = pos;
			Deck::cards[i + j]->GetComponent<Transform>()->position = pos;
			Deck::cards[i + j]->state = CardState::Hidden;
			Deck::cards[i + j]->GetComponent<SpriteRenderer>()->SetBackSprite();

			if (j >= 10)
			{
				Deck::cards[i + j - 10]->locker = Deck::cards[i + j];
				Deck::cards[i + j]->locked = Deck::cards[i + j - 10];
			}
		}
		i += HIDDEN_CARDS;

		for (int j = 0; j < OPENED_CARDS; j++)
		{
			int offset = (j + 4) % 10 < 4 ? 5 : 4;
			glm::vec2 pos = glm::vec2(gameBoard->GetCardPiles()[(j + 4) % 10].x, gameBoard->GetCardPiles()[(j + 4) % 10].y - 0.1f * offset);
			Deck::cards[i + j]->homePosition = pos;
			Deck::cards[i + j]->GetComponent<Transform>()->position = pos;
			Deck::cards[i + j]->state = CardState::Opened;

			Deck::cards[i + j - 10]->locker = Deck::cards[i + j];
			Deck::cards[i + j]->locked = Deck::cards[i + j - 10];
		}
	}

	void Update()
	{
		for (int i = Deck::cards.size() - 1; i >= 0; i--)
		{	
			if (Deck::cards[i]->Move())
			{
				break;
			}
		}

		for (int i = 0; i < Deck::cards.size(); i++)
		{
			Deck::cards[i]->Render();
		}

		if (Deck::cardsInDeck.size() > 0)
		{
			Deck::cardsInDeck[0]->Render();

			if (Events::GetMouseButtonDown(0) && Deck::cardsInDeck[0]->GetComponent<BoxCollider>()->CheckCollision(Window::ScreenToWorldPoint(Events::GetMousePos())))
			{
				std::vector<Card*> newCards;
				for (int i = 0; i < Deck::cards.size(); i++)
				{
					if (Deck::cards[i]->state == CardState::Opened && !Deck::cards[i]->child)
					{
						Deck::cardsInDeck[0]->GetComponent<SpriteRenderer>()->orderInLayer =
							Deck::cards[i]->GetComponent<SpriteRenderer>()->orderInLayer + 1;
						
						Deck::cards[i]->state = CardState::Locked;
						Deck::cardsInDeck[0]->state = CardState::Opened;

						Deck::cards[i]->locker = Deck::cardsInDeck[0];
						Deck::cardsInDeck[0]->locked = Deck::cards[i];

						Deck::cardsInDeck[0]->GetComponent<SpriteRenderer>()->SetFrontSprite();
						Deck::cardsInDeck[0]->GetComponent<Transform>()->position = Deck::cards[i]->GetComponent<Transform>()->position;
						Deck::cardsInDeck[0]->GetComponent<Transform>()->position.y -= 0.25f * Deck::cards[i]->GetComponent<Transform>()->scale.y;

						Deck::cardsInDeck[0]->homePosition = Deck::cardsInDeck[0]->GetComponent<Transform>()->position;

						newCards.push_back(Deck::cardsInDeck[0]);
						Deck::cardsInDeck.erase(Deck::cardsInDeck.begin(), Deck::cardsInDeck.begin() + 1);
					}
				}
				Deck::cards.insert(Deck::cards.end(), newCards.begin(), newCards.end());
			}
		}
	} 
};