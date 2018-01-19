#version 330 core

//layout(location = 0) in vec3 pos;
attribute vec3 pos;
attribute vec4 color;
attribute vec2 texcoord;

out vec4 v_Color;
out vec2 v_Texcoord;
void main()
{
	gl_Position = vec4(pos, 1.0);
	v_Color     = color;
	v_Texcoord  = texcoord;
}