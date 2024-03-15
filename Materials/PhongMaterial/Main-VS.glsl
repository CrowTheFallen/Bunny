#version 460


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
uniform vec3 PosLum;
uniform vec3 posCam ;
// Output to fragment shader
out vec4 FragColor; // Final color of the fragment
 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
    };


layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;


// Output to fragment shader




void main()
{
    //a partir de posCam, il est maintenant possible de calculer V, la direction de la caméra

    vec3 V = normalize(posCam - Position);
    //specular
    
    


    //Direction de la lumière
    vec3 LightDir = normalize(PosLum - Position);

    vec3 R = reflect(-LightDir, Normal);


    float specularDot = max(dot(V, R), 0.0);
    float Is = specularDot * pow(specularDot, 32.0);
    //Couleur de la lumière
    vec3 lightColor = vec3(1, 0.4, 0.4);

    //Couleur ambiante 10% de la couleur de la lumière
    vec3 Ambient = 0.1 * lightColor;

    //Diffusion de la lumière
    float Diffuse = dot(Normal, LightDir) + Is;
    
    //Couleur finale
    vec3 res = Ambient + (lightColor * Diffuse);

    FragColor = vec4(res, 1);
    gl_Position = Proj * View * Model * vec4(Position, 1.0);

}