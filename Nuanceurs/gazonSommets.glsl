#version 430 core
struct Light
{
	vec3 Ambient; 
	vec3 Diffuse;
	vec3 Specular;
	//Light position in camera space
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

layout(location = 0) in vec2 vt;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec3 vp;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 MV_N;
uniform mat4 M;
uniform mat4 V;
uniform Light Lights[3]; // 0:ponctuelle  1:spot  2:directionnelle

out vec2 fragTexCoord;
out vec3 normal;
out vec3 light0Vect,light1Vect,light2Vect;

void main (void)
{
	vec3 csPosition3;

	// Transformation de la position
	gl_Position = MVP * vec4(vp,1.0);
	vec4 csPosition = MV * vec4 (vp, 1.0);
	csPosition3 = (csPosition.xyz);

	//Vecteurs de la surface vers la lumière
	// source ponctuelle: position(lumière) - position(sommet)
	light0Vect = Lights[0].Position.xyz - csPosition3;
	light1Vect = Lights[1].Position.xyz - csPosition3;
	// source directionnelle: direction = Light.Position.xyz
	light2Vect = -Lights[2].Position.xyz;

	//Normale en référentiel caméra:
	normal = normalize(MV_N * vn);

	//Coordonée de texture:
	fragTexCoord = vt;
}
