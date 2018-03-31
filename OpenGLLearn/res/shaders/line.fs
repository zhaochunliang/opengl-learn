#version 330 core

uniform vec3 line_color;

void main()
{
	gl_FragColor=  vec4(line_color, 1.0f);
	
}