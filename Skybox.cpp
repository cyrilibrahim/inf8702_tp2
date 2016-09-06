///////////////////////////////////////////////////////////////////////////////
///  @file Skybox.cpp
///  @author  Frédéric Plourde 
///  @brief   Définit la classe CSkybox qui encapsule un skybox openGL avec
///           texture cubemap en format cross
///  @date    2007-12-11
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////

#include "Skybox.h"

///////////////////////////////////////////////////////////////////////////////
///  public constructor  CSkybox \n
///  Construit un skybox au moyen d'une seule texture (seule possibilité pour un skybox)
///  attention : le format de la texture DOIT être en format "cross".
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
CSkybox::CSkybox(char * nomFichierTexture, float echelle = 1.0):
CModele3DAbstrait(echelle, nomFichierTexture, TYPE_TEXTURE_CUBEMAP, true, false)
{
   // il est nécessaire d'appeler "construire" ici pour créer la liste d'affichage
   // et les textures associées
   //construire(&dessiner, &appliquerTextures, true);
	setupVAO();
}



///////////////////////////////////////////////////////////////////////////////
///  public destructor  ~CSkybox \n
///  Destructeur par défaut d'un skybox
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
CSkybox::~CSkybox(void)
{
}


///////////////////////////////////////////////////////////////////////////////
///  public static  dessiner \n
///  Fonction à implémenter absolument si on veut voir apparaître quelque chose !
///  cette fonction sera appelée par la classe de base (CModele3DAbstrait) par 
///  l'entremise d'une pointeur de fonction passé à la construction. On mettra ici
///  uniquement le graphisme associé à l'objet (i.e.  glBegin()...glVertex(), etc...)
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
void CSkybox::dessiner()
{
	// appliquer la texture de façon personnalisée (mode CLAMP_TO_EDGE)
	appliquerTextures();

	glBindVertexArray(m_vao);
	glDrawElements(
		GL_QUADS,			// mode
		m_taille,			// count
		GL_UNSIGNED_INT,    // type
		(void*)0            // element array buffer offset
	);

}

void CSkybox::setupVAO()
{
	// Sommets du cube:
	float sommets[] = {
		// Positions			//Normales
		
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f,-0.5f, 0.5f, 0.0f, 0.0f, -1.0f,
		0.5f,-0.5f, 0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -1.0f,

		-0.5f,-0.5f,-0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f,-0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f,-0.5f, 0.0f, 0.0f, 1.0f,
		0.5f,-0.5,-0.5f, 0.0f, 0.0f, 1.0f,
		
		-0.5f, 0.5f,-0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, 0.5f,-0.5f, 0.0f, -1.0f, 0.0f,

		0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,-0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,-0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f,

		-0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f,

		0.5f,-0.5f,-0.5f, -1.0f, 0.0f, 0.0f,
		0.5f,-0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		0.5f, 0.5f,-0.5f, -1.0f, 0.0f, 0.0f,

	};

	// Indique les indexes des sommets composant les faces du cube (groupés en triangles)
	unsigned int indices_sommets[] = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};

	// Notre Vertex Array Object - VAO
	glGenVertexArrays(1, &m_vao);
	// Un buffer pour les sommets
	glGenBuffers(1, &m_vbo);
	// Un buffer pour les indices des sommets
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sommets), sommets, GL_STATIC_DRAW);
	
	// Retenir la taille nécessaire a dessiner plus tard.
	m_taille = sizeof(sommets);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_sommets), &indices_sommets[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char *)NULL + (0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char *)NULL + (16));
	glEnableVertexAttribArray(1);
}

void CSkybox::appliquerTextures()
{
   // appliquer la texture de façon personnalisée (mode CLAMP_TO_EDGE)
   (*(obtenirTextures()))[0]->appliquer(
      WRAP_S|WRAP_T|MIN_FILTER|MAG_FILTER, 
      GL_CLAMP_TO_EDGE,        GL_CLAMP_TO_EDGE,    0,
      GL_LINEAR, GL_LINEAR,
      0,                       0,
      0,                       0,
      0,                       0,
      false,                   GL_TEXTURE0);
}