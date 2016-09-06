///////////////////////////////////////////////////////////////////////////////
///  @file Modèle3D-OBJ.cpp
///  @author  Frédéric Plourde
///  @brief   Définit la classe CModele3DOBJ qui encapsule un modele3D 
///           chargé à partir d'un fichier OBJ
///  @date    2008-10-27
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////

#include "Modele3DOBJ.h"

//vector<Vertex>    CModele3DOBJ::g_Vertices_;
//vector<Triangle>  CModele3DOBJ::g_Triangles_;
//vector<Quad>      CModele3DOBJ::g_Quads_;
//CVecteur3         CModele3DOBJ::g_ObjCentroid_;

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CModele3DOBJ \n
///  constructeur d'un modèle 3D avec 1 seule texture (utile seulement pour 
///  faire des tests du côté openGL... pas utile pour le labo en tant que tel...
///
///  @param [in, out]  nomsFichierOBJ char *	    La chaîne de caractères contenant le nom de fichier OBJ du modèle 3D
///  @param [in, out]  nomFichierTexture char *     l'unique nom de fichier de l'unique texture
///  @param [in]       echelle float [=1.000000]    mise à l'échelle qui sera appliquée automatique (glScale)
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2008-10-27
///
///////////////////////////////////////////////////////////////////////////////
CModele3DOBJ::CModele3DOBJ(char* nomFichierOBJ, char * nomFichierTexture, float echelle) :
CModele3DAbstrait(echelle, nomFichierTexture, TYPE_TEXTURE2D, true)
{
	// charger le modèle 3D en mémoire
	chargerModeleOBJ(nomFichierOBJ);
}


///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CModele3DOBJ \n
///  constructeur d'un modèle 3D avec plusieurs textures. Cette version du constructeur
///  est particulièrement utile lorsqu'on veut associer plusieurs textures aux différentes
///  unitées de texture du nuanceur.
///
///  @param [in, out]  nomsFichierOBJ char *        La chaîne de caractères contenant le nom de fichier OBJ du modèle 3D
///  @param [in, out]  nomsFichiersTextures std::vector<char*> *    Le vecteur contenant la liste des noms de fichiers. Cette liste est copiée, alors l'appelant peut en disposer.
///  @param [in]       echelle float [=1.000000]    mise à l'échelle qui sera appliquée automatique (glScale)
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2008-10-27
///
///////////////////////////////////////////////////////////////////////////////
CModele3DOBJ::CModele3DOBJ(char* nomFichierOBJ, std::vector<char*> *nomsFichiersTextures, float echelle) :
CModele3DAbstrait(echelle, nomsFichiersTextures, TYPE_TEXTURE2D, true)
{
	// charger le modèle 3D en mémoire
	chargerModeleOBJ(nomFichierOBJ);
}



///////////////////////////////////////////////////////////////////////////////
///  public destructor  ~CModele3DOBJ \n
///  Destructeur par défaut.
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2008-10-27
///
///////////////////////////////////////////////////////////////////////////////
CModele3DOBJ::~CModele3DOBJ(void)
{
	// Clean up
	g_Vertices_.clear();
	g_Triangles_.clear();
	g_Quads_.clear();
}


///////////////////////////////////////////////////////////////////////////////
///  public static  chargerModeleOBJ \n
///  Fonction qui charge en mémoire les sommets et les normales d'un modèle 
///  définit dans un fichier .OBJ.
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2008-10-27
///
///////////////////////////////////////////////////////////////////////////////
void CModele3DOBJ::chargerModeleOBJ(char* fichierOBJ)
{
	COBJParser* Parser = new COBJParser();

	if (Parser->OpenFile(fichierOBJ))
	{
		GLenum error = glGetError();
		cerr << "Lecture du fichier : " << fichierOBJ << endl;
		Parser->ParseFile();
		Parser->CloseFile();

		g_Vertices_ = Parser->GetVertices();
		g_Triangles_ = Parser->GetTriangles();
		g_Quads_ = Parser->GetQuads();
		g_ObjCentroid_ = Parser->GetCentroid();

		cerr << "Centroid: " << g_ObjCentroid_ << endl;
		cerr << "Nombre de faces : " << (g_Triangles_.size() + g_Quads_.size()) << endl;

		vector<float> vertex_vector = getFloatsFromVertices(g_Vertices_);
		int byte_size = vertex_vector.size() * sizeof(float);

		// Notre Vertex Array Object - VAO
		glGenVertexArrays(1, &m_triangles_vao);
		// Un buffer pour les sommets
		glGenBuffers(1, &m_sommets_vbo);
		// Un buffer pour les indices des sommets des triangles
		glGenBuffers(1, &m_triangles_ibo);

		// Lier 
		glBindVertexArray(m_triangles_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_sommets_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_triangles_ibo);

		//Peupler
		glBufferData(GL_ARRAY_BUFFER, byte_size, &vertex_vector[0], GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_Triangles_.size()*sizeof(Triangle), &g_Triangles_[0].Vertex[0], GL_STATIC_DRAW);

		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &m_size);

		//glBindBuffer(GL_ARRAY_BUFFER, m_sommets_vbo);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (0));//texcoords
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (2 * sizeof(float)));//normals
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (5 * sizeof(float)));//positions
		glEnableVertexAttribArray(2);

		cerr << "Chargement termine !!" << endl;
	}

	delete Parser;
}



///////////////////////////////////////////////////////////////////////////////
///  
///
///  @return Aucune
///
///  @author 
///  @date   
///
///////////////////////////////////////////////////////////////////////////////
void CModele3DOBJ::appliquerTextures(void*)
{
}


/// fonction qui permet de definir un nuanceur pour l'objet.
//void CModele3DOBJ::attribuerNuanceur(CNuanceurProg nuanceur)
//{
//	m_nuanceur_prog = nuanceur;
//}


///////////////////////////////////////////////////////////////////////////////
///  public static  afficherModele3DOGL4 \n
///  Fonction qui affiche le modèle 3D à partir des tableaux de sommets lus 
///  dans le fichier source OBJ.
///
///  @return Aucune
///
///  @author Félix G. Harvey
///  @date   2016
///
///////////////////////////////////////////////////////////////////////////////
void CModele3DOBJ::dessiner()
{
	if (!g_Triangles_.empty())
	{
		glDrawElements(
			GL_TRIANGLES,       // mode
			m_size,				// count
			GL_UNSIGNED_INT,    // type
			(void*)0            // element array buffer offset
			);
	}
}

