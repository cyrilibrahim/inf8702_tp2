///////////////////////////////////////////////////////////////////////////////
///  @file TextureAbstraite.h
///  @author  Fr�d�ric Plourde
///  @brief   D�clare la classe abstraite CTextureAbstraite qui encapsule 
///           l'interface g�n�rique d'une texture openGL
///  @date    2008-01-17
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include "Var.h"
#include "Cst.h"

// d�finition plus commode (et abr�g�e) du type "unsigned int" (16-bit integer - word)
typedef unsigned int uint;

// d�finition des diff�rents bits utilis�s pour le choix des param�tres de texturage
const uint WRAP_S       = 0x0001;
const uint WRAP_T       = 0x0002;
const uint WRAP_R       = 0x0004;
const uint MIN_FILTER   = 0x0008;
const uint MAG_FILTER   = 0x0010;
const uint MIN_LOD      = 0x0020;
const uint MAX_LOD      = 0x0040;
const uint BASE_LEVEL   = 0x0080;
const uint MAX_LEVEL    = 0x0100;
const uint BORDER_COLOR = 0x0200;
const uint PRIORITY     = 0x0400;

/// d�finition des �num�rations de types de texture
enum TEXTypeEnum {TYPE_TEXTURE2D, TYPE_TEXTURE_CUBEMAP, TYPE_TEXTURE_CUBEMAP_HDR};


///////////////////////////////////////////////////////////////////////////////
///  @class CTextureAbstraite
///  @brief Cette classe encapsule une texture g�n�rique openGL.
///
///  @remarks la fonction membre virtuelle pure chargerTexture() doit �tre 
///         impl�ment�e � la saveur de la texture surcharg�e. Par exemple, 
///         une texture HDR surchargera la fonction chargerImage() de fa�on 
///         � charger en m�moire une image HDR. La seule fonction qui est 
///         publi�e au public, est "appliquerTexture(...) qui permet les trois choses
///         suivantes :
///              1) Active l'unit� de texture d�sir�e (pour le multitexturage)
///              2) active le texturage sur la cible s�lectionn�e
///              3) Lie (bind) la texture � la cible associ�e
///
///  @author Fr�d�ric Plourde 
///  @date   2008-01-17 
///
///////////////////////////////////////////////////////////////////////////////
class CTextureAbstraite
{
public:
   /// constructeur sp�cifique
   CTextureAbstraite(char* nomFichier, GLenum cible, bool mipmap = false, bool genTex = true);
   /// constructeur sp�cifique
   CTextureAbstraite(GLenum cible, bool mipmap = false, bool genTex = true);
   /// destructeur par d�faut
   ~CTextureAbstraite(void);
   
   /// applique la texture dans openGL et sp�cifie les param�tres de texturage
   void appliquer(uint flagParams, GLenum gl_texture_wrap_s,       GLenum gl_texture_wrap_t,      GLenum gl_texture_wrap_r,
                                   GLenum gl_texture_min_filter,   GLenum gl_texture_mag_filter, 
                                   GLenum gl_texture_min_lod,      GLenum gl_texture_max_lod, 
                                   GLenum gl_texture_base_level,   GLenum gl_texture_max_level, 
                                   GLenum gl_texture_border_color, GLenum gl_texture_priority,
                                   bool mipmapping,                GLenum uniteTexture = GL_NONE);

   /// d�sactive la texture (sous la cible associ�e) dans openGL
   void desactiver();

protected:
   /// m�thode virtuelle pure de chargement de la texture en m�moire qui devrait toujours �tre impl�ment�e dans la version surcharg�e
   virtual void chargerTexture() = 0; // devrait toujours �tre surcharg�e "priv�e"

   void genTex();

   /// fonction utilitaire servant � charger un BMP en m�moire � partir d'un nom de fichier
   int loadBMP(char *nomFichier, Image *image);

   /// le nom de fichier de la texture
   char*  nomFichier_;
   /// le nom de texture openGL associ� � cette texture
   GLuint nomTexture_;
   /// la cible openGL associ�e � cette texture
   const  GLenum CIBLE_;
   /// la derni�re unit� de texture (GL_TEXTURE0, GL_TEXTURE1, etc...) appliqu�e � cette texture
   GLenum derniereUniteTexture_;
   /// doit-on mipmaper ?
   bool mipmap_;
};
