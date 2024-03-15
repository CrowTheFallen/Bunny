#version 460
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
uniform float Sin;

 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
    };

out vec3 NormalColor;

layout (location = 0) in vec3 Position;

layout (location = 2) in vec3 Normal;

void main()
{
    
	gl_Position = Proj * View * Model * vec4(Position + ( Normal * Sin) ,1.0);
 	NormalColor = Normal;
 	

}