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

#define CARD_COUNT 9 

class Game
{
public:
	Shader* shader;
	Texture* cardsTexture;
	Texture* backTexture;

	GameBoard* gameBoard;
	Card** cards;
	std::vector<int> renderQueue;

	bool move = false;

	void Start()
	{
		cardsTexture = new Texture("Cards.png");
		backTexture = new Texture("CardBack.png");

		shader = load_shader("basic.vertex", "basic.fragment");
		
		gameBoard = new GameBoard();
		cards = new Card*[CARD_COUNT];
		renderQueue.reserve(CARD_COUNT);

		Sprite* cardBackSprite = new Sprite(backTexture);

		for (int i = 0; i < CARD_COUNT; i++)
		{
			int cardValue = 1;
			cards[i] = new Card(CardSuit::Clubs, cardValue, CardState::Opened);
			cards[i]->reorderCallback = std::bind(&Game::SortRenderQueue, this);

			Sprite* cardFrontSprite = new Sprite(cardsTexture, cardValue - 1, 13, 4);

			SpriteRenderer* spriteRenderer = new SpriteRenderer(SortingLayer::Open, shader, cardFrontSprite, cardBackSprite, cardBackSprite);
			Transform* transform = new Transform(gameBoard->GetCardPiles()[i]);
			BoxCollider* boxCollider = new BoxCollider(transform, spriteRenderer);

			cards[i]->AddComponent(transform);
			cards[i]->AddComponent(spriteRenderer);
			cards[i]->AddComponent(boxCollider);

			renderQueue.push_back(i);
		}
	}

	void Update()
	{
		for (int i = CARD_COUNT - 1; i >= 0; i--)
		{
			if (int state = cards[renderQueue[i]]->Move())
			{
				if (state == PLACED)
				{
					for (int j = 0; j < CARD_COUNT; j++)
					{
						if (cards[renderQueue[i]]->child != cards[j] &&
							cards[j] != cards[renderQueue[i]] &&
							cards[j]->GetComponent<BoxCollider>()->CheckCollision(cards[renderQueue[i]]->GetComponent<Transform>()->position))
						{
							if (cards[renderQueue[i]]->parent)
							{
								cards[renderQueue[i]]->parent->child = nullptr;
								cards[renderQueue[i]]->parent = nullptr;
							}

							cards[j]->SetChild(cards[renderQueue[i]]);
							break;
						}
						else if (cards[j]->child == cards[renderQueue[i]])
						{
							cards[j]->ReturnChild();
						}
					}
				}
				break;
			}
		}

		for (int i = 0; i < CARD_COUNT; i++)
		{
			cards[renderQueue[i]]->Render();
		}
	} 

	void SortRenderQueue()
	{
		for (int i = 0; i < renderQueue.size() - 1; i++)
		{
			for (int j = i + 1; j < renderQueue.size(); j++)
			{
				if (cards[renderQueue[i]]->GetComponent<SpriteRenderer>()->orderInLayer >
					cards[renderQueue[j]]->GetComponent<SpriteRenderer>()->orderInLayer)
				{
					int temp = renderQueue[i];
					renderQueue[i] = renderQueue[j];
					renderQueue[j] = temp;
				}
			}
		}
	}
};