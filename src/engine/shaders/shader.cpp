#include "shader.hpp"
#include <spdlog/spdlog.h>
#include <fstream>
#include <sstream>

shader::shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	spdlog::info("Create shader vertex paht: {}, fragment path: {}", vertexPath, fragmentPath);

	_vertex_content = read(vertexPath);
	_fragment_content = read(fragmentPath);

	const char* vertex_conent = _vertex_content.c_str();
	const char* fragment_conent = _fragment_content.c_str();

	int  success;
	char info_log[512];
	
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_conent, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if(!success) {
		glGetProgramInfoLog(vertex_shader, 512, NULL, info_log); 
		spdlog::error("Cant compile vertex shader: {}", info_log);
	}

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_conent, NULL);
	glCompileShader(fragment_shader);
	glGetProgramiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(fragment_shader, 512, NULL, info_log);
		spdlog::error("Can't compile fragment shader: {}", info_log);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, fragment_shader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(ID, 512, NULL, info_log);
		spdlog::error("Can't link shader with vertex and fragment: {}", info_log);
	}

	glDeleteShader(fragment_shader);
	glDeleteShader(vertex_shader);
}

std::string shader::read(const std::string& path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if (!file) {
		throw std::ios_base::failure("Error opening file: " + path);
	}

	std::ostringstream contentStream;
	contentStream << file.rdbuf();
	
	spdlog::info("Read {}, Content:\n {}", path, contentStream.str());
	return contentStream.str();
}

void shader::activate()
{
	glUseProgram(ID);
}

void shader::remove()
{
	glDeleteProgram(ID);
}

shader::~shader()
{
	spdlog::info("Delete shader: {} {}", _vertex_content, _fragment_content);
}