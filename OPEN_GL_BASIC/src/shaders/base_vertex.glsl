#version 330

attribute vec2 coord2d;

out vec4 color;

// uniform vec4 test_color;

void main()
{
	color		= vec4(cos(coord2d.x), sin(coord2d.y), 0.0, 1.0);
	gl_Position = vec4(coord2d, 0.0, 1.0);
};