#include "SpriteRenderer.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Core/Window.h"
#include "../../Core/Events.h"

SpriteRenderer::SpriteRenderer(SortingLayer layer, Shader* s, Sprite* fs, Sprite* bs, Sprite* cs)
{
	sortingLayer = layer;
	orderInLayer = 0;
	shader = s;
	frontSprite = fs;
	backSprite = bs;
	currentSprite = cs;
}

SpriteRenderer::~SpriteRenderer()
{
	delete frontSprite;
	delete backSprite;
}

void SpriteRenderer::Render(Transform* t)
{
	glm::mat4 transform = glm::mat4(1.0f);

	glm::vec2 pos = t->position;
	transform = glm::translate(transform, glm::vec3(pos, 0.0f));
	
	glm::vec2 scale = t->scale;
	transform = glm::scale(transform, glm::vec3(scale, 1.0f));

	glm::vec2 rotation = t->rotation;
	transform = glm::translate(transform, glm::vec3(rotation, 0.0f));

	currentSprite->texture->Bind();
	shader->Use();
	shader->UniformFloat("spriteRatio", currentSprite->GetSpriteRatio());
	shader->UniformFloat("aspectRatio", Window::GetAspectRatio());
	shader->UniformFloat("windowScale", Window::GetScale());
	shader->UniformMat4f("transform", glm::value_ptr(transform));
	currentSprite->vao->Bind();
	currentSprite->vbo->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}