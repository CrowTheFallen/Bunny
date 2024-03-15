#version 460

layout (location = 0) out vec4 Color;

in vec3 NormalColor;
void main()
{
	Color = vec4(NormalColor.x,NormalColor.y,NormalColor.z,1.0);
}