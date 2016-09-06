#version 430 core
struct Light
{
        vec3 Ambient; 
        vec3 Diffuse;
        vec3 Specular;
        vec4 Position;  // Si .w = 1.0 -> Direction de lumiere directionelle.
        vec3 SpotDir;
        float SpotExp;
        float SpotCutoff;
        vec3 Attenuation; //Constante, Lineraire, Quadratique
};

struct Mat
{
        vec4 Ambient; 
        vec4 Diffuse;
        vec4 Specular;
        vec4 Exponent;
        float Shininess;
};

uniform sampler2D colorMap;

in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 color;

void main (void) 
{
    // Compléter afin d'ajouter la contribution de la texture:
    vec4 out_color;
    out_color = fragColor;
    
    //Contribution de la texture:
    // ...
    
    color = clamp(out_color, 0.0, 1.0);
    
    
    
   
}