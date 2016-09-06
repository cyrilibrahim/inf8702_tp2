///////////////////////////////////////////////////////////////////////////////
///  @file Modele3D.h
///  @author  Frédéric Plourde
///  @brief   Déclare la classe CModele3DOBJ qui encapsule un modele3D spécifique 
///           chargé à partir d'un fichier OBJ
///  @date    2008-10-27
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "modele3dabstrait.h"
#include "Lumiere.h"
#include "Cst.h"
#include "Texture2D.h"
#include "Objparser/OBJParser.h"
#include "Objparser/Geometry.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/matrix_inverse.hpp>
#include <gtx/transform.hpp>
#include <gtx/matrix_cross_product.hpp>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
///  CModele3DOBJ
///  Cette classe encapsule l'objet grahique principal du TP : un modèle 3D chargé
///  à partir d'un fichier OBJ
///
///  Base class CModele3DOBJAbstrait La classe de base encapsule tout modèle 3D openGL
///
///
///  @author Frédéric Plourde 
///  @date   2008-10-27
///
///////////////////////////////////////////////////////////////////////////////
class CModele3DOBJ :
	public CModele3DAbstrait
{
public:
	/// constructeur spécifique pour création du modèle 3D ne comportant qu'une seule texture
	CModele3DOBJ(char* nomFichierOBJ, char * nomFichierTexture, float echelle = 1.0);
	/// constructeur spécifique pour création du modèle 3D comportant plusieurs textures
	CModele3DOBJ(char* nomFichierOBJ, std::vector<char*> *nomsFichiersTextures, float echelle = 1.0);
	/// destructeur par défaut
	~CModele3DOBJ(void);
	/// Fonction compatible avec opengl4 qui affiche le modèle 3D à partir des tableaux de sommets lus dans le fichier source OBJ.
	void dessiner();
	/// fonction qui charge en mémoire les sommets et les normales d'un modèle définit dans un fichier .OBJ.
	void chargerModeleOBJ(char* fichierOBJ);
	/// fonction à implémenter pour personnaliser l'application de texture (à faire aussi : dans le constructeur, appeler "construire(&dessiner, &appliquerTextures)"
	void appliquerTextures(void*);
	/// fonction qui permet de definir un nuanceur pour l'objet.
	//void attribuerNuanceur(CNuanceurProg nuanceur);


private:

	/// le tableau des sommets du modèle 3D
	vector<Vertex>   g_Vertices_;

	/// le tableau des triangles du modèle 3D
	vector<Triangle> g_Triangles_;

	/// le tableau des quads du modèle 3D
	vector<Quad>     g_Quads_;

	/// le centroïde du modèle3D
	CVecteur3        g_ObjCentroid_;

	/// ID du VBO pour les sommets
	GLuint			 m_sommets_vbo;

	/// ID du IBO pour les triangles
	GLuint			 m_triangles_ibo;

	/// ID du VAO pour les triangles
	GLuint			 m_triangles_vao;

	/// ID du IBO pour les quads
	GLuint			 m_quads_ibo;

	/// ID du VAO pour les quads
	GLuint			 m_quads_vao;

	/// Nombre de floats à lire lors de l'affichage
	GLint			 m_size;

	/// Programme de nuanceurs de l'objet
	//CNuanceurProg m_nuanceur_prog;

};
