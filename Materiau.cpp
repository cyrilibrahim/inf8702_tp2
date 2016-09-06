///////////////////////////////////////////////////////////////////////////////
///  @file Materiau.cpp
///  @author  Fr�d�ric Plourde 
///  @brief   D�finit la classe CMateriau qui encapsule un glMaterial
///  @date    2007-12-13
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#include "Materiau.h"



///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CMateriau \n
///
///  Cr�e un materiau openGL (GLMaterial) par d�faut (blanc pour toutes
///  les composantes)
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
CMateriau::CMateriau(void)
{
   KA_[0] = 1.0;
   KA_[1] = 1.0;
   KA_[2] = 1.0;
   KA_[3] = 1.0;

   KD_[0] = 1.0;
   KD_[1] = 1.0;
   KD_[2] = 1.0;
   KD_[3] = 1.0;

   KS_[0] = 1.0;
   KS_[1] = 1.0;
   KS_[2] = 1.0;
   KS_[3] = 1.0;

   KE_[0] = 1.0;
   KE_[1] = 1.0;
   KE_[2] = 1.0;
   KE_[3] = 1.0;

   shini_ = 1.0;
}



///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CMateriau \n
///
///  Contructeur d'une lumi�re sp�cifique.
///
///  @param [in]       lumKD GLenum   l'Identifiant openGL de la lumi�re associ�e.
///  @param [in]       KAr GLfloat    composante ambiante (rouge)
///  @param [in]       KAg GLfloat    composante ambiante (verte)
///  @param [in]       KAb GLfloat    composante ambiante (bleue)
///  @param [in]       KAa GLfloat    composante ambiante (alpha)
///  @param [in]       KDr GLfloat    composante diffuse (rouge)
///  @param [in]       KDg GLfloat    composante diffuse (verte)
///  @param [in]       KDb GLfloat    composante diffuse (bleue)
///  @param [in]       KDa GLfloat    composante diffuse (alpha)
///  @param [in]       KSr GLfloat    composante sp�culaire (rouge)
///  @param [in]       KSg GLfloat    composante sp�culaire (verte)
///  @param [in]       KSb GLfloat    composante sp�culaire (bleue)
///  @param [in]       KSa GLfloat    composante sp�culaire (alpha)
///  @param [in]       KEr GLfloat    composante �mettrice (rouge)
///  @param [in]       KEg GLfloat    composante �mettrice (verte)
///  @param [in]       KEb GLfloat    composante �mettrice (bleue)
///  @param [in]       KEa GLfloat    composante �mettrice (alpha)
///  @param [in]       shini GLfloat[1.0]  l'exposant sp�culaire du mat�riau
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
CMateriau::CMateriau(GLfloat KAr, GLfloat KAg, GLfloat KAb, GLfloat KAa, GLfloat KDr, GLfloat KDg, GLfloat KDb, GLfloat KDa, GLfloat KSr, GLfloat KSg, GLfloat KSb, GLfloat KSa, GLfloat KEr, GLfloat KEg, GLfloat KEb, GLfloat KEa, GLfloat shini)
{
   KA_[0] = KAr;
   KA_[1] = KAg;
   KA_[2] = KAb;
   KA_[3] = 1.0;

   KD_[0] = KDr;
   KD_[1] = KDg;
   KD_[2] = KDb;
   KD_[3] = 1.0;

   KS_[0] = KSr;
   KS_[1] = KSg;
   KS_[2] = KSb;
   KS_[3] = 1.0;

   KE_[0] = KEr;
   KE_[1] = KEg;
   KE_[2] = KEb;
   KE_[3] = 1.0;

   shini_ = shini;
}



///////////////////////////////////////////////////////////////////////////////
///  public destructor  ~CMateriau \n
///
///  Destructeur par d�faut (vide)
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
CMateriau::~CMateriau(void)
{
}
