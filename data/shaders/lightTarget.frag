#version 330 core
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;	// is normalized accounting for rotation and scale

uniform sampler2D uTexture1;
uniform vec3 uLightColor;
uniform vec3 uLightPos;
uniform vec3 uViewPos;

out vec4 FragColor;

void main() {
    vec3 lightDir = normalize(uLightPos - FragPos);
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * uLightColor;

    // diffuse
    float diff = max(dot(lightDir, Normal), 0.0);
    vec3 diffuse = diff * uLightColor;

    // specular
    float specStrength = 0.5;
    float spec = pow(max(dot(viewDir, reflectDir), 0), 256);
    vec3 specular = specStrength * spec * uLightColor;

    FragColor = vec4(diffuse + ambient + specular, 1.0) * texture(uTexture1, TexCoord);
} 
