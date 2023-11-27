#version 330 core

layout (location = 0) in vec2 aPos;
out vec3 aCol;

uniform mat4 transformer;

void main()
{
	gl_Position = transformer * vec4(aPos, 0.0, 1.0);
	aCol = vec3(1.0, 0.0, 0.0);
}