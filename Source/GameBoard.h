#pragma once

#include <glm/glm.hpp>

#include "Core/Window.h"

class GameBoard
{
private:
	float width, height;
	glm::vec2* cardPiles;
	glm::vec2 deckPile;
	glm::vec2 discardPile;

public:
	GameBoard()
	{
		width = 2 * Window::GetScale() * Window::GetAspectRatio();
		height = 2 * Window::GetScale();
		cardPiles = new glm::vec2[10];

		float step = width / 10;

		for (float x = -width / 2 + step / 2, i = 0; i < 10; x += step, i += 1)
		{
			cardPiles[(int)i] = glm::vec2(x, height / 2 - 0.7f);
		}

		deckPile = glm::vec2(cardPiles[9].x, -height / 2 + 0.7f);
		discardPile = glm::vec2(cardPiles[0].x, -height / 2 + 0.7f);
	}

	inline glm::vec2* GetCardPiles() const { return cardPiles; }
	inline glm::vec2 GetDeckPile() const { return deckPile; }
	inline glm::vec2 GetDiscardPile() const { return discardPile; }

	inline float GetWidth() const { return width; }
	inline float GetHeight() const { return height; }
};

