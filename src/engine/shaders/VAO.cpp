#include "VAO.hpp"
#include <spdlog/spdlog.h>

VAO::VAO()
{
	spdlog::info("Create VAO");
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
	remove();
}

void VAO::link_VBO(VBO& vbo, GLuint layout)
{
	vbo.bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(layout);
	vbo.unbind();
}

void VAO::bind()
{
	glBindVertexArray(ID);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

void VAO::remove()
{
	glDeleteVertexArrays(1, &ID);
}