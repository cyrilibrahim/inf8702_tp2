///////////////////////////////////////////////////////////////////////////////
///  @file Var.h
///  @author  Fr�d�ric Plourde 
///  @author  F�lix Gingras Harvey
///  @brief   D�clare les VARIABLES GLOBALES du programme
///  @date    2007 - 2016
///  @version 2.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Singleton.h"
#include <vector>
#include "Lumiere.h"
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/matrix_inverse.hpp>
#include <gtx/transform.hpp>
#include <gtx/matrix_cross_product.hpp>


///////////////////////////////////////////////
// Structure de donn�es globales             //
///////////////////////////////////////////////

struct Image {
   bool valide;
   int tailleX;
   int tailleY;
   GLubyte *data;
};


///////////////////////////////////////////////////////////////////////////
/// @class CVar
/// @brief Les VARIABLES globales du programme.
///        C'est une classe singleton.
///
/// @author Fr�d�ric Plourde
/// @date 2007-12-11
///////////////////////////////////////////////////////////////////////////
class CVar : public Singleton<CVar>
{
   SINGLETON_DECLARATION_CLASSE(CVar);

public:
   /// indique si l'on veut afficher les axes
   static int axesOn;    

   /// indique si l'on veut activer le brouillard
   static int fogOn;

   /// indique si on d�sire activer l'animation du mod�le
   static int animModeleOn;

   /// indique si on d�sire activer la rotation automatique du mod�le
   static int rotAutoOn;

   /// indique si on d�sire activer la bump mapping de perlin
   static int perlinOn;


   /// Indique le filtre � utiliser pour le minFilter (utilis� comme index � CCst::mapFilters[])
   static int minFilter;
   /// Indique le filtre � utiliser pour le minFilter (utilis� comme index � CCst::mapFilters[])
   static int magFilter;


   /// le ID de la fen�tre graphique GLUT
   static int g_nWindowID; 

   /// Largeur et hauteur courantes de la fen�tre graphique (viewport)
   static int currentW, currentH;  

   /// indique si on est en mode Perspective (true) ou glOrtho (false) 
   static bool isPerspective;

   /// indique si on fait tourner le/les objets
   static bool isRotating;

   /// indique si on fait tourner le/les objets
   static bool mouseControl;

   /// angle de rotation de la cam�ra en theta (coord. sph�riques)
   static double theta;

   /// angle de rotation de la cam�ra en phi (coord. sph�riques)
   static double phi;

   /// angle de rotation de la cam�ra en rho (coord. sph�riques)
   static double rho;    

   /// la position de la camera en X
   static float x;

   /// la position de la camera en Y
   static float y;

   /// la position de la camera en Z
   static float z;	


   /// angle courant de rotation en X du mod�le
   static float angleRotX;   

   /// angle courant de rotation en Y du mod�le
   static float angleRotY;

   /// angle courant de rotation en Z du mod�le
   static float angleRotZ;


   /// indique si la souris fut boug�e d�j�
   static bool premierMouvement;

   /// la derni�re valeur en X de position lue de la souris
   static double dernierX;      

   /// la derniere valeur en Y de position lus de la souris
   static double dernierY;


   /// d�claration de la liste d'affichage du mod�le  
   static GLuint listeAffModele;  


   /// la texture de perlin
   static GLuint perlinTex;


   /// temps
   static double temps;

   /// Matrice vue courante
   static glm::mat4 vue;

   /// Matrice projection courante
   static glm::mat4 projection;


   // la liste des lumieres openGL de la sc�ne
   static std::vector<CLumiere*> lumieres;

   /// Lumiere ponctuelle allum�e?
   static bool pointLightOn;
   
   /// Lumiere directionnelle allum�e?
   static bool dirLightOn;

   /// Lumi�re spot allum�e?
   static bool spotLightOn;

   static bool showDebugInfo;

};
