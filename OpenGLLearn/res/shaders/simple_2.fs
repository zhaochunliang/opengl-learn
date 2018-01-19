#version 330 core

uniform sampler2D U_MainTexture;

in vec4 v_Color;
in vec2 v_Texcoord;

void main()
{
	gl_FragColor= v_Color* texture2D(U_MainTexture, v_Texcoord.xy);
}