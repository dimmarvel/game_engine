#pragma once

#include <lib/glad/glad.h>
#include <vector>

class EBO
{
public:
	EBO(std::vector<GLuint> indices);
	~EBO();

public:
	void bind();
	void unbind();
	void remove();

private:
	GLuint ID;
};