#pragma once

#include "../../OpenGL/Texture.h"
#include "../../OpenGL/VertexArray.h"
#include "../../OpenGL/VertexBuffer.h"
#include "../../OpenGL/Shader.h"

#include "Transform.h"

class SpriteRenderer
{
	friend class GameObject;

	Shader* shader;
	Texture* texture;
	int spriteColumns, spriteRows;
	VertexArray* vao;
	VertexBuffer* vbo;

	void Render(Transform* transform);
public:
	SpriteRenderer(Shader* s, Texture* texture, int spriteNumber, int spriteColumns, int spriteRows);
	~SpriteRenderer();
};

