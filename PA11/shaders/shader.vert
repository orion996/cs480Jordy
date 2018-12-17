#version 330
#define MAX_LIGHTS 10

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texture;
layout (location = 2) in vec3 v_normal;

out vec4 color;
out vec2 texture;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform int numLights;
uniform struct Light {
    vec4 ambientProduct, diffuseProduct, specularProduct;
    vec4 lightPosition;
    vec3 lightDirection;
    float lightAngle;
    float shininess;
    float attenuationProduct;
} lights[MAX_LIGHTS];

uniform sampler2D gSampler;

void main(void)
{
    vec4 v = vec4(v_position, 1.0);
    vec3 pos = ((viewMatrix * modelMatrix) * v).xyz;
    
    vec3 E = normalize(-pos);

    vec3 N = normalize((viewMatrix * modelMatrix) * vec4(v_normal, 0.0)).xyz;

    vec3 linearColor = vec3(0);

    for (int i = 0; i < numLights; i++)
    {
        vec3 L = normalize(lights[i].lightPosition.xyz - (modelMatrix * vec4(v_position, 1.0)).xyz);
        vec3 H = normalize(L + E);

        vec4 ambient = lights[i].ambientProduct;

        float Kd = max(dot(L,N), 0.0);
        vec4 diffuse = Kd * lights[i].diffuseProduct;

        float Ks = pow(max(dot(N,H), 0.0), lights[i].shininess);
        vec4 specular = Ks * lights[i].specularProduct;
        if (dot(L,N) < 0.0)
        {
            specular = vec4(0.0, 0.0, 0.0, 1.0);
        }

        //calculate attenuation
        float distanceToLight = length(lights[i].lightPosition.xyz - (modelMatrix * v).xyz);
        float attenuation = 1.0 / (1.0 + lights[i].attenuationProduct * pow(distanceToLight, 2));

        //if object is outside the cone of influence, set attenuation to zero
        vec3 direction = normalize(lights[i].lightDirection);
        float lightToSurfaceAngle = degrees(acos(dot(-L,direction)));
        if (lightToSurfaceAngle > lights[i].lightAngle)
        {
            attenuation = 0.0;
        }

        linearColor += (ambient + (attenuation * (diffuse + specular))).xyz;
    }

    vec3 gamma = vec3(1.0/2.2);

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;

    texture = v_texture;
    color = vec4(pow(linearColor, gamma), 1.0);
}
