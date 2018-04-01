#version 330 core

uniform sampler2D U_MTexture;

in vec2 v_Texcoord;

void main()
{
	vec4 color0 = texture2D(U_MTexture, v_Texcoord.xy);
	gl_FragColor=  color0;
}