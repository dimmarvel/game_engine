#pragma once

#include <lib/glad/glad.h>
#include <vector>

class VBO
{
public:
	VBO(std::vector<GLfloat> vertices);
	~VBO();
public:
	void bind();
	void unbind();
	void remove();

private:
	GLuint ID;
};