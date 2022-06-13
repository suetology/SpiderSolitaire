#include <iostream>

#include "GL/glew.h"
#include "Application.h"

class Sandbox : public Application
{
public:
	void Start() override
	{
		if (glewInit() != GLEW_OK)
		{
			std::cout << "error\n";
		}

		unsigned int vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		float vertices[] = {
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.0f, 0.5f
		};

		glBufferData(GL_VERTEX_ARRAY, sizeof(vertices), &vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void Update() override
	{

	}
};