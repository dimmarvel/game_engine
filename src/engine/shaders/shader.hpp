#pragma once
#include <lib/glad/glad.h>
#include <string>

class shader
{
public:
	shader(const std::string& vertexPath, const std::string& fragmentPath);
	~shader();

public:
	std::string get_vertex_content() { return _vertex_content; }
	std::string get_fragment_content() { return _fragment_content; }

	std::string read(const std::string& path);

	void activate();
	void remove();
	GLuint get_ID() { return ID; }

private:
	GLuint ID;
	GLuint _shader_program;
	std::string _vertex_content;
	std::string _fragment_content;
};