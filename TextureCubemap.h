///////////////////////////////////////////////////////////////////////////////
///  @file TextureCubemap.h
///  @author  Frédéric Plourde 
///  @brief   Déclare la classe CTextureCubemap qui implémente une texture
///           cubemap dans openGL
///  @date    2008-01-18
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "textureAbstraite.h"

// définition d'une macro utile pour la copie des sous-images
// les parenthèses autour de (y) et (x) sont hyper importantes
#define lirePixelRGB(x, y) (textureImage.data + ((textureImage.tailleX * (textureImage.tailleY - 1 - (y))) + (x)) * 3)


class CTextureCubemap :
   public CTextureAbstraite
{
public:
   /// constructeur d'une texture cubemap openGL (de type GL_TEXTURE_CUBE_MAP) à partir du nom de fichier de la texture
   CTextureCubemap(char* nomFichier);
   /// destructeur par défaut
   ~CTextureCubemap(void);

private:
   /// charge la texture en mémoire avec la cible GL_TEXTURE_CUBE_MAP
   virtual void chargerTexture();
   /// membre privé temporaire servant la conserver les texels lus du fichier
   Image textureImage;
};
