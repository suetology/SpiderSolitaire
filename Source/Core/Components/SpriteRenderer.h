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
	Open
};

struct Sprite
{
	Texture* texture;
	VertexArray* vao;
	VertexBuffer* vbo;
	int spriteNumber, spriteColumn, spriteRow;
	float spriteRatio;

	Sprite(Texture* tex, int sn = 0, int sc = 1, int sr = 1)
		: texture(tex), spriteNumber(sn), spriteColumn(sc), spriteRow(sr)
	{
		spriteRatio = ((float)texture->GetWidth() / spriteColumn) / ((float)texture->GetHeight() / spriteRow);
		vao = new VertexArray();
		vao->Bind();
		vbo = new VertexBuffer(spriteNumber, texture->GetWidth(), texture->GetHeight(), texture->GetWidth() / spriteColumn, texture->GetHeight() / spriteRow);
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
};

