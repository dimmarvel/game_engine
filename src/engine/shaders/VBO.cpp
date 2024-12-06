#include "VBO.hpp"
#include <lib/glad/glad.h>
#include <vector>
#include <spdlog/spdlog.h>

VBO::VBO(std::vector<GLfloat> vertices)
{
	spdlog::info("Create VBO");
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
}

VBO::~VBO()
{
	remove();
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
}

void VBO::remove()
{
	glDeleteBuffers(1, &ID);
}