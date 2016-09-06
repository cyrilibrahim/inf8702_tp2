///////////////////////////////////////////////////////////////////////////////
///  @file GrilleQuads.cpp
///  @author  Félix Harvey
///  @brief   Définit la classe CGrilleQuads qui encapsule les face d'un cube, 
///			  ou le mesh du gazon, ou autre.
///  @date    2016
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////

#include "GrilleQuads.h"


CGrilleQuads::CGrilleQuads(char * nomFichierTexture, float largeur, float hauteur, int nbColonnes, int nbRangees, float echelle, bool mipmap, bool bumpy) :
CModele3DAbstrait(echelle, nomFichierTexture, TYPE_TEXTURE2D, true, mipmap)
{
	// initialisations...
	largeur_ = largeur;
	hauteur_ = hauteur;
	nbColonnes_ = nbColonnes;
	nbRangees_ = nbRangees;
	isBumpy_ = bumpy;

	creerLaGrille(largeur_, hauteur_, nbRangees_, nbColonnes_, true);
}

CGrilleQuads::CGrilleQuads(std::vector<char*> *nomsFichiersTextures, float largeur, float hauteur, int nbColonnes, int nbRangees, float echelle, bool mipmap, bool bumpy) :
CModele3DAbstrait(echelle, nomsFichiersTextures, TYPE_TEXTURE2D, true, mipmap)
{
	// initialisations...
	largeur_ = largeur;
	hauteur_ = hauteur;
	nbColonnes_ = nbColonnes;
	nbRangees_ = nbRangees;
	isBumpy_ = bumpy;

	creerLaGrille(largeur_, hauteur_, nbRangees_, nbColonnes_, true);
	
}

void CGrilleQuads::creerLaGrille(float largeur, float hauteur, int nbRangees, int nbColonnes, bool normaleVersExt)
{
	GLenum err = glGetError();

	m_sommets.clear();

	float normFact = normaleVersExt ? -1.f : 1.f;

	float startX = -largeur / 2.0f;
	float startY = hauteur / 2.0f;
	float s1, t1, s2, t2;

	float incrementX = largeur / (float)nbColonnes;
	float incrementY = hauteur / (float)nbRangees;

	float val;
	for (int i = 0; i<nbColonnes; i++) {
		for (int k = 0; k<nbRangees; k++) {

			s1 = (i*incrementX) / largeur;
			s2 = ((i + 1)*incrementX) / largeur;
			t1 = (k*incrementY) / hauteur;
			t2 = ((k + 1)*incrementY) / hauteur;

			// Tex
			m_sommets.push_back(s1);
			m_sommets.push_back(t1);
			// Normale
			m_sommets.push_back(0.0f);
			m_sommets.push_back(0.0f);
			m_sommets.push_back(normFact);
			// Position
			m_sommets.push_back(startX + i*incrementX);
			m_sommets.push_back(startY - k*incrementY);
			m_sommets.push_back(0.0f);

			m_sommets.push_back(s2);
			m_sommets.push_back(t1);

			m_sommets.push_back(0.0f);
			m_sommets.push_back(0.0f);
			m_sommets.push_back(normFact);

			m_sommets.push_back((startX + i*incrementX) + incrementX);
			m_sommets.push_back(startY - k*incrementY);
			m_sommets.push_back(0.0f);

			m_sommets.push_back(s2);
			m_sommets.push_back(t2);

			m_sommets.push_back(0.0f);
			m_sommets.push_back(0.0f);
			m_sommets.push_back(normFact);

			m_sommets.push_back((startX + i*incrementX) + incrementX);
			m_sommets.push_back((startY - k*incrementY) - incrementY);
			m_sommets.push_back(0.0f);

			m_sommets.push_back(s1);
			m_sommets.push_back(t2);

			m_sommets.push_back(0.0f);
			m_sommets.push_back(0.0f);
			m_sommets.push_back(normFact);

			m_sommets.push_back(startX + i*incrementX);
			m_sommets.push_back((startY - k*incrementY) - incrementY);
			m_sommets.push_back(0.0f);
		}
	}

	std::vector<int> indices(m_sommets.size() / 8);
	for (int i = 0; i < m_sommets.size() / 8; i++)
	{
		indices[i] = i;
	}

	// Notre Vertex Array Object - VAO
	glGenVertexArrays(1, &m_quads_vao);
	// Un buffer pour les sommets
	glGenBuffers(1, &m_sommets_vbo);
	// Un buffer pour les indices
	glGenBuffers(1, &m_quads_ibo);

	glBindVertexArray(m_quads_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_sommets_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quads_ibo);
	int s_byte_size = m_sommets.size() * sizeof(float);
	int i_byte_size = indices.size() * sizeof(int);
	glBufferData(GL_ARRAY_BUFFER, s_byte_size, &m_sommets[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_byte_size, &indices[0], GL_STATIC_DRAW);

	m_size = indices.size();

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (0));//texcoords
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (2 * sizeof(float)));//normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (5 * sizeof(float)));//positions
	glEnableVertexAttribArray(2);

	err = glGetError();
}

CGrilleQuads::~CGrilleQuads(void)
{
}

//void CGrilleQuads::appliquerTextures(void*)
//{
//	appliquerBruitPerlin();
//}

void CGrilleQuads::dessiner()
{
	glBindVertexArray(m_quads_vao);
	//if (isBumpy_){
	appliquerBruitPerlin();	
	//}
	appliquerTextures();

	if (!m_sommets.empty())
	{
		glDrawElements(
			GL_QUADS,       // mode
			m_size,				// count
			GL_UNSIGNED_INT,    // type
			(void*)0            // element array buffer offset
			);
	}
}

void CGrilleQuads::appliquerBruitPerlin()
{
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, CVar::perlinTex);
	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}