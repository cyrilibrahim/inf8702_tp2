///////////////////////////////////////////////////////////////////////////////
///  @file Modele3DAbstrait.h
///  @author  Frédéric Plourde
///  @brief   Déclare la classe CModele3DAbstrait qui encapsule un modèle 3D
///           openGL dont le graphisme est spécifié par l'entremise d'un 
///           pointeur de fonction
///  @date    2007-12-13
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TextureAbstraite.h"
#include "NuanceurProg.h"
#include "TextureCubemap.h"
#include  <GL/glew.h> 
#include <vector>
#include <string>


///////////////////////////////////////////////////////////////////////////////
///  CModele3DAbstrait
///  Cette classe encapsule tout objet graphique openGL.
///
///
///  @remarks Pour créer un objet graphique (utilisant une liste d'affichage openGL), 
///           on devrait DÉRIVER une classe personnalisé de CModele3DAbstrait. la
///           fonction protégée "construire" est disponible à toute classe dérivée
///           et doit impérativement être appelée à la construction de la classe
///           dérivée afin de fournir à la classe de base abstraite les pointeurs
///           de fonction sur la fonction d'affichage (au moins) et la fonction
///           de d'application des textures (faccult.).  Le graphisme "glBegin...glEnd"
///           devrait donc toujours faire partie de la classe dérivée et être pointée
///           par le pointeur de fonction "dessinerFunc" passé à "construire()".
///
///  @author Frédéric Plourde 
///  @date   2008-03-11   <TODO: insérer initiales ici> <TODO: insérer le texte ici> 
///
///////////////////////////////////////////////////////////////////////////////
class CModele3DAbstrait
{
public:
	/// constructeur créant un modèle 3D générique comportant une seule texture
	CModele3DAbstrait(float echelle, char * nomFichierTexture, TEXTypeEnum texType, bool compilerTex = true, bool mipmap = false);
	/// constructeur créant un modèle 3D générique comportant plusieurs textures
	CModele3DAbstrait(float echelle, std::vector<char*> *nomsFichiersTextures, TEXTypeEnum texType, bool compilerTex = true, bool mipmap = false);
	/// destructeur par défaut
	~CModele3DAbstrait(void);
	/// ajoute une texture spécifique (préconstruite)au modèle
	void ajouterTexture(CTextureAbstraite* texture);
	/// doit etre implementé par les classes enfant pour afficher le modele
	virtual void dessiner() = 0;

	//////////////////////////////////////////
	// Les Accesseurs...                     /
	//////////////////////////////////////////
	/// obtient l'échelle du modèle 3D
	inline float obtenirEchelle() const;
	/// modifie l'échelle du modèle 3D
	inline void modifierEchelle(float echelle);
	/// obtient une référence sur la texture
	inline std::vector<CTextureAbstraite*>* obtenirTextures();
	/// Fonction permettant d'attribuer un nuanceur au modele
	void attribuerNuanceur(CNuanceurProg nuanceur);

	/// Fonction permettant d'activer le nuanceur
	void activerNuanceur();

protected:
	// Construit les différentes textures spécifiée
	virtual void chargerTextures();
	//On applique les textures
	virtual void appliquerTextures();

	/// la liste des textures openGL du modèle 3D
	std::vector<CTextureAbstraite*> textures_;
	/// Programme de nuanceurs de l'objet
	CNuanceurProg m_nuanceur_prog;

private:
	/// le type de textures associées à l'objet (GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP, etc...)
	TEXTypeEnum texType_;
	/// facteur d'échelle général appliqué dans la liste d'affichage (glScale) lors de la compilation
	float  echelle_;
	/// doit-on mipmapper ?
	bool mipmap_;
	/// flag disant si oui ou non les textures seront inclues dans la liste d'Affichage ou non (laissées à la discrétion du l'usager)
	bool   compilerTex_;
	/// la liste des noms de fichiers des textures
	std::vector<char*> nomsFichiersTextures_;

};



////////////////////////////////
// Définitions inline
////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirEchelle \n
///
///  obtient l'échelle du modèle 3D
///
///  @param [in]       Aucun
///  @author Frédéric Plourde 
///  @date   2008-02-18
///
///////////////////////////////////////////////////////////////////////////////
inline float CModele3DAbstrait::obtenirEchelle() const
{
	return echelle_;
}


///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierEchelle \n
///
///  // modifie l'échelle du modèle 3D
///
///  @param [in]       echelle  float  la nouvelle échelle du modèle 3D
///
///  @author Frédéric Plourde 
///  @date   2008-02-18
///
///////////////////////////////////////////////////////////////////////////////
inline void CModele3DAbstrait::modifierEchelle(float echelle)
{
	echelle_ = echelle;
}



///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirTextures \n
///
///  obtient une référence sur la te du modèle
///
///  @param [in]       Aucun
///  @author Frédéric Plourde 
///  @date   2008-02-18
///
///////////////////////////////////////////////////////////////////////////////
inline std::vector<CTextureAbstraite*>* CModele3DAbstrait::obtenirTextures()
{
	return &textures_;
}

