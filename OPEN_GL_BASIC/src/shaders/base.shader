#shader vertex
#version 330
attribute vec2 coord2d;
void main()
{
	gl_Position = vec4(coord2d, 0.0, 1.0);
};
#end shader vertex

#shader fragment
#version 330
void main()
{
	gl_FragColor = vec4(1.0, 0.0, 0.0, 0.1);
};
#end shader fragment