#version 330 core
in vec3 normal;
in vec2 texCoord;
in vec3 position;
out vec4 fragColor;

uniform vec3 viewPos;
uniform bool m_texture;

struct Light { // point light
    vec3 position;
    vec3 direction;
<<<<<<< HEAD
    vec2 cutoff;
    vec3 attenuation;
=======
>>>>>>> testing
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

struct Material {
    sampler2D TexDiffuse;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

void main() {
<<<<<<< HEAD
    vec3 texColor = texture(material.diffuse, texCoord).xyz;
  	vec3 ambient = texColor * light.ambient;
 
    float dist = length(light.position - position);
    vec3 distPoly = vec3(1.0, dist, dist*dist);

    float attenuation = 1.0 / dot(distPoly, light.attenuation); // 내적
    vec3 lightDir = (light.position - position) / dist;
    
    vec3 result = ambient;
    float theta = dot(lightDir, normalize(-light.direction));
    float intensity = clamp((theta - light.cutoff[1]) / (light.cutoff[0] - light.cutoff[1]), 0.0, 1.0);
    
    if (intensity > 0.0) {
        vec3 pixelNorm = normalize(normal);
        float diff = max(dot(pixelNorm, lightDir), 0.0);
        vec3 diffuse = diff * texColor * light.diffuse;

        vec3 specColor = texture(material.specular, texCoord).xyz;
        vec3 viewDir = normalize(viewPos - position);
        vec3 reflectDir = reflect(-lightDir, pixelNorm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = spec * specColor * light.specular;

        result += (diffuse + specular) * intensity;
    }

    result *= attenuation;
    fragColor = vec4(result, 1.0);
}
=======
  vec3 texColor = m_texture ? texture(material.TexDiffuse, texCoord).xyz : material.diffuse;
  vec3 ambient = m_texture ? texColor * light.ambient : light.ambient * material.ambient;

  vec3 lightDir = normalize(light.position - position);
  vec3 pixelNorm = normalize(normal);
  float diff = max(dot(pixelNorm, lightDir), 0.0);
  vec3 diffuse = diff * texColor * light.diffuse;

  vec3 viewDir = normalize(viewPos - position);
  vec3 reflectDir = reflect(-lightDir, pixelNorm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = spec * material.specular * light.specular;

  vec3 result = ambient + diffuse + specular;
  fragColor = vec4(result, 1.0);
}

>>>>>>> testing
