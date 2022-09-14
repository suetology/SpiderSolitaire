#include "Texture.h"

#include "../stb_image/stb_image.h"

Texture::Texture(const char* filename, int widthInSprites, int heightInSprites)
	: widthInSprites(widthInSprites), heightInSprites(heightInSprites)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLint format = GL_RGB;
		if (nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		//std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
