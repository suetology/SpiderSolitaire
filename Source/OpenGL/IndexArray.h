#pragma once

#include "GL/glew.h"

class IndexBuffer
{
public:
	IndexBuffer(const void* indices, GLsizeiptr size);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	void Delete();

private:
	unsigned int m_Id;
};

