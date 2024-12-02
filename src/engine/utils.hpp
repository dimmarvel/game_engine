#pragma once

static constexpr const char *fragment_shader_code = "#version 330 core\n" // TODO: move to files and read it
	"out vec4 fragment_color;\n"
	"void main()\n"
	"{\n"
	"   fragment_color = vec4(1, 0.375f, 0, 1);\n"
	"}\0";
 
const char *vertex_shader_code = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
