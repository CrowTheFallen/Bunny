#version 460



uniform vec4 Phong;
uniform vec3 diffuseAlbedo;
uniform vec3 specularColor;
uniform sampler2D tex;

in VTF {
    vec3 vL;
    vec3 vV;
    vec3 vN;
    vec3 v_Color;
    vec2 v_TextureCoords;
};


layout (location = 0) out vec4 Color;


void main()
{


    vec3 L = normalize(vL);
    vec3 V = normalize(vV);
    vec3 N = normalize(vN);
    vec4 textureColor = texture(tex, v_TextureCoords);
    vec4 diffuse = textureColor;


    float Id = max(0, dot(L, N));
    float Is = pow(max(0, dot(reflect(-L, N), V)), Phong.w);

    Color = Phong.x*diffuse + Phong.y*diffuse*Id + Phong.z*Is*vec4(1.0);


    Color.w = 1.0;

}
