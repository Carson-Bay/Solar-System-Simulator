#version 330 core
out vec3 color;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 UVx;
in vec2 UVy;
in vec2 UVz;

uniform sampler2D texture1;
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;

float PI = 3.14159265;

void blendWeights(in vec2 uv, out float blendValue){
    float SHARPNESS = 0.8;
    blendValue = abs(cos(SHARPNESS*PI*(uv.x-0.5))) * abs(cos(SHARPNESS*PI*(uv.y-0.5)));
}

void main()
{
    float blendWeightx = 1.0;
    float blendWeighty = 1.0;
    float blendWeightz = 1.0;

    blendWeights(UVx, blendWeightx);
    blendWeights(UVy, blendWeighty);
    blendWeights(UVz, blendWeightz);

    vec3 blendweights = vec3(blendWeightx, blendWeighty, blendWeightz);
    blendweights = normalize(blendweights);

	vec3 objectColorx = texture(texture1, UVx).rgb * blendweights.x;  //PINK vec3(0.88, 0.46 ,0.61)
    vec3 objectColory = texture(texture1, UVy).rgb * blendweights.y;
    vec3 objectColorz = texture(texture1, UVz).rgb * blendweights.z;
    
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    float diffuseStrength = 0.5;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseStrength * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + specular + diffuse) * (objectColorx + objectColory + objectColorz); //
    color = result;
} 