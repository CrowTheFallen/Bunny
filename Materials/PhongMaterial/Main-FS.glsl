#version 460

in vec4 FragColor;

layout (location = 0) out vec4 Color;

void main()
{
	Color = vec4(FragColor.x, FragColor.y, FragColor.z,1.0);
}