#version 330 core

attribute vec3 position;
attribute vec4 normal;
attribute vec2 texcoord;

out vec2 v_Texcoord;

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
	v_Texcoord  = texcoord;
}