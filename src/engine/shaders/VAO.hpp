#pragma once

#include <lib/glad/glad.h>
#include "VBO.hpp"

class VAO
{
public:
	VAO();
	~VAO();
public:
	void link_attrib(	VBO& vbo, GLuint layout, GLuint num_components, 
						GLenum type, GLsizeiptr stride, void* offset);

	void bind();
	void unbind();
	void remove();

private:
	GLuint ID;
};