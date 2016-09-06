///////////////////////////////////////////////////////////////////////////////
///  @file GrilleQuads.h
///  @author  Felix Harvey
///  @brief   Déclare la classe CGrilleQuads qui encapsule les face d'un cube, 
///			  ou le mesh du gazon.
///  @date    2016
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Cst.h"
#include "Texture2D.h"

#include "noise.h"
#include "TextureAbstraite.h"
#include "Modele3DAbstrait.h"
#include "Lumiere.h"
#include  <GL/glew.h> 
#include <vector>


///////////////////////////////////////////////////////////////////////////////
///  CGrilleQuad
///  Cette classe représente une grille de quads qui se prête bien au texturage,
///  bump mapping, normal mapping, displacement mapping, etc.
///
///
///  @author Felix Harvey
///  @date   2016
///
///////////////////////////////////////////////////////////////////////////////
class CGrilleQuads :
	public CModele3DAbstrait
{
public:
	/// constructeur spécifique pour création d'une carte ne comportant qu'une seule texture
	CGrilleQuads(char * nomFichierTexture, float largeur, float hauteur, int nbColonnes, int nbRangees, float echelle = 1.0, bool mipmap=false, bool bumpy=false);
	/// constructeur spécifique pour création d'une carte comportant plusieurs textures
	CGrilleQuads(std::vector<char*> *nomsFichiersTextures, float largeur, float hauteur, int nbColonnes, int nbRangees, float echelle = 1.0, bool mipmap = false, bool bumpy = false);
	/// destructeur par défaut
	~CGrilleQuads(void);

	/// fonction à implémenter pour définir la géométrie openGL de la carte d'identité de poly (est statique, car est référée par un pointeur de fonction)
	void dessiner();

private:
	/// fonction personnalisée qui applique le bruit de perlin
	void appliquerBruitPerlin();

	/// la largeur de la carte, en unités d'objet
	float largeur_;
	/// la hauteur de la carte, en unités d'objet
	float hauteur_;
	/// le nombre de divisions verticales du maillage de la carte
	float nbRangees_;
	/// le nombre de divisions horizontales du maillage de la carte
	float nbColonnes_;
	// As-t-on besoin de bruit de perlin?
	bool isBumpy_;

	/// ID du VBO pour les sommets
	GLuint			 m_sommets_vbo;
	/// ID du IBO pour les quads
	GLuint			 m_quads_ibo;
	/// ID du VAO pour les quads
	GLuint			 m_quads_vao;
	/// Nombre de floats à lire lors de l'affichage
	GLint			 m_size;

	// Conteneur pour les sommets (tex/normales/positions)
	std::vector<float> m_sommets;

	/// fonction privée de création du maillage de la carte
	void creerLaGrille(float largeur, float hauteur, int nbRangees, int nbColonnes, bool normaleVersExt);
};
