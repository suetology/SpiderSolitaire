#pragma once

#include <iostream>

#include "Core/Events.h"
#include "Core/GameObject.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/Texture.h"
#include "OpenGL/Shader.h"
#include "stb_image/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Game
{
public:
	Shader* shader;
	Texture* texture;

	GameObject* object;

	void Start()
	{
		texture = new Texture("Cards.png");
		shader = load_shader("basic.vertex", "basic.fragment");
		
		object = new GameObject();
		object->AddComponent(new Transform());
		object->AddComponent(new SpriteRenderer(shader, texture, 5, 13, 4));
	}

	void Update()
	{
		object->Render();
	}
};