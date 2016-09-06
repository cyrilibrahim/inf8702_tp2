///////////////////////////////////////////////////////////////////////////////
///  @file Cst.h
///  @author  Fr�d�ric Plourde 
///  @brief   D�clare les CONSTANTES GLOBALES du programme
///  @date    2007-12-11
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Singleton.h"
#include <GL/glew.h>

///////////////////////////////////////////////
// d�finitions de types globaux              //
///////////////////////////////////////////////
typedef unsigned int uint;

///////////////////////////////////////////////////////////////////////////////
///  colorRGB
///  Cette structure d�clare une couleur RGB (r,g,b) sur des float (0..1)
///
///
///  @author Fr�d�ric Plourde @date 2008-03-11
///////////////////////////////////////////////////////////////////////////////
struct colorRGB {
   float r;
   float g;
   float b;
} ;

///////////////////////////////////////////////////////////////////////////////
///  vect3D
///  Cette structure d�clare un vecteur 3D (x,y,z)
///
///  @remarks <TODO: ins�rer une remarque ici>
///
///  @author Fr�d�ric Plourde @date 2008-03-11
///////////////////////////////////////////////////////////////////////////////
struct vect3D {
   float x;
   float y;
   float z;
} ;



///////////////////////////////////////////////////////////////////////////////
///  Point
///  Structure encapsulant un point 3D dans l'espace
///
///
///  @author Fr�d�ric Plourde @date 2008-03-11
///////////////////////////////////////////////////////////////////////////////
struct Point {
	float x;
	float y;
	float z;
};

///////////////////////////////////////////////
// �num�rations globales                     //
///////////////////////////////////////////////

/// �num�ration des lumi�res de la sc�nes (� utiliser comme INDEX de lumieres[])
enum ENUM_LUM { LumPonctuelle, LumSpot, LumDirectionnelle };


///////////////////////////////////////////////
// d�claration des macros et defines globaux //
///////////////////////////////////////////////

#ifndef M_PI
#define M_PI 3.1415926535897932385
#endif

#define DEG2RAD(a) (a / 180.0f) * (M_PI);

#define PRODVECT(normale, vect1, vect2) \
	normale.x = (vect1.y*vect2.z) - (vect1.z*vect2.y); \
	normale.y = (vect1.z*vect2.x) - (vect1.x*vect2.z); \
	normale.z = (vect1.x*vect2.y) - (vect1.y*vect2.x)

#define NORMALIZE(normale) \
	{float norm = sqrt((normale.x*normale.x) + \
			          (normale.y*normale.y) + \
					  (normale.z*normale.z)); \
	normale.x = normale.x / norm;  \
	normale.y = normale.y / norm;  \
	normale.z = normale.z / norm;}


#define SUBVECT(result, lhs, rhs) \
	result.x = lhs.x - rhs.x; \
	result.y = lhs.y - rhs.y; \
	result.z = lhs.z - rhs.z;

#define MIN(a,b) a <= b ? a : b
#define MAX(a,b) a >= b ? a : b

#define ASSIGNVECT(res, V1) res.x = V1.x; res.y = V1.y; res.z = V1.z;
#define SUBVECT(res, V1, V2) res.x = V1.x - V2.x; res.y = V1.y - V2.y; res.z = V1.z - V2.z;
#define ADDVECT(res, V1, V2) res.x = V1.x + V2.x; res.y = V1.y + V2.y; res.z = V1.z + V2.z;
#define DIVVECT(V1, a) V1.x /= a; V1.y /= a; V1.z /= a;
#define CITYBLOCKNORM(V1) (V1.x*V1.x) + (V1.y*V1.y) + (V1.z*V1.z);




///////////////////////////////////////////////////////////////////////////
/// @class CCst
/// @brief Les CONSTANTES globales du programme.
///        C'est une classe singleton.
///
/// @author Fr�d�ric Plourde
/// @date 2007-12-11
///////////////////////////////////////////////////////////////////////////
class CCst : public Singleton<CCst>
{
   SINGLETON_DECLARATION_CLASSE(CCst);

public:

   /// sp�cificateur du mode de s�paration de la couleur sp�culaire
   static const GLfloat gl_separate_specular_color;

   /// la largeur initiale de la fen�tre GLUT
   static const int g_nWidth;
   /// la hauteur initiale de la fen�tre GLUT
   static const int g_nHeight;

   /// la fr�quence de rotation en X du mod�le
   static const float freqRotX;            
   /// la fr�quence de rotation en Y du mod�le
   static const float freqRotY;       
   /// la fr�quence de rotation en Z du mod�le
   static const float freqRotZ;   

   /// le framerate cible de l'application graphique.          
   static const float frameRate;

   /// le nombre de lumi�res openGL de la sc�ne
   static const int nbLumieresOpenGL;

   /// la largeur du mod�le 3D
   static const float largeurModele;
   /// la hauteur du mod�le 3D
   static const float hauteurModele; 
   /// le nombre de colonnes (quads) dans la grille de quads
   static const int   nbColonnes;
   /// le nombre de rang�es (quads) dans la grille de quads
   static const int   nbRangees;
   /// la grandeur du skybox
   static const float grandeurSkybox;
   /// la largeur du gazon (patch Bspline)
   static const float largeurGazon;
   /// la longueur du gazon (patch Bspline)
   static const float longueurGazon;
   /// la hauteur du gazon (patch Bspline)
   static const float hauteurGazon;

   /// le facteur multiplicatif des axes unitaires dessin�s dans la sc�ne
   static const float axeScaleFact;

   /// la couleur du FOG dans l'application
   static const GLfloat fogColor[];

   /// l'amplitude maximale du displacement mapping selon X
   static const float dispAmplitude1;
   /// l'amplitude maximale du displacement mapping selon Z
   static const float dispAmplitude2;
   /// la fr�quence du disp. map. selon X (en cycles/sec) 0.0 = off
   static const float dispFrequency1;
   /// la fr�quence du disp. map. selon X (en cycles/sec) 0.0 = off
   static const float dispFrequency2;
   /// la largeur du bruit de Perlin pour le bumpmapping de la carte
   static const int noiseWidth;
   /// la hauteur du bruit de Perlin pour le bumpmapping de la carte
   static const int noiseHeight;

   /// la constante "0" pour l'unit� de texture 0
   static const int texUnit_0;
   /// la constante "1" pour l'unit� de texture 1
   static const int texUnit_1;
   /// la constante "2" pour l'unit� de texture 2
   static const int texUnit_2;
   /// la constante "3" pour l'unit� de texture 3
   static const int texUnit_3;
   /// la constante "4" pour l'unit� de texture 4
   static const int texUnit_4;

   /// les diff�rents param�tres pour le filtrage mipmaping
   static const GLuint mapFilters[6];

   /// le vecteur des GLenum d'unit�s de textures
   static const GLenum unitesTextures[32];

   /// l'index unique de l'attribut de tangente
   static const GLuint indexTangente;

   /// les points de contr�le de la patch BSpline du gazon
   static const Point Points[32]; 

   /// le vecteur nodal en U de la patch BSpline (gazon)
   static const float VNodalU[12];

   /// le vecteur nodal en V de la patch BSpline (gazon)
   static const float VNodalV[8];
};
