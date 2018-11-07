#version 330

in vec3 fN;
in vec3 fL;
in vec3 fE;
in vec3 fP;
in vec2 texture;
//in float attenuation;

uniform vec4 ambientProduct, diffuseProduct, specularProduct;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform vec4 lightPosition;
uniform vec3 lightDirection;
uniform float lightAngle;
uniform float shininess;
uniform float attenuationProduct;

uniform sampler2D gSampler;

void main()
{
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
    vec3 H = normalize(L + E);

    vec4 ambient = ambientProduct;

    float Kd = max(dot(L,N), 0.0);
    vec4 diffuse = Kd * diffuseProduct;

    float Ks = pow(max(dot(N, H), 0.0), shininess);
    vec4 specular = Ks * specularProduct;

    if(dot(L,N) < 0.0){
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    //calculate attenuation
    float distanceToLight = length(lightPosition.xyz - fP);
    float attenuation = 1.0 / (1.0 + attenuationProduct * pow(distanceToLight, 2));

    //if object is outside the cone of influence, set attenuation to zero
    vec3 direction = normalize(lightDirection);
    float lightToSurfaceAngle = degrees(acos(dot(-L,direction)));
    if (lightToSurfaceAngle > lightAngle)
    {
        attenuation = 0.0;
    }

    vec3 linearColor = (ambient + (attenuation * (diffuse + specular))).xyz;

    vec3 gamma = vec3(1.0/2.2);

    gl_FragColor = vec4(pow(linearColor, gamma), 1.0) * texture2D(gSampler, texture.st);
    gl_FragColor.a = 1.0;

}