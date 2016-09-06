///////////////////////////////////////////////////////////////////////////////
///  @file TextureAbstraite.h
///  @author  Fr�d�ric Plourde
///  @brief   D�clare la classe CTextureAbstraite qui encapsule une texture
///           openGL g�n�rique
///  @date    2007-12-13
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "TextureAbstraite.h"



///////////////////////////////////////////////////////////////////////////////
///  public constructor  CTextureAbstraite \n
///  Cconstruite une texture abstraite 
///  Elle est abstraite afin de permettre le polymorphisme des textures en 2D, ou cubemap, ou etc...
///
///  @param [in, out]  nomFichier char *    le nom de fichier de la texture
///  @param [in]       cible GLenum         la cible openGL associ�e � la texture
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
CTextureAbstraite::CTextureAbstraite(char* nomFichier, GLenum cible, bool mipmap, bool genTex) :
CIBLE_(cible), derniereUniteTexture_(GL_NONE), mipmap_(mipmap)
{
    // enregistrer le nom de fichier pour les classes filles
    if (nomFichier != NULL) {
        nomFichier_ = new char[strlen(nomFichier)];
        strcpy(nomFichier_, nomFichier);
    } else {
        nomFichier = NULL;
    }

    if (genTex) {
       // cr�er la texture
       glGenTextures(1, &nomTexture_);	
       glBindTexture(CIBLE_, nomTexture_);
    }
}



CTextureAbstraite::CTextureAbstraite(GLenum cible, bool mipmap, bool genTex) :
CIBLE_(cible), derniereUniteTexture_(GL_NONE), mipmap_(mipmap)
{
   nomFichier_ = new char[1];

   // enregistrer le nom de fichier pour les classes filles
   strcpy(nomFichier_, "");

   if (genTex) {
      // cr�er la texture
      glGenTextures(1, &nomTexture_);	
      glBindTexture(CIBLE_, nomTexture_);
   }
}



///////////////////////////////////////////////////////////////////////////////
///  public destructor  ~CTextureAbstraite \n
///  Destructeur par d�faut d'une texture g�n�rique. Lib�re la m�moire de texture
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
CTextureAbstraite::~CTextureAbstraite(void)
{
   // destruction du nom de texture associ� afin de le lib�rer pour d'autres textures
   const GLuint textureADetruire = nomTexture_;
   glDeleteTextures(1, &textureADetruire);

   if (nomFichier_ != NULL) {
      delete [] nomFichier_;
   }
}



///////////////////////////////////////////////////////////////////////////////
///  protected pure virtual  chargerTexture \n
///  Fonction virtuelle PURE servant d'interface au chargement de textures
///  dans les versions sp�cialis�es. Ne devrait JAMAIS �tre impl�ment�e.
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
void CTextureAbstraite::chargerTexture()
{
   // NE SERA JAMAIS IMPL�MENT�E � CE NIVEAU HI�RARCHIQUE !
   // devra �tre impl�ment�e dans les versions enfants pour sp�cialisation
}



