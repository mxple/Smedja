#version 430 core

in vec2 TexCoord;
in vec4 TintColor;

uniform sampler2D uTexture;

out vec4 FragColor;

void main() {
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    FragColor = texture(uTexture, TexCoord) * TintColor;
} 
