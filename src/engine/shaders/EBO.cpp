#include "EBO.hpp"
#include <lib/glad/glad.h>
#include <vector>
#include <spdlog/spdlog.h>

EBO::EBO(std::vector<GLuint> indices)
{
	spdlog::info("Create EBO");
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

EBO::~EBO()
{
	remove();
}

void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}

void EBO::remove()
{
	glDeleteBuffers(1, &ID);
}