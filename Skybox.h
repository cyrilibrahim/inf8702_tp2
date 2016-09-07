///////////////////////////////////////////////////////////////////////////////
///  @file Skybox.h
///  @author  Fr�d�ric Plourde 
///  @brief   D�clare la classe CSkybox qui encapsule un skybox openGL avec
///           texture cubemap en format cross
///  @date    2007-12-11
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Modele3DAbstrait.h"

class CSkybox :
   public CModele3DAbstrait
{
public:
   /// constructeur cr�ant un skybox avec texture sp�cifi�e unique (obligatoire)
   CSkybox(char * nomFichierTexture, float echelle);
   /// destructeur par d�faut
   ~CSkybox(void);

   /// fonction � impl�menter pour d�finir la g�om�trie openGL du skybox (est statique, car est r�f�r�e par un pointeur de fonction)
   void dessiner();
   /// fonction � impl�menter pour d�finir un texturage personnalis�
   void appliquerTextures(void);

private:
	void setupVAO();
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	GLint m_taille;

};
