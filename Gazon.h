///////////////////////////////////////////////////////////////////////////////
///  @file Gazon.h
///  @author  Fr�d�ric Plourde 
///  @brief   D�clare la classe CGazon qui encapsule une patch BSplinaire openGL
///           avec antialiasing
///  @date    2007-12-11
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Modele3DAbstrait.h"
#include "SurfaceBSplinaire.h"
#include "Cst.h"


class CGazon :
   public CModele3DAbstrait, CSurfaceBSplinaire
{
public:
   /// constructeur cr�ant une patch bsplinaire (gazon) avec texture sp�cifi�e unique (obligatoire)
   CGazon(char * nomFichierTexture, float largeurGazon = 1.0, float longueurGazon = 1.0);
   /// destructeur par d�faut
   ~CGazon(void);

   /// fonction � impl�menter pour d�finir la g�om�trie openGL du gazon (est statique, car est r�f�r�e par un pointeur de fonction)
   void dessiner();
   /// fonction � impl�menter pour d�finir un texturage personnalis�
   void appliquerTextures();

private:
};
