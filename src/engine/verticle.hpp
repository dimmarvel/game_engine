#pragma once

#include <vector>
#include <spdlog/spdlog.h>

#include "window.hpp"
#include "api.hpp"

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
		setup();
	}

	~triangle()
	{
		spdlog::info("Destroy triangle");
	}
	
	void setup()
	{
		if(is_polygon_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		_vao = std::make_unique<VAO>();
		_vao->bind();
		_vbo = std::make_unique<VBO>(_vertex);
		_ebo = std::make_unique<EBO>(_indices);
		_vao->link_attrib(*_vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		_vao->link_attrib(*_vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		_vao->unbind();
		_vbo->unbind();
		_ebo->unbind();
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