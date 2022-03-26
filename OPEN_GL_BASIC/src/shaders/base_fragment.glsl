#version 330

out vec4 FragColor;
in vec4	 color;


void main()
{
	FragColor = color;
	// gl_FragColor = vec4(1.0, 0.0, 0.0, 0.1);
};