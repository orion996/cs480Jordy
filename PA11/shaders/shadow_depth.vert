#version 440

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texture;

out vec4 fragPosition;
out vec2 fragTexture;

uniform mat4 lightSpaceMatrix;
uniform mat4 modelMatrix;

void main()
{
	fragTexture = v_texture;
	fragPosition = (lightSpaceMatrix * modelMatrix) * vec4(v_position, 1.0);
    gl_Position = fragPosition;
} 