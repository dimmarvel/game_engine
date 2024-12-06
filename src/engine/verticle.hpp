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
	triangle(std::shared_ptr<shader> shader_ptr, VAO& vao, VBO& vbo, EBO& ebo, bool polygon_mode = false) : 
		_shader_program(shader_ptr),
		_vao(vao),
		_vbo(vbo),
		_ebo(ebo)
	{
		if(is_polygon_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

	void init()
	{
	}

	void draw()
	{
		_shader_program->activate();
		_vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

private:

	std::shared_ptr<shader> _shader_program;
	VAO& _vao;
	VBO& _vbo;
	EBO& _ebo;
	bool is_polygon_mode = false;

};