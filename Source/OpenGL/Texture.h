#pragma once

#include <GL/glew.h>

class Texture
{
public:
	Texture(const char* filename, int widthInSprites = 1, int heightInSprites = 1);
	~Texture();

	void Bind() const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline int GetWidthInSprites() const { return widthInSprites; }
	inline int GetHeightInSprites() const { return heightInSprites; }

private:
	unsigned int id;
	int width, height, nrChannels;
	int widthInSprites, heightInSprites;
};

