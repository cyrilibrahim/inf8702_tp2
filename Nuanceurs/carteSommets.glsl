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


uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 MV_N;
uniform mat4 M;
uniform mat4 V;
uniform float time;
uniform int animOn;
uniform int pointLightOn;
uniform int dirLightOn;
uniform int spotLightOn;
uniform Light Lights[3];
uniform Mat frontMat;
uniform Mat backMat;
uniform vec3 Tangent; 

layout(location = 0) in vec2 vt;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec3 vp;


out float fragFogCoord;
out vec2 fragTexCoord;
out vec4 frontFragColor;
out vec4 backFragColor;
out vec3 VertexPosition_cameraSpace;
out vec3 Normal_cameraSpace;
out mat3 tsMatrix;
out vec3 Light0HV;   // HalfVector de la Lumière 0 en espace Tangent
out vec3 Light1HV;   // HalfVector de la Lumière 1 en espace Tangent
out vec3 Light2HV;   // HalfVector de la Lumière 2 en espace Tangent

// Accumulateurs pour les facteurs d'éclairage
vec4 Ambient;
vec4 Diffuse;

const float PI = 3.1415926535897932385;  // Pi
const float PI_INV = 1.0 / PI;        // Pi inversé

// Calcul pour une lumière ponctuelle
void pointLight(in int i, in vec3 normal, in vec3 eye, in vec3 csPosition3)
{
   // À compléter, inspirez vous du gazon!
}


// Calcul pour une lumière "spot"
void spotLight(in int i, in vec3 normal, in vec3 eye, in vec3 csPosition3)
{
    // À compléter, inspirez vous du gazon!
}


// Calcul pour une lumière directionnelle
void directionalLight(in int i, in vec3 normal)
{
   // À compléter, inspirez vous du gazon!
}

// éclairage pour la surface du dessus
void frontLighting(in vec3 normal, in vec3 csPosition)
{
   vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
   const vec3 eye = normalize(-csPosition);

   // Clear the light intensity accumulators
   Ambient  = vec4 (0.0, 0.0, 0.0, 1.0);
   Diffuse  = vec4 (0.0, 0.0, 0.0, 1.0);

   // Calcul des 3 lumières
   // if (pointLightOn == 1) {
   //    pointLight(0, normal, eye, csPosition);
   // }
   // 
   // if (dirLightOn == 1) {
   //      directionalLight(2, normal);
   // }
   // 
   // if (spotLightOn == 1) {
   //    spotLight(1, normal, eye, csPosition);
   // }

   color = Ambient  * frontMat.Ambient + Diffuse  * frontMat.Diffuse;
   color = clamp( color, 0.0, 1.0 );
   frontFragColor = color;
}


// elairage pour la surface du dessous
void backLighting(in vec3 invNormal, in vec3 csPosition)
{
   vec4 color;
   const vec3 eye = normalize(-csPosition);

   // Clear the light intensity accumulators
   Ambient  = vec4 (0.0);
   Diffuse  = vec4 (0.0);

   // Calcul des 3 lumières
   // if (pointLightOn == 1) {
   //   pointLight(0, invNormal, eye, csPosition);
   // }
   //
   // if (dirLightOn == 1) {
   //   directionalLight(2, invNormal);
   // }
   //
   // if (spotLightOn == 1) {
   //    spotLight(1, invNormal, eye, csPosition);
   // }

   color = Ambient  * backMat.Ambient + Diffuse * backMat.Diffuse;
   color = clamp( color, 0.0, 1.0 );
   backFragColor = color;
}

// Retourne la matrice d'une rotation de theta radians autour de Y
mat3 rotMatX(float theta)
{
   return mat3(1.0, 0.0,        0.0,
      0.0, cos(theta), -sin(theta),
      0.0, sin(theta), cos(theta));
}


// Retourne la matrice d'une rotation de theta radians autour de Y
mat3 rotMatY(float theta)
{
   return mat3(cos(theta), 0.0, -sin(theta),
      0.0,        1.0, 0.0,
      sin(theta), 0.0, cos(theta));
}

