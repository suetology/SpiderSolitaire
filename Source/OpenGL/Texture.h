#pragma once

#include <GL/glew.h>

class Texture
{
public:
	Texture(const char* filename);
	~Texture();

	void Bind() const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_Id;
	int m_Width, m_Height, m_NrChannels;
};

