///////////////////////////////////////////////////////////////////////////////
///  @file Modele3DAbstrait.h
///  @author  Fr�d�ric Plourde
///  @brief   D�clare la classe CModele3DAbstrait qui encapsule un mod�le 3D
///           openGL dont le graphisme est sp�cifi� par l'entremise d'un 
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
///  @remarks Pour cr�er un objet graphique (utilisant une liste d'affichage openGL), 
///           on devrait D�RIVER une classe personnalis� de CModele3DAbstrait. la
///           fonction prot�g�e "construire" est disponible � toute classe d�riv�e
///           et doit imp�rativement �tre appel�e � la construction de la classe
///           d�riv�e afin de fournir � la classe de base abstraite les pointeurs
///           de fonction sur la fonction d'affichage (au moins) et la fonction
///           de d'application des textures (faccult.).  Le graphisme "glBegin...glEnd"
///           devrait donc toujours faire partie de la classe d�riv�e et �tre point�e
///           par le pointeur de fonction "dessinerFunc" pass� � "construire()".
///
///  @author Fr�d�ric Plourde 
///  @date   2008-03-11   <TODO: ins�rer initiales ici> <TODO: ins�rer le texte ici> 
///
///////////////////////////////////////////////////////////////////////////////
class CModele3DAbstrait
{
public:
	/// constructeur cr�ant un mod�le 3D g�n�rique comportant une seule texture
	CModele3DAbstrait(float echelle, char * nomFichierTexture, TEXTypeEnum texType, bool compilerTex = true, bool mipmap = false);
	/// constructeur cr�ant un mod�le 3D g�n�rique comportant plusieurs textures
	CModele3DAbstrait(float echelle, std::vector<char*> *nomsFichiersTextures, TEXTypeEnum texType, bool compilerTex = true, bool mipmap = false);
	/// destructeur par d�faut
	~CModele3DAbstrait(void);
	/// ajoute une texture sp�cifique (pr�construite)au mod�le
	void ajouterTexture(CTextureAbstraite* texture);
	/// doit etre implement� par les classes enfant pour afficher le modele
	virtual void dessiner() = 0;

	//////////////////////////////////////////
	// Les Accesseurs...                     /
	//////////////////////////////////////////
	/// obtient l'�chelle du mod�le 3D
	inline float obtenirEchelle() const;
	/// modifie l'�chelle du mod�le 3D
	inline void modifierEchelle(float echelle);
	/// obtient une r�f�rence sur la texture
	inline std::vector<CTextureAbstraite*>* obtenirTextures();
	/// Fonction permettant d'attribuer un nuanceur au modele
	void attribuerNuanceur(CNuanceurProg nuanceur);

	/// Fonction permettant d'activer le nuanceur
	void activerNuanceur();

protected:
	// Construit les diff�rentes textures sp�cifi�e
	virtual void chargerTextures();
	//On applique les textures
	virtual void appliquerTextures();

	/// la liste des textures openGL du mod�le 3D
	std::vector<CTextureAbstraite*> textures_;
	/// Programme de nuanceurs de l'objet
	CNuanceurProg m_nuanceur_prog;

private:
	/// le type de textures associ�es � l'objet (GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP, etc...)
	TEXTypeEnum texType_;
	/// facteur d'�chelle g�n�ral appliqu� dans la liste d'affichage (glScale) lors de la compilation
	float  echelle_;
	/// doit-on mipmapper ?
	bool mipmap_;
	/// flag disant si oui ou non les textures seront inclues dans la liste d'Affichage ou non (laiss�es � la discr�tion du l'usager)
	bool   compilerTex_;
	/// la liste des noms de fichiers des textures
	std::vector<char*> nomsFichiersTextures_;

};



////////////////////////////////
// D�finitions inline
////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirEchelle \n
///
///  obtient l'�chelle du mod�le 3D
///
///  @param [in]       Aucun
///  @author Fr�d�ric Plourde 
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
///  // modifie l'�chelle du mod�le 3D
///
///  @param [in]       echelle  float  la nouvelle �chelle du mod�le 3D
///
///  @author Fr�d�ric Plourde 
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
///  obtient une r�f�rence sur la te du mod�le
///
///  @param [in]       Aucun
///  @author Fr�d�ric Plourde 
///  @date   2008-02-18
///
///////////////////////////////////////////////////////////////////////////////
inline std::vector<CTextureAbstraite*>* CModele3DAbstrait::obtenirTextures()
{
	return &textures_;
}

