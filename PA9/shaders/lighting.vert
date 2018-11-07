#version 330

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texture;
layout (location = 2) in vec3 v_normal;

out vec3 fN;
out vec3 fE;
out vec3 fL;
out vec3 fP;
out vec2 texture;
//out float attenuation;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

uniform vec4 lightPosition;

void main()
{
	/*
	vec4 v = (viewMatrix * modelMatrix) * vec4(v_position, 1.0);


    fN = ((viewMatrix * modelMatrix) * vec4(v_normal, 0.0)).xyz;
    fE = v.xyz * -1;
    fL = lightPosition.xyz;

    if(lightPosition.w != 0.0){
        fL = lightPosition.xyz - (modelMatrix * vec4(v_position, 1.0)).xyz;
    }

    texture = v_texture;

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;
    */

    vec4 v = vec4(v_position, 1.0);
    vec3 pos = ((viewMatrix * modelMatrix) * v).xyz;

    fN = ((viewMatrix * modelMatrix) * vec4(v_normal, 0.0)).xyz;
    fE = -pos;
    fL = lightPosition.xyz;
    if(lightPosition.w != 0.0)
    {
        fL = lightPosition.xyz - (modelMatrix * vec4(v_position, 1.0)).xyz;
    }
    fP = (modelMatrix * v).xyz;

    //float distanceToLight = length(lightPosition.xyz - (modelMatrix * v).xyz);
    //attenuation = 1.0 / (1.0 + attenuationProduct * pow(distanceToLight, 2));

    texture = v_texture;

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;
} 
