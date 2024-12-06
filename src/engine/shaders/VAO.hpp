#pragma once

#include <lib/glad/glad.h>
#include "VBO.hpp"

class VAO
{
public:
	VAO();
	~VAO();
public:
	void link_VBO(VBO& vbo, GLuint layout);

	void bind();
	void unbind();
	void remove();

private:
	GLuint ID;
};