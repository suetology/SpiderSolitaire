#pragma once

#include "../../OpenGL/Texture.h"
#include "../../OpenGL/VertexArray.h"
#include "../../OpenGL/VertexBuffer.h"
#include "../../OpenGL/Shader.h"

#include "Transform.h"

#include <vector>

enum class SortingLayer
{
	Hidden,
	Open,
	Taken
};

struct Sprite
{
	Texture* texture;
	VertexArray* vao;
	VertexBuffer* vbo;
	int spriteNumber;
	float spriteRatio;

	Sprite(Texture* tex, int sn = 0)
		: texture(tex), spriteNumber(sn - 1)
	{
		spriteRatio = ((float)texture->GetWidth() / texture->GetWidthInSprites()) / ((float)texture->GetHeight() / texture->GetHeightInSprites());
		vao = new VertexArray();
		vao->Bind();
		vbo = new VertexBuffer(spriteNumber, texture->GetWidth(), texture->GetHeight(), texture->GetWidth() / texture->GetWidthInSprites(), texture->GetHeight() / texture->GetHeightInSprites());
	}

	~Sprite()
	{
		delete vbo;
		delete vao;
	}

	inline float GetSpriteRatio() { return spriteRatio; }
};

class SpriteRenderer
{
	friend class GameObject;

	Shader* shader;

	Sprite* currentSprite;
	Sprite* frontSprite;
	Sprite* backSprite;

	void Render(Transform* transform);
public:
	SortingLayer sortingLayer;
	int orderInLayer;

	SpriteRenderer(SortingLayer layer, Shader* s, Sprite* fs, Sprite* bs, Sprite* cs);
	~SpriteRenderer();

	inline Sprite* GetCurrentSprite() { return currentSprite; }

	inline void SetFrontSprite() { currentSprite = frontSprite; }
	inline void SetBackSprite() { currentSprite = backSprite; }
};

