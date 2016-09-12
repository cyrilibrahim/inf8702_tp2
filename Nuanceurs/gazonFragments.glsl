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
uniform int pointLightOn;
uniform int spotLightOn;
uniform int dirLightOn;
uniform Light Lights[3]; // 0:ponctuelle  1:spot  2:directionnelle
uniform Mat Material;

in vec2 fragTexCoord;
in vec3 normal;
in vec3 light0Vect,light1Vect,light2Vect;
out vec4 color;

//Accumulateurs de contributions Ambiantes et Diffuses:
vec4 Ambient;
vec4 Diffuse;

// Calcul pour une lumi�re ponctuelle
void pointLight(in vec3 lightVect, in vec3 normal)
{
   float nDotVP;       // Produit scalaire entre VP et la normale
   float attenuation;  // facteur d'att�nuation calcul�
   float d;            // distance entre lumi�re et fragment
   vec3  VP;           // Vecteur lumi�re

   // Calculer vecteur lumi�re
   VP = lightVect;

   // Calculer distance � la lumi�re
   d = length(VP);

   // Normaliser VP
   VP = normalize(VP);

   // Calculer l'att�nuation due � la distance
   vec3 vAtt = Lights[0].Attenuation;
   attenuation = 1/(vAtt[0] + vAtt[1]*d + vAtt[2]*d*d);
   
   nDotVP = clamp(dot(normal,VP),0,1);

   // Calculer les contributions ambiantes et diffuses
   Ambient  += attenuation * vec4(Lights[0].Ambient,1);
   Diffuse  += attenuation * vec4(Lights[0].Diffuse,1) * nDotVP;
}


// Calcul pour une lumi�re directionnelle
void directionalLight(in vec3 lightVect, in vec3 normal)
{
   vec3  VP;             // Vecteur lumi�re
   float nDotVP;         // Produit scalaire entre VP et la normale

   VP = normalize(lightVect);

   nDotVP = clamp(dot(normal,VP),0,1);

   // Calculer les contributions ambiantes et diffuses
   Ambient  += vec4(Lights[2].Ambient,1);
   Diffuse  += vec4(Lights[2].Diffuse,1) * nDotVP;
}


// Calcul pour une lumi�re "spot"
void spotLight(in vec3 lightVect, in vec3 normal)
{
   float nDotVP;             // Produit scalaire entre VP et la normale
   float spotAttenuation;    // Facteur d'att�nuation du spot
   float attenuation;        // Facteur d'att�nuation du � la distance
   float angleEntreLumEtSpot;// Angle entre le rayon lumieux et le milieu du cone
   float d;                  // Distance � la lumi�re
   vec3  VP;                 // Vecteur lumi�re

   // Calculer le vecteur Lumi�re
   VP = lightVect;

   // Calculer la distance � al lumi�re
   d = length(VP);

   // Normaliser VP
   VP = normalize(VP);

   // Calculer l'att�nuation due � la distance
   vec3 vAtt = Lights[1].Attenuation;
   attenuation = 1/(vAtt[0] + vAtt[1]*d + vAtt[2]*d*d);

   // Le fragment est-il � l'int�rieur du c�ne de lumi�re ?
   vec3 spotDir = Lights[1].SpotDir;
   vec3 lightDir = -VP;
   angleEntreLumEtSpot = degrees(acos(dot(spotDir,lightDir)));

   if (angleEntreLumEtSpot > Lights[1].SpotCutoff)
   {
       spotAttenuation = 0.0; // en dehors... aucune contribution
   }
   else
   {
       spotAttenuation = pow(dot(spotDir,lightDir),Lights[1].SpotExp);

   }

   // Combine les att�nuation du spot et de la distance
   attenuation *= spotAttenuation;

   nDotVP = clamp(dot(VP,normal),0,1);

   // Calculer les contributions ambiantes et diffuses
   Ambient  += attenuation * vec4(Lights[1].Ambient,1) ;
   Diffuse  += attenuation * vec4(Lights[1].Diffuse,1) * nDotVP;
}

vec4 flight(in vec3 light0Vect, in vec3 light1Vect, in vec3 light2Vect, in vec3 normal)
{
    vec4 color;
    vec3 ecPosition3;

    // R�initialiser les accumulateurs
    Ambient  = vec4 (0.0);
    Diffuse  = vec4 (0.0);

    if (pointLightOn == 1) {
        pointLight(light0Vect, normal);
    }
    if (spotLightOn == 1) {
        spotLight(light1Vect, normal);
    }
    if (dirLightOn == 1) {
        directionalLight(light2Vect, normal);
    }
    
    //� d�-commenter!
    color = (Ambient * Material.Ambient + Diffuse  * Material.Diffuse);
    color = clamp( color, 0.0, 1.0 );
    
    return color;
}

void main (void) 
{
    // Compl�ter afin d'ajouter la contribution de la texture:
    vec4 out_color = flight(light0Vect, light1Vect, light2Vect, normal);
    
    //Contribution de la texture:
    out_color *= texture(colorMap, fragTexCoord);

    color = clamp(out_color, 0.0, 1.0);
}

