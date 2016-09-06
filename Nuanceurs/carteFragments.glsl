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

in float fragFogCoord;
in vec2 fragTexCoord;
in vec4 frontFragColor;
in vec4 backFragColor;
in vec3 VertexPosition_cameraSpace;
in vec3 Normal_cameraSpace;

// Half vectors en espace tangent
in vec3 Light0HV;          
in vec3 Light1HV;          
in vec3 Light2HV;          

out vec4 color;

uniform int pointLightOn;
uniform int dirLightOn;
uniform int spotLightOn;
uniform int perlinOn;
uniform Light Lights[3];
uniform Mat frontMat;
uniform Mat backMat;
uniform sampler2D frontColorMap;  // Unité de texture pour le dessus
uniform sampler2D backColorMap;   // Unité de texture pour le dessous
uniform sampler2D normalMap;      // Unité de texture pour le bruit


// Calcule la spécularité d'une source lumineuse
vec4 lightSpec(in int i, in vec3 normal, in vec3 halfVector, in float shininess)
{
    // À compléter
    // ...
    return vec4(0.0);
}

void main (void) 
{   
    // Couleur du fragment
    vec4 trueColor;
    vec4 frontColor;  
    vec4 backColor;
    vec3 normal;            // Vecteur normal en espace tangent
    vec4 matSpecular;       // Couleur speculaire du matériau
    float matShininess;     // Shininess du matériau
    vec3 noise;
    
    // Propriétés de la surface
    if(gl_FrontFacing)
    {	
        frontColor = frontFragColor;
        // Sampling de la texture
        // ...
        
        // Propriétés de la surface
        matSpecular  = frontMat.Specular;
        matShininess = frontMat.Shininess;

        // Échantillonnage du bruit de perlin
        // noise = ...

        // Perturbation de la normale
        /*
        if (perlinOn == 1) {
            // normal = ...
        } else {
            // normal = ...
        }
        */
        normal = vec3(0.0, 0.0, 1.0);
        trueColor = frontColor;
    }
    else
    {
        backColor = backFragColor;
        // Sampling de la texture
        // ...

        // Propriétés de la surface
        matSpecular  = backMat.Specular;
        matShininess = backMat.Shininess;
        // Normale inversée
        normal = vec3(0.0, 0.0, -1.0);
        trueColor = backColor;
    }

    // Calcul du facteur spéculaire selon la lumière (allumée ou non)
    vec4 specular = vec4(0.0, 0.0, 0.0, 1.0);

    // À dé-commenter
    /*
    if (pointLightOn == 1) {
        specular +=  lightSpec(0, normal, Light0HV, 400.0);
    }
    if (dirLightOn == 1) {
        specular +=  lightSpec(2, normal, Light2HV, 100.0);
    }
    if (spotLightOn == 1) {
        specular +=  lightSpec(1, normal, Light1HV, 400.0);
    }
    */
    
    // Ajout de la contribution spéculaire au fragement
    trueColor += specular * matSpecular;
    color = clamp(trueColor, 0.0, 1.0);
}