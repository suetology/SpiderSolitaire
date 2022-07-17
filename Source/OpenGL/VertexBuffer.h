#pragma once

#include "GL/glew.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* vertices, GLsizeiptr size);
	VertexBuffer(int number, int textureWidth, int textureHeight, int spriteWidth, int spriteHeight);
	VertexBuffer();
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_Id;
};

