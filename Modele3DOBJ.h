///////////////////////////////////////////////////////////////////////////////
///  @file Modele3D.h
///  @author  Fr�d�ric Plourde
///  @brief   D�clare la classe CModele3DOBJ qui encapsule un modele3D sp�cifique 
///           charg� � partir d'un fichier OBJ
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
///  Cette classe encapsule l'objet grahique principal du TP : un mod�le 3D charg�
///  � partir d'un fichier OBJ
///
///  Base class CModele3DOBJAbstrait La classe de base encapsule tout mod�le 3D openGL
///
///
///  @author Fr�d�ric Plourde 
///  @date   2008-10-27
///
///////////////////////////////////////////////////////////////////////////////
class CModele3DOBJ :
	public CModele3DAbstrait
{
public:
	/// constructeur sp�cifique pour cr�ation du mod�le 3D ne comportant qu'une seule texture
	CModele3DOBJ(char* nomFichierOBJ, char * nomFichierTexture, float echelle = 1.0);
	/// constructeur sp�cifique pour cr�ation du mod�le 3D comportant plusieurs textures
	CModele3DOBJ(char* nomFichierOBJ, std::vector<char*> *nomsFichiersTextures, float echelle = 1.0);
	/// destructeur par d�faut
	~CModele3DOBJ(void);
	/// Fonction compatible avec opengl4 qui affiche le mod�le 3D � partir des tableaux de sommets lus dans le fichier source OBJ.
	void dessiner();
	/// fonction qui charge en m�moire les sommets et les normales d'un mod�le d�finit dans un fichier .OBJ.
	void chargerModeleOBJ(char* fichierOBJ);
	/// fonction � impl�menter pour personnaliser l'application de texture (� faire aussi : dans le constructeur, appeler "construire(&dessiner, &appliquerTextures)"
	void appliquerTextures(void*);
	/// fonction qui permet de definir un nuanceur pour l'objet.
	//void attribuerNuanceur(CNuanceurProg nuanceur);


private:

	/// le tableau des sommets du mod�le 3D
	vector<Vertex>   g_Vertices_;

	/// le tableau des triangles du mod�le 3D
	vector<Triangle> g_Triangles_;

	/// le tableau des quads du mod�le 3D
	vector<Quad>     g_Quads_;

	/// le centro�de du mod�le3D
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

	/// Nombre de floats � lire lors de l'affichage
	GLint			 m_size;

	/// Programme de nuanceurs de l'objet
	//CNuanceurProg m_nuanceur_prog;

};
