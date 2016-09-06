///////////////////////////////////////////////////////////////////////////////
///  @file SurfaceBSplinaire.h
///  @author  Fr�d�ric Plourde 
///  @brief   D�clare la classe CSurfaceBSplinaire qui encapsule une surface
///           bsplinaire compl�tement param�trable.
///  @date    2007-12-13
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <math.h>
#include <vector>
#include "Cst.h"


///////////////////////////////////////////////////////////////////////////////
///  @class CSurfaceBSplinaire
///  @brief Classe encapsulant une surface Bsplinaire
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
class CSurfaceBSplinaire
{
public:
   /// constructeur sp�cifique
   CSurfaceBSplinaire(uint numPts_U, uint numPts_V, const Point* Points, uint num_knots_U, uint num_knots_V, const float* knots_U, const float* knots_V, uint NDD = 20, uint degree_U = 3, uint degree_V = 3, uint order_U = 4, uint order_V = 4, float scale_U = 1.0, float scale_V = 1.0);
   /// destructeur de la surface bsplinaire
   ~CSurfaceBSplinaire(void);

   /// fonction r�cursive de calculs des coefficients de la B-spline associ�e 
   static float CoxDeBoor(float u,int i,int k,const float* noeuds);
   /// �value la B-spline aux coordonn�es (u,v)
   static Point calculer(float u,float v);
   /// effectue le calcul des "u" de la B-spline sur la rang�e v sp�cifi�e par "row"
   static Point calculerU(float t,int row);
   /// effectue le calcul des "v" de la B-spline sur toutes les colonnes
   static Point calculerV(float t,Point* pnts);
   ///Creer la grille et genere le VAO
   void setupVAO();
   /// affiche la surface bsplinaire
   void dessinerOpenGL();

   /// retourne la valeur minimale de la plage valide du param�tre en u
   static float MinU();
   /// retourne la valeur minimale de la plage valide du param�tre en v
   static float MinV();
   /// retourne la valeur maximale de la plage valide du param�tre en u
   static float MaxU();
   /// retourne la valeur maximale de la plage valide du param�tre en v
   static float MaxV();

   /// La liste des points de contr�le de la surface bsplinaire
   static Point* points_;

   /// Le vecteur nodal U
   static float* noeudsU_;
   /// Le vecteur nodal V
   static float* noeudsV_;

   /// La liste d'affichage openGL de la surface bsplinaire
   static GLuint surfaceList_;

   /// Le nom de la texture utilis�e pour afficher la surface
   static GLuint textureName_;

   /// le nombre de noeuds dans le vecteur nodal en direction U
   static unsigned int nbNoeudsU_;
   /// le nombre de noeuds dans le vecteur nodal en direction V
   static unsigned int nbNoeudsV_;
   /// le nombre de points de contr�le de la surface en direction U
   static unsigned int nbPtsCtrlU_;
   /// le nombre de points de contr�le de la surface en direction V
   static unsigned int nbPtsCtrlV_;
   /// le degr� du polyn�me d'approximation en direction U
   static unsigned int degreU_;
   /// le degr� du polyn�me d'approximation en direction V
   static unsigned int degreV_;
   /// l'ordre du polyn�me d'approximation en direction U
   static unsigned int ordreU_;
   /// l'ordre du polyn�me d'approximation en direction U
   static unsigned int ordreV_;

   /// la mise � l'�chelle openGL (glScalef) � appliquer � la surface selon u dans la liste d'affichage
   static float scaleU_;
   /// la mise � l'�chelle openGL (glScalef) � appliquer � la surface selon v dans la liste d'affichage
   static float scaleV_;

   /// le Niveau De D�tail de la surface (nombre de colonne et de rang�es en sommets)
   static unsigned int NDD_;

   std::vector<float>m_sommets;
   std::vector<unsigned int>m_indices;
   GLuint m_vao;
   GLuint m_vbo;
   GLuint m_ibo;
   GLint m_taille;

};