#version 330 core

uniform sampler2D U_SatelliteTexture;
uniform sampler2D U_WeathTexture;

in vec4 v_Color;
in vec2 v_Texcoord;

void main()
{
	vec4 color0 = texture2D(U_SatelliteTexture, v_Texcoord.xy);
	vec4 color1 = texture2D(U_WeathTexture, v_Texcoord.xy);
	gl_FragColor=  color0 + color1 ;
}