// Retourne la matrice d'une rotation de theta radians autour de Y
mat3 rotMatZ(float theta)
{
   return mat3(cos(theta),  sin(theta), 0.0,
      -sin(theta), cos(theta), 0.0,
      0.0,         0.0,        1.0);
}

// Animation de flexion de la carte (displacement mapping)
// Cette fonction transforme les variables en entrée
void animation(inout vec4 position, inout vec3 normal, inout vec3 tangent)
{ 
	float amplitude; // Amplitude selon le temps et l'espace (animation) 
	float deltaPos;    // Variation de la hauteur du vertex
	mat3 rotMat;     // Matrice de tranformation pour la normale et tangente
	float theta;	 // Angle pour calculer la normale et la tangente
	
	amplitude = 2.0 * sin(time);
	// Déformation selon l'amplitude (time)
    if(amplitude < 0.0) {
        // Déformation sur l'axe des X selon la position X
		// TODO: 
		// Remplacer le commentaire ci-bas par la valeur de position necessaire
        deltaPos = amplitude * sin(/*position X * */ PI);
		theta = 0.5 * (vt.x - 0.5) * PI * sin(-amplitude);
		 // TODO:
		 //rotMat= ...
    } else {
        // Déformation sur l'axe des Y, selon la position Y
		// TODO: 
		// Remplacer le commentaire ci-bas par la valeur de position necessaire
        deltaPos = amplitude * sin(/*position Y * */ PI);
		float theta = 0.5 * (vt.y - 0.5) * PI * sin(amplitude);
		 // TODO:
		//rotMat = ...
    }
    // TODO:
    // Obtenir le déplacement du sommets en cours
    // position = ..

    // TODO:
    // Trouver les nouvelles normale + tangente après déplacement du sommet
    // normal = ...
    // tangent = ...
}

// Transformation des coordonnées d'espace tangent
void tsTransform(in vec3 csNormal, vec3 csTangent, vec3 csPosition)
{
    // Complétez cette fonction.
    // Vous trouverez ci-bas un genre de pseudo-code commenté 
    // qui vous aidera à structurer votre solution.

    // Calcul de la binormale
    // vec3 ecBinormal = ...

    // Construction de la matrice de transformation pour passer en espace tangent
    // mat3 tsMatrix = mat3(...);

    // Construction et calcul des vecteurs pertinants
    // Nous sommes en coordonnées de visualisation
    // vec3 EyeDir    = ... 
    // Light0HV  = ... en fonction de EyeDir et ...
    // Light1HV  = ... 
    // Light2HV  = ... en fonction de EyeDir et ...

    // Transformation dans l'espace tangent (on applique la matrice tsMatrix)
    // Light0HV  = ...
    // Light1HV  = ...
    // Light2HV  = ...
   
}

float ffog(in float distance_cameraSpace)
{
   return(abs(distance_cameraSpace));
}

void main () {

   // Variables qui seront transformées par l'animation
   vec4 position = vec4(vp,1.0);
   vec3 normal = vn;
   vec3 tangent = Tangent;
   vec3 Tangent_cameraSpace; 
  
   // Pasage des coordonées des textures
   // fragTexCoord = ...
   
   // Transformation du vertex selon le temps
   // if (animOn == 1) {
   //   animate(position, normal, tangent);
   // }
   
    //On passe au référenciel de caméra (ou eye-coordinate)
    VertexPosition_cameraSpace = ( V * M * position).xyz;
    Normal_cameraSpace = normalize(MV_N * normal);
    Tangent_cameraSpace  = normalize(MV_N * tangent); 

    // Transformation du vertex dans l'espace de clipping/écran
    gl_Position = MVP * position;

    // Calcul de la lumière ambiente et diffuse
    frontLighting(Normal_cameraSpace, VertexPosition_cameraSpace); 
    backLighting(-Normal_cameraSpace, VertexPosition_cameraSpace);
    
    // Transformation des coordonées en espace tangent
    tsTransform(Normal_cameraSpace, Tangent_cameraSpace, VertexPosition_cameraSpace);

}