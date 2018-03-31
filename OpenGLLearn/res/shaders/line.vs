#version 330 core

attribute vec3 position;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;


void main()
{
	gl_Position = P * V * M * vec4(position.x, position.y, position.z, 1.0);
}