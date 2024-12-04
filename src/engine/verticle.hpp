#pragma once

#include <vector>
#include "window.hpp"
#include "utils.hpp"
#include "api.hpp"
#include <spdlog/spdlog.h>

class triangle
{
public:
	triangle(bool polygon_mode = false) : is_polygon_mode(polygon_mode)
	{
		if(is_polygon_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	~triangle()
	{
		spdlog::info("Destroy triangle");
		glDeleteVertexArrays(1, &vertex_array_obj);
		glDeleteBuffers(1, &vertex_buffer_obj);
		glDeleteProgram(shader_program);
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
		int  success;
		char info_log[512];
		
		UInt vertex_shader = create_vertex_shader();
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(vertex_shader, 512, NULL, info_log); 
			spdlog::error("Cant compile vertex shader: {}", info_log);
		}

		UInt fragment_shader = create_fragment_shader();
		glGetProgramiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(fragment_shader, 512, NULL, info_log);
			spdlog::error("Can't compile fragment shader: {}", info_log);
		}

		create_shader_program(vertex_shader, fragment_shader);
		glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(shader_program, 512, NULL, info_log);
			spdlog::error("Can't link shader with vertex and fragment: {}", info_log);
		}

		glDeleteShader(fragment_shader);
		glDeleteShader(vertex_shader);

		init_buffers();
	}

	void draw()
	{
		glUseProgram(shader_program);
		glBindVertexArray(vertex_array_obj);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

private:
	UInt create_vertex_shader()
	{
		UInt vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
		glCompileShader(vertex_shader);
		return vertex_shader;
	}

	UInt create_fragment_shader()
	{
		UInt fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
		glCompileShader(fragment_shader);
		return fragment_shader;
	}

	UInt create_shader_program(UInt vert_shader, UInt fragment_shader)
	{
		shader_program = glCreateProgram();
		glAttachShader(shader_program, vert_shader);
		glAttachShader(shader_program, fragment_shader);
		glLinkProgram(shader_program);
		return shader_program;
	}

	void init_buffers()
	{
		glGenVertexArrays(1, &vertex_array_obj);
		glGenBuffers(1, &vertex_buffer_obj);
		glBindVertexArray(vertex_array_obj);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), vertex.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0); 
		glBindVertexArray(0); 
	}

private:
	unsigned int shader_program;
	unsigned int vertex_array_obj;
	unsigned int vertex_buffer_obj;
	bool is_polygon_mode = false;
	std::vector<float> vertex =
		{ 
			-0.5f, -0.5f, 0,
			0.5f,  -0.5f, 0,
			0,      0.5f, 0,
		};
};