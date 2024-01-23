#version 330 core

out vec4 TintColor;
out vec2 TexCoord;

struct QuadData {
	vec3 position;
	vec2 size;
	float rotation;
	vec4 tintCol;
	vec2 texCoord1;
	vec2 texCoord2;
}

layout(std430, binding = 0) readonly buffer QuadBuffer {
	QuadDana quads[];
};

const vec2 positions[6] = vec2[] (
	vec2(0, 1), vec2(1, 1), vec2(0, 0),
	vec2(1, 1), vec2(1, 0), vec2(0, 0)
);

void main() {
	uint index = gl_VertexID / 6;
	uint vertex = gl_VertexID % 6;
	QuadData quad = QuadBuffer.quads[index];

	float rotRad = radians(quad.rotation);
	mat2 rotMat = mat2(
		cos(rotRad), sin(rotRad),
		-sin(rotRad), cos(rotRad)
	);

	mat2 scaleMat = mat2(
		quad.size.x, 0,
		0, quad.size.y
	);

	gl_Position = vec4(quad.position.xy + (rotMat * scaleMat * positions[vertex]), quad.position.z, 1.0);
	TintColor = quad.tintCol;
	TexCoord = mix(quad.texCoord1, quad.texCoord2, positions[vertex]);
}
