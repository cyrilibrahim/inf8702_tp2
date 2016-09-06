///////////////////////////////////////////////////////////////////////////////
///  @file SurfaceBSplinaire.cpp
///  @author  Frédéric Plourde 
///  @brief   Définit la classe CSurfaceBSplinaire qui encapsule une surface
///           bsplinaire complètement paramétrable.
///  @date    2007-12-13
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#include "SurfaceBSplinaire.h"


// déclaration des membres statiques
Point* CSurfaceBSplinaire::points_;
float* CSurfaceBSplinaire::noeudsU_;
float* CSurfaceBSplinaire::noeudsV_;
GLuint CSurfaceBSplinaire::surfaceList_;
GLuint CSurfaceBSplinaire::textureName_;
unsigned int CSurfaceBSplinaire::nbNoeudsU_;
unsigned int CSurfaceBSplinaire::nbNoeudsV_;
unsigned int CSurfaceBSplinaire::nbPtsCtrlU_;
unsigned int CSurfaceBSplinaire::nbPtsCtrlV_;
unsigned int CSurfaceBSplinaire::degreU_;
unsigned int CSurfaceBSplinaire::degreV_;
unsigned int CSurfaceBSplinaire::ordreU_;
unsigned int CSurfaceBSplinaire::ordreV_;
float CSurfaceBSplinaire::scaleU_;
float CSurfaceBSplinaire::scaleV_;
unsigned int CSurfaceBSplinaire::NDD_;


CSurfaceBSplinaire::CSurfaceBSplinaire(uint numPts_U, uint numPts_V, const Point* Points, uint num_knots_U, uint num_knots_V, const float* knots_U, const float* knots_V, uint NDD, uint degree_U, uint degree_V, uint order_U, uint order_V, float scale_U, float scale_V)
{
   // initialisations
   nbNoeudsU_ = num_knots_U;
   nbNoeudsV_ = num_knots_V;
   nbPtsCtrlU_= numPts_U;
   nbPtsCtrlV_= numPts_V;
   degreU_    = degree_U;
   degreV_    = degree_V;
   ordreU_    = order_U;
   ordreV_    = order_V;
   scaleU_    = scale_U;
   scaleV_    = scale_V;
   NDD_       = NDD;

   // construction des noeuds
   noeudsU_ = new float[num_knots_U];
   for (uint i=0; i<num_knots_U; i++)
      noeudsU_[i] = knots_U[i];
   noeudsV_ = new float[num_knots_V];
   for (uint i=0; i<num_knots_V; i++)
      noeudsV_[i] = knots_V[i];

   // construction (et copie) des points de contrôle
   points_ = new Point[numPts_U * numPts_V];
   for (uint v=0; v<numPts_V; v++) {
      for (uint u=0; u<numPts_U; u++) {
         points_[v*numPts_U + u] = Points[v*numPts_U + u];
      }
   }

   setupVAO();
}




///////////////////////////////////////////////////////////////////////////////
///  public destructor  ~CSurfaceBSplinaire \n
///
///  Destructeur de la surface. Détruit : noeudsU_, noeudsV_ et points_
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
CSurfaceBSplinaire::~CSurfaceBSplinaire(void)
{
   if(noeudsU_)
      delete [] noeudsU_;

   if(noeudsV_)
      delete [] noeudsV_;

   if(points_)
      delete [] points_;
}


