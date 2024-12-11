#pragma once

#include <vector>
#include "window.hpp"
#include "utils.hpp"
#include "api.hpp"
#include <spdlog/spdlog.h>

#include <engine/shaders/shader.hpp>
#include <engine/shaders/VAO.hpp>
#include <engine/shaders/VBO.hpp>
#include <engine/shaders/EBO.hpp>

class triangle
{
public:

	triangle(std::vector<GLfloat> vertex, std::vector<GLuint> indices, std::shared_ptr<shader> shader, bool polygon_mode = false) : 
		_vertex(vertex),
		_indices(indices),
		_shader_program(shader)
	{
		if(is_polygon_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		_vao = std::make_unique<VAO>();
		_vao->bind();
		_vbo = std::make_unique<VBO>(_vertex);
		_ebo = std::make_unique<EBO>(_indices);
		_vao->link_VBO((*_vbo), 0);
		_vao->unbind();
		_ebo->unbind();
	}

	~triangle()
	{
		spdlog::info("Destroy triangle");
	}

	void enable_polygons()
	{
		if(is_polygon_mode) return;
		is_polygon_mode = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void disable_polygons()
	{
		if(!is_polygon_mode) return;
		is_polygon_mode = false;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	bool is_polygons()
	{
		return is_polygon_mode;
	}

	void draw()
	{
		_shader_program->activate();
		_vao->bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	}

private:
	std::vector<GLfloat> 	_vertex;
	std::vector<GLuint> 	_indices;

	std::shared_ptr<shader> _shader_program;
	std::unique_ptr<VAO> 	_vao;
	std::unique_ptr<VBO> 	_vbo;
	std::unique_ptr<EBO> 	_ebo;
	
	bool is_polygon_mode = false;
};