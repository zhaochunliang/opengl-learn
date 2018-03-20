#version 330 core

attribute vec3 position;
attribute vec4 normal;
attribute vec2 texcoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 v_Texcoord;

void main()
{
	gl_Position = P * V * M * vec4(position.x, position.y, position.z, 1.0);
	v_Texcoord  = texcoord;
}