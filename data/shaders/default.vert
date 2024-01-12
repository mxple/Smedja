#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection; 

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

void main() {
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
	FragPos = vec3(uModel * vec4(aPos, 1.0));
	TexCoord = aTex;
	Normal = mat3(transpose(inverse(uModel))) * aNormal;
}
