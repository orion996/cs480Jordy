#version 330 core

smooth in vec3 color;
out vec4 FragColor;
  
//uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
//std::cout<<"meow"<< std::endl;
//lightingShader.setVec3("viewPos", camera.Position);
//std::cout<<"meow2"<< std::endl;
//in vec3 Normal;
//uniform vec3 lightPos;  
//in vec3 FragPos;
//lightingShader.setVec3("lightPos", lightPos);

//vec3 norm = normalize(Normal);
//vec3 lightDir = normalize(lightPos - FragPos);  


//float diff = max(dot(norm, lightDir), 0.0);
//vec3 diffuse = diff * lightColor;

void main()
{
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightPos - FragPos);  
    //float diff = max(dot(norm, lightDir), 0.0);
   // vec3 diffuse = diff * lightColor;

/*float specularStrength = 0.5;
vec3 viewDir = normalize(viewPos - FragPos);
vec3 reflectDir = reflect(-lightDir, norm);  
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = specularStrength * spec * lightColor; 

*/
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 result = ambient * objectColor;
    FragColor = vec4(result.rgb, 1.0);
}