void CSurfaceBSplinaire::setupVAO()
{
	vect3D dVect, gVect, hVect, bVect;
	vect3D vectMoyenU, vectMoyenV;
	vect3D normale;

	//std::vector<float> sommets;
	//std::vector<unsigned int> indices;
	unsigned int idx = 0;

	glPointSize(3.0f);
	// pour chaque quad dans la patch Bspline
	for (int i = 0; i != NDD_ - 1; ++i) {
		for (int j = 0; j != NDD_ - 1; ++j) {

			for (int k = i; k <= i + 1; k++) {
				for (int l = j + ((k - i) == 0 ? 0 : 1); (k - i) == 0 ? l <= j + 1 : l >= j; (k - i) == 0 ? l++ : l--) {

					// calculer la valeur paramétrique u (centré au point courant)
					// et les valeurs paramétriques des sommets situés à droite (ud) et à gauche (ug)
					float u0 = (MaxU() - MinU())*(float)(k) / (NDD_ - 1) + MinU();
					float ug = (MaxU() - MinU())*(float)(MAX(k - 1, 0)) / (NDD_ - 1) + MinU();
					float ud = (MaxU() - MinU())*(float)(MIN(k + 1, NDD_ - 1)) / (NDD_ - 1) + MinU();

					// calculer la valeur paramétrique v (centré au point courant)
					// et les valeurs paramétriques des sommets situés en haut (vh) et en bas (vb)
					float v0 = (MaxV() - MinV())*(float)(l) / (NDD_ - 1) + MinV();
					float vh = (MaxV() - MinV())*(float)(MAX(l - 1, 0)) / (NDD_ - 1) + MinV();
					float vb = (MaxV() - MinV())*(float)(MIN(l + 1, NDD_ - 1)) / (NDD_ - 1) + MinV();

					// Calculer les coordonnées de différents points sur la patch
					// point courant (p0) + point gauche (pg), droit (pd), haut (ph) et bas (pb)
					Point p0 = calculer(u0, v0);
					Point pg = calculer(ug, v0);
					Point pd = calculer(ud, v0);
					Point pb = calculer(u0, vb);
					Point ph = calculer(u0, vh);

					// Calculer les vecteurs entre le point courant et ces différents points
					// vecteurs vers la droite (dVect), la gauche (gVect), le haut (hVect) et le bas (bVect)
					SUBVECT(gVect, p0, pg);
					SUBVECT(dVect, pd, p0);
					SUBVECT(bVect, p0, pb);
					SUBVECT(hVect, ph, p0);

					// trouver les moyennes entre les vecteurs antagonistes (gauche-droite) et (haut-bas)
					// les vecteurs résultants seronts appelés vectMoyenU et vectMoyenV
					ADDVECT(vectMoyenU, gVect, dVect);
					DIVVECT(vectMoyenU, ((k == 0) | (l == 0) | (k == NDD_ - 1) | (l == NDD_ - 1)) ? 1.0f : 2.0f);

					ADDVECT(vectMoyenV, bVect, hVect);
					DIVVECT(vectMoyenV, ((k == 0) | (l == 0) | (k == NDD_ - 1) | (l == NDD_ - 1)) ? 1.0f : 2.0f);

					// définir la normale en fonction des vecteurs moyens
					PRODVECT(normale, vectMoyenU, vectMoyenV);
					NORMALIZE(normale);

					// ajouter le sommet en cours
					//tex:
					m_sommets.push_back(u0*4.0f);
					m_sommets.push_back(v0*2.0f);
					//normales:
					m_sommets.push_back(normale.x);
					m_sommets.push_back(normale.y);
					m_sommets.push_back(normale.z);
					//positions:
					m_sommets.push_back(p0.x);
					m_sommets.push_back(p0.y);
					m_sommets.push_back(p0.z);

					m_indices.push_back(idx);
					idx++;
						
				}
			}
		}
	}
	GLenum  err = glGetError();

	// Notre Vertex Array Object - VAO
	glGenVertexArrays(1, &m_vao);
	// Un buffer pour les sommets
	glGenBuffers(1, &m_vbo);
	// Un buffer pour les indices des sommets des triangles
	glGenBuffers(1, &m_ibo);
	err = glGetError();
	// Lier 
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	err = glGetError();
	//Peupler
	m_taille = m_indices.size();
	glBufferData(GL_ARRAY_BUFFER, m_sommets.size() * sizeof(float), &m_sommets[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(float), &m_indices[0], GL_STATIC_DRAW);
	

	err = glGetError();
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (0));//texcoords
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (2 * sizeof(float)));//normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (5 * sizeof(float)));//positions
	glEnableVertexAttribArray(2);
	err = glGetError();

}

void CSurfaceBSplinaire::dessinerOpenGL()
{
	GLenum err = glGetError();
	glBindVertexArray(m_vao);
		glDrawElements(
			GL_QUADS,			 // mode
			m_taille,			// count
			GL_UNSIGNED_INT,    // type
			(void*)0            // element array buffer offset
		);
	err = glGetError();
}





