#version 330 core

in vec3 aCol;
out vec4 Color;

void main()
{
	Color = vec4(aCol, 1.0);
}