///////////////////////////////////////////////////////////////////////////////
///  @file Texture2D.h
///  @author  Fr�d�ric Plourde 
///  @brief   D�clare la classe CTexture2D qui impl�mente une texture2D openGL
///  @date    2008-01-18
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "TextureAbstraite.h"

///////////////////////////////////////////////////////////////////////////////
///  CTexture2D
///  Cette classe encapsule une texture 2D openGL. (type GL_TEXTURE_2D)
///
///  Base class CTextureAbstraite <TODO: ins�rer la description de la classe de base ici>
///
///  @remarks La classe poss�de deux constructeurs. Un premier ne prenant qu'un nom de 
///           fichier, est utile pour charger des images 2D � partir du disque (BMP
///           uniquement !), et uu deuxi�me, prenant un vect3D* data, est utile pour 
///           cr�er une texture 2D openGL � partir de donn�es d�j� existantes en m�moire.
///           � noter cependant que cette version ne prend QUE des vect3D, i.e. une 
///           texture 2D en format GL_FLOAT. Pour d'autres supports de formats, 
///           veuillez ajouter les constructeurs appropri�s et le code associ�.
///
///  @author Fr�d�ric Plourde 
///  @date   2008-03-11   <TODO: ins�rer initiales ici> <TODO: ins�rer le texte ici> 
///
///////////////////////////////////////////////////////////////////////////////
class CTexture2D :
   public CTextureAbstraite
{
public:
   /// constructeur d'une texture 2D openGL (de type GL_TEXTURE_2D) � partir du nom de fichier de la texture
   CTexture2D(char* filename, bool mipmap = false);
   /// constructeur d'une texture 2D openGL � partir d'un poiteur sur des donn�es float
   CTexture2D(vect3D* data, int hauteur, int largeur, bool mipmap = false);
   /// destructeur par d�faut
   ~CTexture2D(void);

private:
   /// charge la texture en m�moire avec la cible GL_TEXTURE_2D
   virtual void chargerTexture(); // devrait toujours �tre priv�e
   /// membre priv� temporaire servant la conserver les texels lus du fichier
   Image TextureImage;
};
