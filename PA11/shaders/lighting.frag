#version 440
#define MAX_LIGHTS 10

in vec4 f_position;
in vec3 fN;
in vec3 fE;
in vec3 fP;
in vec2 uv;

out vec4 frag_color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform int numLights;
uniform struct Light {
    mat4 lightMatrix;
    vec4 ambientProduct, diffuseProduct, specularProduct;
    vec4 lightPosition;
    vec3 lightDirection;
    float lightAngle;
    float shininess;
    float attenuationProduct;
    bool directional;
    bool shadowed;    
} lights[MAX_LIGHTS];

uniform vec3 cameraPosition;

uniform sampler2D gSampler;

uniform int numShadows;
uniform sampler2D shadowMap[MAX_LIGHTS];

vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

float CalculateShadow(vec4 posLightSpace, float bias, int shadowIndex)
{
    // manual perspective divide (unnecessary if orthographic projection)
    vec3 projCoords = posLightSpace.xyz / posLightSpace.w;

    // shift coordinates from [-1, 1] to [0, 1]
    projCoords = projCoords * 0.5 + 0.5;

    // get closest depth value from light's perspective
    float closestDepth = texture(shadowMap[shadowIndex], projCoords.xy).r;

    // get depth of current fragment
    float currentDepth = projCoords.z;

    float shadow = 0.0;

    if (projCoords.z > 1.0)
    {
        return shadow;
    }

    // if in shadow set to 0
    //shadow = (currentDepth - bias) > closestDepth ? 1.0 : 0.0;

    for (int i = 0; i < 4; i++)
    {
        if (texture(shadowMap[shadowIndex], projCoords.xy + poissonDisk[i]/500.0).z < projCoords.z)
        {
            shadow += 0.01;
        }
    }

    vec2 texelSize = 1.0 / textureSize(shadowMap[shadowIndex], 0);
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            float pcfDepth = texture(shadowMap[shadowIndex], projCoords.xy + vec2(i, j) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    
    return shadow;
}

void main()
{
    vec3 N = normalize(fN);
    vec3 E = normalize(cameraPosition);

    vec3 linearColor = vec3(0);

    for (int i = 0; i < numLights; i++)
    {
        vec3 fL = lights[i].lightPosition.xyz;
        if(lights[i].lightPosition.w != 0.0)
        {
            fL = lights[i].lightPosition.xyz - fP;
        }

        vec3 L = normalize(fL);
        vec3 H = normalize(L + E);

        vec4 ambient = lights[i].ambientProduct;

        float Kd = max(dot(L,N), 0.0);
        vec4 diffuse = Kd * lights[i].diffuseProduct;

        float Ks = pow(max(dot(N, H), 0.0), lights[i].shininess);
        vec4 specular = Ks * lights[i].specularProduct;
        if(dot(L,N) < 0.0){
            specular = vec4(0.0, 0.0, 0.0, 1.0);
        }

        //calculate attenuation
        float distanceToLight = length(lights[i].lightPosition.xyz - fP);
        float attenuation = 1.0 / (1.0 + lights[i].attenuationProduct * pow(distanceToLight, 2));

        if (!lights[i].directional)
        {
            //if object is outside the cone of influence, set attenuation to 
            //zero
            vec3 direction = normalize(lights[i].lightDirection);
            float lightToSurfaceAngle = degrees(acos(dot(-L,direction)));
            if (lightToSurfaceAngle > lights[i].lightAngle)
            {
                attenuation = 0.0;
            }
        }
        else
        {
            attenuation = 1.0;
        }

        //calculate shadows if this light casts shadows
        vec4 lightSpacePos;
        float shadow;
        if (lights[i].shadowed)
        {
            if (dot(N, L) < 0)
            {
                shadow = 0.0;
            }
            else
            {
                // get position of fragment in light space
                lightSpacePos = (lights[i].lightMatrix * modelMatrix) * f_position;

                // set the bias
                float bias = 0.001 * tan(acos(dot(N,L)));
                bias = clamp(bias, 0.0, 0.005);

                shadow = CalculateShadow(lightSpacePos, bias, i);
            }
        }
        else
        {
            shadow = 0.0;
        }

        linearColor += (ambient + (1.0 - shadow) * (attenuation * (diffuse + specular))).xyz;
    }

    vec3 gamma = vec3(1.0/2.2);

    frag_color = vec4(pow(linearColor, gamma), 1.0) * texture2D(gSampler, uv.st);
    frag_color.a = 1.0;

}