////////////////////////////////////////////////////////////////////////
///
/// @fn CSurfaceBSplinaire::CoxDeBoor(float u,int i,int k,const float* Knots) 
/// Cette fonction permet de descendre récursivement le long des intervalles adjascents 
/// de façon à trouver quels intervalles jouent un rôle (return 1.0f) ou non 
/// return (0.0f) dans l'évaluation de la spline courante au point u
///
/// @param[in] u      : la valeur du paramètre d'évaluation (l'endroit sur la spline où 
///                     on veut évaluer la coordonnée.
/// @param[in] i      : le numéro de l'intervalle considéré
/// @param[in] k      : l'ordre courant du polynôme d'évaluation
/// @param[in] noeuds : un pointeur sur le vecteur nodal en cours (soit en U.. soit en V)
///
/// @return 1.0 si l'intervalle intervient dans l'évaluation du point considéré
///         0.0 s'il n'intervient pas.
///
////////////////////////////////////////////////////////////////////////
float CSurfaceBSplinaire::CoxDeBoor(float u,int i,int k,const float* noeuds) 
{
   // si l'ordre k = 1, alors...
	if(k == 1) {
	   // si u est à l'intérieur de l'intervalle [noeudCourant, noeudSuivant], retourner 1.0, sinon 0.0
	   if(u >= noeuds[i] && u <= noeuds[i+1])
		   return 1.0f;
	   else
		   return 0.0f;
	}
   
   // calcul des coefficients reliés aux deux différentes équations
	float Den1 = noeuds[i+k-1] - noeuds[i];  // ...
	float Den2 = noeuds[i+k] - noeuds[i+1];  // ...

   // les deux équations recursives vers les deux intervalles adjacents.
	float Eq1=0,Eq2=0;
   
	if(Den1>0) {
      // calcul de l'équation récursive 1
		Eq1 = ((u - noeuds[i]) / Den1) * CoxDeBoor(u, i, k-1, noeuds); //...
	}
	if(Den2>0) {
      // calcul de l'équation récursive 2
		Eq2 = ((u - noeuds[i+k]) / Den2) * CoxDeBoor(u, i+1, k-1, noeuds); // ...
	}
	return Eq1-Eq2;
}




Point CSurfaceBSplinaire::calculerU(float t,int row) {
	Point p = {0,0,0};

   // sommer les effets de tous les points de controles de la courbe
   // sur ce point pour obtenir le point évalué...
   for(unsigned int i=0;i!=nbPtsCtrlU_;++i) {

      // calculer l'effet de ce point sur la courbe
      float Val = CoxDeBoor(t, i, ordreU_, noeudsU_); 

      if(Val>0.001f) {

         // sommer l'effet du point de contrôle sur cette
         // partie de la courbe
         p.x += Val * points_[row*nbPtsCtrlU_ + i].x;
         p.y += Val * points_[row*nbPtsCtrlU_ + i].y;
         p.z += Val * points_[row*nbPtsCtrlU_ + i].z;
      }
   }

   return p;
}




Point CSurfaceBSplinaire::calculerV(float t,Point* pnts) {

	Point p = {0,0,0};

	// sommer les effets de tous les points de controles de la courbe
   // sur ce point pour obtenir  le point évalué...
	for(unsigned int i=0;i!=nbPtsCtrlV_;++i) {

      // calculer l'effet de ce point sur la courbe
		float Val = CoxDeBoor(t, i, ordreV_, noeudsV_);

		if(Val>0.001f) {

         // sommer l'effet du point de contrôle sur cette
         // partie de la courbe
			p.x += Val * pnts[i].x;
			p.y += Val * pnts[i].y;
			p.z += Val * pnts[i].z;
		}
	}

	return p;
}




Point CSurfaceBSplinaire::calculer(float u,float v) {


	Point* temp = new Point[nbPtsCtrlV_];
	for(unsigned int i=0;i!=nbPtsCtrlV_;++i) {
	
      // Considérer tout d'abord la surface somme un ensemble
      // de n courbes. Calculer un point sur chacune de ces courbes
      // et mémoriser le résultat
		temp[i] = calculerU(u,i);
	}

   // Après avoir obtenu ces points, on les utilise entre eux
   // pour former une nouvelle courbe sur laquelle on calcule
   // la valeur en direction v.
	Point p = calculerV(v,temp);

	delete [] temp;

	return p;
}




///////////////////////////////////////////////////////////////////////////////
///  private  MinU \n
///
///  retourne la valeur minimale de la plage valide du paramètre en u
///
///  @return float : la valeur minimale de la plage valide du paramètre en u
///
///  @author Frédéric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
float CSurfaceBSplinaire::MinU() 
{
   return noeudsU_[degreU_];
}




///////////////////////////////////////////////////////////////////////////////
///  private  MinV \n
///
///  retourne la valeur minimale de la plage valide du paramètre en v
///
///  @return float : la valeur minimale de la plage valide du paramètre en v
///
///  @author Frédéric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
float CSurfaceBSplinaire::MinV()
{
   return noeudsV_[degreV_];
}




///////////////////////////////////////////////////////////////////////////////
///  private  MaxU \n
///
///  retourne la valeur maximale de la plage valide du paramètre en u
///
///  @return float : la valeur maximale de la plage valide du paramètre en u
///
///  @author Frédéric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
float CSurfaceBSplinaire::MaxU()
{
   return noeudsU_[nbNoeudsU_-degreU_];
}




///////////////////////////////////////////////////////////////////////////////
///  private  MaxV \n
///
///  retourne la valeur maximale de la plage valide du paramètre en v
///
///  @return float : la valeur maximale de la plage valide du paramètre en v
///
///  @author Frédéric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
float CSurfaceBSplinaire::MaxV()
{
   return noeudsV_[nbNoeudsV_-degreV_];
}