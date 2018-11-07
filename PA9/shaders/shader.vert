#version 330

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texture;
layout (location = 2) in vec3 v_normal;

out vec4 color;
out vec2 texture;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform vec4 ambientProduct, diffuseProduct, specularProduct;
uniform vec4 lightPosition;
uniform float shininess;

uniform sampler2D gSampler;

void main(void)
{
    vec4 v = vec4(v_position, 1.0);
    vec3 pos = ((viewMatrix * modelMatrix) * v).xyz;

    vec3 L = normalize(lightPosition.xyz - pos);
    vec3 E = normalize(-pos);
    vec3 H = normalize(L + E);

    vec3 N = normalize((viewMatrix * modelMatrix) * vec4(v_normal, 0.0)).xyz;

    vec4 ambient = ambientProduct;

    float Kd = max(dot(L,N), 0.0);
    vec4 diffuse = Kd * diffuseProduct;

    float Ks = pow(max(dot(N,H), 0.0), shininess);
    vec4 specular = Ks * specularProduct;
    if (dot(L,N) < 0.0)
    {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;

    texture = v_texture;

    color = ambient + diffuse + specular;
    color.a = 1.0;

}
