#version 330 core

//layout(location = 0) in vec3 pos;
attribute vec3 pos;

out vec4 v_Color;
void main()
{
	gl_Position = vec4(pos, 1.0);
	v_Color     = vec4(1.0f, 1.0f, 1.0f, 1.0f); 
}