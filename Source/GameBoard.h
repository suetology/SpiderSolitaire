#pragma once

#include <glm/glm.hpp>

#include "Core/Window.h"

class GameBoard
{
private:
	float width, height;
	glm::vec2* cardPiles;

public:
	GameBoard()
	{
		width = 2 * Window::GetScale() * Window::GetAspectRatio();
		height = 2 * Window::GetScale();
		cardPiles = new glm::vec2[9];

		float step = width / 9;

		for (float x = -width / 2 + step / 2, i = 0; i < 9; x += step, i += 1)
		{
			cardPiles[(int)i] = glm::vec2(x, height / 2 - 0.7f);
		}
	}

	inline glm::vec2* GetCardPiles() const { return cardPiles; }
	inline float GetWidth() const { return width; }
	inline float GetHeight() const { return height; }
};

