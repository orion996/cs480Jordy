#version 440

in vec4 fragPosition;
in vec2 fragTexture;

out vec4 FragColor;

uniform vec3 lightPosition;
uniform sampler2D depthMap;

float near = 0.01;
float far = 100.0;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{             
	//float depthValue = texture(depthMap, fragTexture).r;
	//FragColor = vec4(vec3(LinearizeDepth(depthValue) / far), 1.0);

	//float lightDistance = length(fragPosition.xyz - lightPosition);
	//gl_FragDepth = lightDistance / far;

	//gl_FragDepth = LinearizeDepth(depthValue) / far;
}  