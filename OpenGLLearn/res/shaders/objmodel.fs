#version 330 core

uniform sampler2D U_SatelliteTexture;
uniform sampler2D U_WeatherTexture;

in vec2 v_Texcoord;

void main()
{
	vec4 color0 = texture2D(U_SatelliteTexture, v_Texcoord.xy);
	vec4 color1 = texture2D(U_WeatherTexture,  v_Texcoord.xy);
	gl_FragColor=  color0 * 0.4f +  color1 * 0.5f;
}