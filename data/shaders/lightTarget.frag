#version 330 core
in vec2 TexCoord;
in vec3 FragPos;

uniform sampler2D uTexture1;
uniform vec3 uLightColor;
uniform vec3 uObjectColor;
uniform vec3 uLightPos;

out vec4 FragColor;

void main() {
    // calculate light direction
    vec3 lightDir = normalize(uLightPos - FragPos);


    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * uLightColor;

    // diffuse
    float diff = max(dot(normalize(lightDir), normalize(FragPos)), 0.0);
    vec3 diffuse = diff * uLightColor;

    FragColor = vec4(diffuse + ambient, 1.0) * texture(uTexture1, TexCoord);
} 
