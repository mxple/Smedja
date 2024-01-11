#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection; 

out vec2 TexCoord;

void main() {
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
	TexCoord = aTex;
}
