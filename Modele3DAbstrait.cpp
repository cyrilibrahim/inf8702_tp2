///////////////////////////////////////////////////////////////////////////////
///  @file Modele3DAbstrait.cpp
///  @author  Fr�d�ric Plourde
///  @brief   D�finit la classe CModele3DAbstrait qui encapsule un mod�le 3D
///           openGL dont le graphisme est sp�cifi� par l'entremise d'un 
///           pointeur de fonction
///  @date    2007-12-13
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////

#include "Modele3DAbstrait.h"
#include "Texture2D.h"
#include <cstring>
#include "Cst.h"


///////////////////////////////////////////////////////////////////////////////
///  CModele3DAbstrait::CModele3DAbstrait(float echelle, char * nomFichierTexture, TEXTypeEnum texType = TYPE_TEXTURE2D, bool compilerTex = true)
///  Construit un mod�le 3D openGL g�n�rique au et ne comportant qu'une seule texture interne
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
CModele3DAbstrait::CModele3DAbstrait(float echelle, char * nomFichierTexture, TEXTypeEnum texType = TYPE_TEXTURE2D, bool compilerTex, bool mipmap) :
echelle_(echelle), texType_(texType), compilerTex_(compilerTex), mipmap_(mipmap)
{
	// m�moriser le nom de fichier
	if (nomFichierTexture) {
		if (strlen(nomFichierTexture) >= 1) {
			char * temp;
			temp = new char[strlen(nomFichierTexture)];
			strcpy(temp, nomFichierTexture);
			nomsFichiersTextures_.push_back(temp);
		}
	}

	this->chargerTextures();

}



///////////////////////////////////////////////////////////////////////////////
///  CModele3DAbstrait::CModele3DAbstrait(float echelle, std::vector<char*> *nomsFichiersTextures, TEXTypeEnum texType = TYPE_TEXTURE2D, bool compilerTex = true)
///  Construit un mod�le 3D openGL g�n�rique et comportant plusieurs textures sp�cifiques dans un std::vecteur.
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
CModele3DAbstrait::CModele3DAbstrait(float echelle, std::vector<char*> *nomsFichiersTextures, TEXTypeEnum texType = TYPE_TEXTURE2D, bool compilerTex, bool mipmap) :
echelle_(echelle), texType_(texType), compilerTex_(compilerTex), mipmap_(mipmap)
{
	// m�moriser les diff�rents noms de fichiers
	if (nomsFichiersTextures) {
		if (nomsFichiersTextures->size() >= 1) {
			for (uint i = 0; i < nomsFichiersTextures->size(); i++) {
				if (strlen((*nomsFichiersTextures)[i]) >= 1) {
					char * temp;
					temp = new char[strlen((*nomsFichiersTextures)[i])];
					strcpy(temp, (*nomsFichiersTextures)[i]);
					nomsFichiersTextures_.push_back(temp);
				}
			}
		}
	}
	this->chargerTextures();
}



///////////////////////////////////////////////////////////////////////////////
///  public destructor  ~CModele3DAbstrait \n
///  Destructeur par d�faut
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
CModele3DAbstrait::~CModele3DAbstrait(void)
{
	// lib�rer la m�moire de texture
	nomsFichiersTextures_.clear();
	textures_.clear();
}

void CModele3DAbstrait::chargerTextures()
{
	// cr�er la texture si sp�cifi�e
	if (nomsFichiersTextures_.size() >= 1) {
		for (uint i = 0; i < nomsFichiersTextures_.size(); i++) {
			switch (texType_) {
			case TYPE_TEXTURE2D: {
				textures_.push_back(new CTexture2D(nomsFichiersTextures_[i], mipmap_));
				break;
			}
			case TYPE_TEXTURE_CUBEMAP: {
				textures_.push_back(new CTextureCubemap(nomsFichiersTextures_[i]));
				break;
			}
			}
		}
	}
	else {
		// signifie qu'il n'y aura pas de texture d'appliqu�e.
	}
}

void CModele3DAbstrait::appliquerTextures()
{
	if (nomsFichiersTextures_.size() >= 1)
	{
		// sinon, texturer de fa�on g�n�rique pour chaque texture
		for (uint i = 0; i < textures_.size(); i++) {

			textures_[i]->appliquer(WRAP_S | WRAP_T | WRAP_R | MIN_FILTER | MAG_FILTER,
				GL_CLAMP, GL_CLAMP, GL_CLAMP,
				GL_LINEAR, GL_LINEAR,
				0, 0,
				0, 0,
				0, 0,
				mipmap_,
				CCst::unitesTextures[i]);

			// s'il y a plusieurs textures de sp�cifi�es en couche, appliquer
			// un modulate g�n�rique
			if (textures_.size() > 1) {
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			}
		}
	}

}

///////////////////////////////////////////////////////////////////////////////
///  public  ajouterTexture \n
///  Ajoute une texture sp�cifique (pr�construite) a l'ensemble des textures
///  du mod�le.
///
///  @param [in, out]  texture CTextureAbstraite *   le pointeur sur la texture abstraite.
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-03-09
///
///////////////////////////////////////////////////////////////////////////////
void CModele3DAbstrait::ajouterTexture(CTextureAbstraite* texture)
{
	textures_.push_back(texture);
}

/// fonction qui permet de definir un nuanceur pour l'objet.
void CModele3DAbstrait::attribuerNuanceur(CNuanceurProg nuanceur)
{
	m_nuanceur_prog = nuanceur;
}

/// fonction qui permet de definir un nuanceur pour l'objet.
void CModele3DAbstrait::activerNuanceur()
{
	m_nuanceur_prog.activer();
}
