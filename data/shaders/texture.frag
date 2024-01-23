#version 330 core

in vec2 TexCoord;
in vec4 TintColor;

uniform sampler2D uTexture;

out vec4 FragColor;

void main() {
    FragColor = texture(uTexture, TexCoord) * TintColor;
} 