///////////////////////////////////////////////////////////////////////////////
///  public  appliquer \n
///  Applique la texture au niveau d'openGL
///
///  @param [in]       flagParams uint    les diff�rents param�tres � sp�cifier. Voir le haut du fichier
///                                       textureAbstraite.h pour les diff�rents tag � ins�rer ici, s�par�s
///                                       par des ou " | ".
///  @param [in]       gl_texture_wrap_s GLenum       le wrap_s de la texture, si sp�fici� dans le flag
///  @param [in]       gl_texture_wrap_t GLenum       le wrap_t de la texture, si sp�fici� dans le flag
///  @param [in]       gl_texture_wrap_r GLenum       le wrap_r de la texture, si sp�fici� dans le flag
///  @param [in]       gl_texture_min_filter GLenum   le min_filter de la texture, si sp�fici� dans le flag
///  @param [in]       gl_texture_mag_filter GLenum   le mag_filter de la texture, si sp�fici� dans le flag
///  @param [in]       gl_texture_min_lod GLenum      le min_lod de la texture, si sp�fici� dans le flag
///  @param [in]       gl_texture_max_lod GLenum      le max_lod de la texture, si sp�fici� dans le flag
///  @param [in]       gl_texture_base_level GLenum   le base_level de la texture, si sp�fici� dans le flag
///  @param [in]       gl_texture_max_level GLenum    le max_level de la texture, si sp�fici� dans le flag
///  @param [in]       gl_texture_border_color GLenum le border_color de la texture, si sp�fici� dans le flag
///  @param [in]       gl_texture_priority GLenum     le priority de la texture, si sp�fici� dans le flag
///  @param [in]       mipmapping bool                indique si l'on veut activer le mipmapping ou non
///  @param [in]       uniteTexture GLenum [=0]       indique quelle unit� de texture sera associ�e. Si aucune -> passer GL_NONE
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
void CTextureAbstraite::appliquer(uint flagParams, GLenum gl_texture_wrap_s,       GLenum gl_texture_wrap_t,       GLenum gl_texture_wrap_r,
                                                   GLenum gl_texture_min_filter,   GLenum gl_texture_mag_filter, 
                                                   GLenum gl_texture_min_lod,      GLenum gl_texture_max_lod, 
                                                   GLenum gl_texture_base_level,   GLenum gl_texture_max_level, 
                                                   GLenum gl_texture_border_color, GLenum gl_texture_priority,
                                                   bool mipmapping,                GLenum uniteTexture)
{
   // activer l'unit� de texture d�sir�, s'il y a lieu
   if (uniteTexture != GL_NONE) {
      derniereUniteTexture_ = uniteTexture;
      glActiveTexture(uniteTexture);
   }

   // ensuite, lier la texture avec la cible de classe GL_TEXTURE_2D
   glBindTexture(CIBLE_, nomTexture_);
   glEnable(CIBLE_);

   // activer le mipmapping automatique si d�sir�
   if (mipmapping) {
      glTexParameteri(CIBLE_, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
   }

   // activer l'anisotropie
   GLfloat maxAnisotropy;
   glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
   glTexParameterf(CIBLE_, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

   // fixer les diff�rents param�tres choisis par l'appelant
   if (flagParams != 0) {
      if ((flagParams & WRAP_S) == WRAP_S) {
         glTexParameteri(CIBLE_, GL_TEXTURE_WRAP_S, gl_texture_wrap_s);
      }

      if ((flagParams & WRAP_T) == WRAP_T) {
         glTexParameteri(CIBLE_, GL_TEXTURE_WRAP_T, gl_texture_wrap_t);
      }

      if ((flagParams & WRAP_R) == WRAP_R) {
         glTexParameteri(CIBLE_, GL_TEXTURE_WRAP_R, gl_texture_wrap_r);
      }

      if ((flagParams & MIN_FILTER) == MIN_FILTER) {
         glTexParameteri(CIBLE_, GL_TEXTURE_MIN_FILTER, gl_texture_min_filter);
      }

      if ((flagParams & MAG_FILTER) == MAG_FILTER) {
         glTexParameteri(CIBLE_, GL_TEXTURE_MAG_FILTER, gl_texture_mag_filter);
      }

      if ((flagParams & MIN_LOD) == MIN_LOD) {
         glTexParameteri(CIBLE_, GL_TEXTURE_MIN_LOD, gl_texture_min_lod);
      }

      if ((flagParams & MAX_LOD) == MAX_LOD) {
         glTexParameteri(CIBLE_, GL_TEXTURE_MAX_LOD, gl_texture_max_lod);
      }

      if ((flagParams & BASE_LEVEL) == BASE_LEVEL) {
         glTexParameteri(CIBLE_, GL_TEXTURE_BASE_LEVEL, gl_texture_base_level);
      }

      if ((flagParams & MAX_LEVEL) == MAX_LEVEL) {
         glTexParameteri(CIBLE_, GL_TEXTURE_MAX_LEVEL, gl_texture_max_level);
      }

      if ((flagParams & BORDER_COLOR) == BORDER_COLOR) {
         glTexParameteri(CIBLE_, GL_TEXTURE_BORDER_COLOR, gl_texture_border_color);
      }

      if ((flagParams & PRIORITY) == PRIORITY) {
         glTexParameteri(CIBLE_, GL_TEXTURE_PRIORITY, gl_texture_priority);
      }
   }
}



///////////////////////////////////////////////////////////////////////////////
///  public  desactiver \n
///  D�sactive le texturage sur la cible en cours. Tr�s important de d�sactiver
///  le texturage entre les diff�rents objets openGL sp�cifi�s, car deux cibles
///  diff�rentes activ�es simultan�mant donnent lieu � des bugs bizarres en 
///  openGL.
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
void CTextureAbstraite::desactiver()
{
   // il est important de toujours d�sactiver la cible de texture
   // une fois celle-ci utilis�e (compil�e dans une liste), car
   // les prochains vertex � texturer auront peut-�tre une cible
   // diff�rente, et plusieurs probl�mes de texturage sont amen�s
   // par le conflit de deux cibles de texturages actives simult.
   glDisable(CIBLE_);
   if (derniereUniteTexture_ != GL_NONE) {
      glActiveTexture(derniereUniteTexture_);
      glDisable(CIBLE_);
   }
}




///////////////////////////////////////////////////////////////////////////////
///  protected  loadBMP \n
///  Fonction utilitaire servant � charger en m�moire un BMP
///
///  @param [in, out]  nomFichier char *    le nom de fichier de la texture
///  @param [in, out]  image Image *        une variable de type Image qui recueillera les donn�es
///
///  @return int <TODO: ins�rer une valeur de retour ici>
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
int CTextureAbstraite::loadBMP(char *nomFichier, Image *image) 
{
	FILE *file;
	unsigned long size;        // size of the image in bytes.
	unsigned long i;           // standard counter.
	unsigned short int planes; // number of planes in image (must be 1) 
	unsigned short int bpp;    // number of bits per pixel (must be 24)
	char temp;                 // temporary color storage for bgr-rgb conversion.

	// make sure the file is there.
	if ((file = fopen(nomFichier, "rb"))==NULL) {
		printf("File Not Found : %s\n",nomFichier);
		return 0;
	}

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// read the width
	if ((i = (unsigned long)fread(&image->tailleX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", nomFichier);
		return 0;
	}

	// read the height 
	if ((i = (unsigned long)fread(&image->tailleY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", nomFichier);
		return 0;
	}

	// calculate the size (assuming 24 bits or 3 bytes per pixel).
	size = image->tailleX * image->tailleY * 3;

	// read the planes
	if (((unsigned long)fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", nomFichier);
		return 0;
	}

	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", nomFichier, planes);
		return 0;
	}

	// read the bpp
	if ((i = (unsigned long)fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", nomFichier);
		return 0;
	}

	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", nomFichier, bpp);
		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	// read the data. 
	image->data = (GLubyte *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}

	if ((i = (unsigned long)fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", nomFichier);
		free(image->data);
		return 0;
	}

	for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
		temp = image->data[i];
		image->data[i] = image->data[i+2];
		image->data[i+2] = temp;
	}

	return 1;  // OK
}


void CTextureAbstraite::genTex()
{
   // cr�er la texture
   glGenTextures(1, &nomTexture_);	
   glBindTexture(CIBLE_, nomTexture_);
}