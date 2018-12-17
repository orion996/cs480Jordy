#version 330

in vec4 color;
in vec2 texture;

uniform sampler2D gSampler;

void main(void)
{
	vec4 frag_color = texture2D(gSampler, texture.st);
	gl_FragColor = color * frag_color;
}

