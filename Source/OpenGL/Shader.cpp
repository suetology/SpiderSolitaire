#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(unsigned int id)
	: m_Id(id) { }

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

void Shader::Use() const
{
	glUseProgram(m_Id);
}

void Shader::UniformFloat(const char* name, float value)
{
    glUniform1f(glGetUniformLocation(m_Id, name), value);
}

void Shader::UniformVec4f(const char* name, float f1, float f2, float f3, float f4)
{
    glUniform4f(glGetUniformLocation(m_Id, name), f1, f2, f3, f4);
}

void Shader::UniformMat4f(const char* name, const GLfloat* data)
{
	glUniformMatrix4fv(glGetUniformLocation(m_Id, name), 1, GL_FALSE, data);
}

Shader* load_shader(const std::string& vsFilepath, const std::string& fsFilepath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vsFile;
	std::ifstream fsFile;

	vsFile.exceptions(std::ifstream::badbit);
	fsFile.exceptions(std::ifstream::badbit);

	try
	{
		vsFile.open(vsFilepath);
		fsFile.open(fsFilepath);

		std::stringstream vsStream, fsStream;

		vsStream << vsFile.rdbuf();
		fsStream << fsFile.rdbuf();

		vertexCode = vsStream.str();
		fragmentCode = fsStream.str();

		vsFile.close();
		fsFile.close();
	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return nullptr;
	}

	const char* vsCode = vertexCode.c_str();
	const char* fsCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar info[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vsCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, info);
        std::cerr << "SHADER::VERTEX: COMPILATION FAILED" << std::endl;
        std::cerr << info << std::endl;
        return nullptr;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fsCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, info);
        std::cerr << "SHADER::FRAGMENT: COMPILATION FAILED" << std::endl;
        std::cerr << info << std::endl;
        return nullptr;
    }

    GLuint id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, nullptr, info);
        std::cerr << "SHADER::PROGRAM: LINKING FAILED" << std::endl;
        std::cerr << info << std::endl;

        return nullptr;
    }

    return new Shader(id);
}