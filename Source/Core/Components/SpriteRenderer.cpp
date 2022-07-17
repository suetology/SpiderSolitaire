#include "SpriteRenderer.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Core/Window.h"
#include "../../Core/Events.h"

SpriteRenderer::SpriteRenderer(Shader* s, Texture* tex, int spriteNumber, int spriteCol, int spriteRow)
{
	spriteColumns = spriteCol;
	spriteRows = spriteRow;
	shader = s;
	texture = tex;
	vao = new VertexArray();
	vao->Bind();
	vbo = new VertexBuffer(spriteNumber, texture->GetWidth(), texture->GetHeight(), texture->GetWidth() / spriteColumns, texture->GetHeight() / spriteRows);
}

SpriteRenderer::~SpriteRenderer()
{
	delete vbo;
	delete vao;
}

void SpriteRenderer::Render(Transform* transform)
{
	glm::vec2 pos = transform->position;
	glm::mat4 translation = glm::mat4(1.0f);
	translation = glm::translate(translation, glm::vec3(pos, 0.0f));

	texture->Bind();
	shader->Use();
	shader->UniformFloat("textureRatio", ((float)texture->GetWidth() / spriteColumns) / ((float)texture->GetHeight() / spriteRows));
	shader->UniformFloat("aspectRatio", Window::GetAspectRatio());
	shader->UniformMat4f("transform", glm::value_ptr(translation));
	vao->Bind();
	vbo->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}