#version 430 core

out vec4 TintColor;
out vec2 TexCoord;

struct QuadData {
	vec4 position_rotation;
	vec4 size_origin;
	vec4 tintCol;
	vec2 texCoord1;
	vec2 texCoord2;
};

layout(std430, binding = 0) readonly buffer QuadBuffer {
	QuadData quads[];
};

const vec2 positions[4] = vec2[] (
	vec2(0, 1), vec2(1, 1), vec2(1, 0), vec2(0, 0)
);

void main() {
	uint index = gl_VertexID / 4;
	uint vertex = gl_VertexID % 4;
	QuadData quad = quads[index];

	float rotRad = radians(quad.position_rotation.w);
	mat2 rotMat = mat2(
		cos(rotRad), sin(rotRad),
		-sin(rotRad), cos(rotRad)
	);

	// deal with origin later
	mat2 scaleMat = mat2(
		quad.size_origin.x, 0,
		0, quad.size_origin.y
	);

	gl_Position = vec4(quad.position_rotation.xy + (rotMat * scaleMat * positions[vertex]), quad.position_rotation.z, 1.0);
	TintColor = quad.tintCol;
	TexCoord = mix(quad.texCoord1, quad.texCoord2, positions[vertex]);
}
