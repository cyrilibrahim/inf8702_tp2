///////////////////////////////////////////////////////////////////////////////
///  @file TextureCubemap.cpp
///  @author  Frédéric Plourde 
///  @brief   Définit la classe CTextureCubemap qui implémente une texture
///           cubemap dans openGL
///  @date    2008-01-18
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////

#include "TextureCubemap.h"

CTextureCubemap::CTextureCubemap(char* nomFichier) :
CTextureAbstraite(nomFichier, GL_TEXTURE_CUBE_MAP)
{
   chargerTexture();
}



CTextureCubemap::~CTextureCubemap(void)
{
}


void CTextureCubemap::chargerTexture()
{
   // un pointeur utilisé pour la copie des sous-images.
   GLubyte *ptr;

   struct TsousImage {
      int tailleX;
      int tailleY;
      GLubyte *data;
   };

   TsousImage sousImage;

   // effectuer le chargement en mémoire du graphisme de la texture cubemap
   if (loadBMP(nomFichier_, &textureImage)) {

      // Parce que l'image cubemap chargée est de format CROSS, 
      // ca taille comporte 3 sous-images (faces) en X et 4 sous-images (faces) en Y
      // ajuster correctement la taille de la variable sousImage.
      sousImage.tailleX = textureImage.tailleX / 3;
      sousImage.tailleY = textureImage.tailleY / 4;
      sousImage.data = new GLubyte[sousImage.tailleX * sousImage.tailleY * 3];

      // copier le graphisme de la face "positive Y" (DEVANT) dans la sous-image
      ptr = sousImage.data;
      for (int j=0; j<sousImage.tailleY; j++) {
         for (int i=0; i<sousImage.tailleX; i++) {
            unsigned char *src = lirePixelRGB(sousImage.tailleX + i, 2 * sousImage.tailleY - (j + 1));
            *ptr++ = *src++;
            *ptr++ = *src++;
            *ptr++ = *src++;
         }
      }
      // associer à la cible courante le graphisme de la sous-image en cours.
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, sousImage.tailleX, sousImage.tailleY, 0, GL_RGB, GL_UNSIGNED_BYTE, sousImage.data);


      // copier le graphisme de la face "positive X" (À DROITE) dans la sous-image
      ptr = sousImage.data;
      for (int i=0; i<sousImage.tailleX; i++) {
         for (int j=0; j<sousImage.tailleY; j++) {
            unsigned char *src = lirePixelRGB(2 * sousImage.tailleX + i, sousImage.tailleY + j );
            *ptr++ = *src++;
            *ptr++ = *src++;
            *ptr++ = *src++;
         }
      }
      // associer à la cible courante le graphisme de la sous-image en cours.
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, sousImage.tailleX, sousImage.tailleY, 0, GL_RGB, GL_UNSIGNED_BYTE, sousImage.data);


      // copier le graphisme de la face "negative Z" (EN-DESSOUS) dans la sous-image
      ptr = sousImage.data;
      for (int j=0; j<sousImage.tailleY; j++) {
         for (int i=0; i<sousImage.tailleX; i++) {
            unsigned char *src = lirePixelRGB(2 * sousImage.tailleX - (i + 1), 2 * sousImage.tailleY + j);
            *ptr++ = *src++;
            *ptr++ = *src++;
            *ptr++ = *src++;
         }
      }
      glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, sousImage.tailleX, sousImage.tailleY, 0, GL_RGB, GL_UNSIGNED_BYTE, sousImage.data);


      // copier le graphisme de la face "negative X" (À GAUCHE) dans la sous-image
      ptr = sousImage.data;
      for (int i=0; i<sousImage.tailleX; i++) {
         for (int j=0; j<sousImage.tailleY; j++) {
            unsigned char *src = lirePixelRGB(sousImage.tailleX - (i + 1), 2 * sousImage.tailleY - (j + 1));
            *ptr++ = *src++;
            *ptr++ = *src++;
            *ptr++ = *src++;
         }
      }
      glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, sousImage.tailleX, sousImage.tailleY, 0, GL_RGB, GL_UNSIGNED_BYTE, sousImage.data);


      // copier le graphisme de la face "negative Y" (EN ARRIÈRE) dans la sous-image
      ptr = sousImage.data;
      for (int j=0; j<sousImage.tailleY; j++) {
         for (int i=0; i<sousImage.tailleX; i++) {
            unsigned char *src = lirePixelRGB(sousImage.tailleX + i, textureImage.tailleY - (j + 1));
            *ptr++ = *src++;
            *ptr++ = *src++;
            *ptr++ = *src++;
         }
      }
      glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, sousImage.tailleX, sousImage.tailleY, 0, GL_RGB, GL_UNSIGNED_BYTE, sousImage.data);


      // copier le graphisme de la face "positive Z" (AU-DESSUS) dans la sous-image
      ptr = sousImage.data;
      for (int j=0; j<sousImage.tailleY; j++) {
         for (int i=0; i<sousImage.tailleX; i++) {
            unsigned char *src = lirePixelRGB(sousImage.tailleX + i, sousImage.tailleY - (j + 1));
            *ptr++ = *src++;
            *ptr++ = *src++;
            *ptr++ = *src++;
         }
      }
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, sousImage.tailleX, sousImage.tailleY, 0, GL_RGB, GL_UNSIGNED_BYTE, sousImage.data);


      delete [] sousImage.data;

      // libérer l'espace mémoire maintenant que la texture est copiée dans la mémoire vidéo
      free( textureImage.data );
   }
}
