#version 330
#define MAX_LIGHTS 10

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texture;
layout (location = 2) in vec3 v_normal;

out vec3 fN;
out vec3 fE;
out vec3 fP;
out vec2 texture;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main()
{
    vec4 v = vec4(v_position, 1.0);
    vec3 pos = ((viewMatrix * modelMatrix) * v).xyz;

    fN = ((viewMatrix * modelMatrix) * vec4(v_normal, 0.0)).xyz;
    fE = -pos;
    fP = (modelMatrix * v).xyz;

    texture = v_texture;

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;
} 
