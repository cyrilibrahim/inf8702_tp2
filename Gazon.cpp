///////////////////////////////////////////////////////////////////////////////
///  @file Gazon.cpp
///  @author  Fr�d�ric Plourde 
///  @brief   D�finit la classe CGazon qui encapsule une patch bsplinaire antialias�e
///  @date    2007-12-11
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////

#include "Gazon.h"

///////////////////////////////////////////////////////////////////////////////
///  public constructor  CGazon \n
///  Construit un skybox au moyen d'une seule texture (seule possibilit� pour un skybox)
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
CGazon::CGazon(char * nomFichierTexture, float largeurGazon, float longueurGazon):
CModele3DAbstrait(1.0, nomFichierTexture, TYPE_TEXTURE2D, true, true),
CSurfaceBSplinaire(8, 4, CCst::Points, 12, 8, CCst::VNodalU, CCst::VNodalV, 40)
{

}



///////////////////////////////////////////////////////////////////////////////
///  public destructor  ~CGazon \n
///  Destructeur par d�faut d'un skybox
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
CGazon::~CGazon(void)
{
}


///////////////////////////////////////////////////////////////////////////////
///  public static  dessiner \n
///  Fonction � impl�menter absolument si on veut voir appara�tre quelque chose !
///  cette fonction sera appel�e par la classe de base (CModele3DAbstrait) par 
///  l'entremise d'une pointeur de fonction pass� � la construction. On mettra ici
///  uniquement le graphisme associ� � l'objet (i.e.  glBegin()...glVertex(), etc...)
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-02-20
///
///////////////////////////////////////////////////////////////////////////////
void CGazon::dessiner()
{
	appliquerTextures();
	dessinerOpenGL();
}


void CGazon::appliquerTextures()
{
	// texturer le gazon
	textures_[0]->appliquer(WRAP_S | WRAP_T | MIN_FILTER | MAG_FILTER,
		GL_REPEAT, GL_REPEAT, 0,
		CCst::mapFilters[CVar::minFilter], CCst::mapFilters[CVar::magFilter],
		0, 0,
		0, 0,
		0, 0,
		true, GL_TEXTURE0);


}


