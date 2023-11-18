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
    vec2 cutoff;
    vec3 attenuation;
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
  vec3 texColor = m_texture ? texture(material.TexDiffuse, texCoord).xyz : material.diffuse;
  vec3 ambient = m_texture ? texColor * light.ambient : light.ambient * material.ambient;

  vec3 lightDir = normalize(light.position - position);
  vec3 pixelNorm = normalize(normal);
  float diff = dot(pixelNorm, lightDir);
  vec3 diffuse = diff * texColor * light.diffuse;

  vec3 viewDir = normalize(viewPos - position);
  vec3 reflectDir = reflect(-lightDir, pixelNorm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = spec * material.specular * light.specular;

  vec3 result = ambient + diffuse + specular;
  fragColor = vec4(result, 1.0);
}
