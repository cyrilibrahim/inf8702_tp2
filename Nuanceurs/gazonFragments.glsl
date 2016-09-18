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

// Calcul pour une lumière ponctuelle
void pointLight(in vec3 lightVect, in vec3 normal)
{
	float nDotVP;       // Produit scalaire entre VP et la normale
	float attenuation;  // facteur d'atténuation calculé
	float d;            // distance entre lumière et fragment
	vec3  VP;           // Vecteur lumière

	Light lum = Lights[0];

	// Calculer vecteur lumière
	VP = lightVect;

	// Calculer distance à la lumière
	d = length(VP);

	// Normaliser VP
	VP = normalize(VP);

	// Calculer l'atténuation due à la distance
	vec3 vAtt = lum.Attenuation;
	// Attenuation = constante + linéaire + quadratique
	attenuation = 1/(vAtt[0] + vAtt[1]*d + vAtt[2]*d*d);

	// la normale a été normalisée au niveau de chaque sommet
	// l'interpolation entre 2 sommmets reste raisonnablement normalisée
	nDotVP = max(dot(normal,VP),0);

	// Calculer les contributions ambiantes et diffuses
	Ambient  += vec4(attenuation * lum.Ambient, 1.0);
	Diffuse  += vec4(attenuation * lum.Diffuse * nDotVP, 1.0);
}


// Calcul pour une lumière directionnelle
void directionalLight(in vec3 lightVect, in vec3 normal)
{
	vec3  VP;             // Vecteur lumière
	float nDotVP;         // Produit scalaire entre VP et la normale
	Light lum = Lights[2];

	VP = normalize(lightVect);

	//Pas besoin de renormaliser
	nDotVP = max(dot(normal,VP),0);

	// Calculer les contributions ambiantes et diffuses
	Ambient  += vec4(lum.Ambient,1.0);
	Diffuse  += vec4(lum.Diffuse * nDotVP, 1.0);
}


// Calcul pour une lumière "spot"
void spotLight(in vec3 lightVect, in vec3 normal)
{
	float nDotVP;             // Produit scalaire entre VP et la normale
	float spotAttenuation;    // Facteur d'atténuation du spot
	float attenuation;        // Facteur d'atténuation du à la distance
	float angleEntreLumEtSpot;// Angle entre le rayon lumieux et le milieu du cone
	float d;                  // Distance à la lumière
	vec3  VP;                 // Vecteur lumière
	Light lum = Lights[1];

	// Calculer le vecteur Lumière
	VP = lightVect;

	// Calculer la distance à al lumière
	d = length(VP);

	// Normaliser VP
	VP = normalize(VP);

	// Calculer l'atténuation due à la distance
	vec3 vAtt = lum.Attenuation;
	attenuation = 1/(vAtt[0] + vAtt[1]*d + vAtt[2]*d*d);

	// Le fragment est-il à l'intérieur du cône de lumière ?
	vec3 spotDir = normalize(lum.SpotDir);
	vec3 lightDir = -VP;
	float dotSpotLight = dot(spotDir, lightDir);
	//acos en radians, SpotCutoff en degrés
	angleEntreLumEtSpot = degrees(acos(dotSpotLight));

	if (angleEntreLumEtSpot > lum.SpotCutoff)
	{
		spotAttenuation = 0.0; // en dehors... aucune contribution
	}
	else
	{
		dotSpotLight = abs(dotSpotLight);
		spotAttenuation = pow(dotSpotLight,lum.SpotExp);

	}

	// Combine les atténuation du spot et de la distance
	attenuation *= spotAttenuation;

	//Pas besoin de renormaliser les normales
	nDotVP = max(dot(VP,normal),0);

	// Calculer les contributions ambiantes et diffuses
	Ambient  += vec4(attenuation * lum.Ambient, 1.0);
	Diffuse  += vec4(attenuation * lum.Diffuse * nDotVP, 1.0);
}

vec4 flight(in vec3 light0Vect, in vec3 light1Vect, in vec3 light2Vect, in vec3 normal)
{
	vec4 color;
	vec3 ecPosition3;

	// Réinitialiser les accumulateurs
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

	// Ambiante + Diffuse
	color = (Ambient * Material.Ambient + Diffuse  * Material.Diffuse);
	color = clamp( color, 0.0, 1.0 );

	return color;
}

void main (void) 
{
	// Contribution de l'éclairage
	vec4 out_color = flight(light0Vect, light1Vect, light2Vect, normal);

	//Contribution de la texture:
	out_color *= texture(colorMap, fragTexCoord);

	color = clamp(out_color, 0.0, 1.0);
}

