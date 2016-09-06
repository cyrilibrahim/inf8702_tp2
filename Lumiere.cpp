///////////////////////////////////////////////////////////////////////////////
///  @file Lumiere.cpp
///  @author  Fr�d�ric Plourde 
///  @brief   D�finit la classe CLumiere qui encapsule une glLight
///  @date    2007-12-11
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#include "Lumiere.h"



///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CLumiere \n
///
///  Cr�e une lumi�re openGL ponctuelle orient�e (w = 1.0),
///  centr�e � (0,0,0) et d'intensit� totale I = 1.0 pour
///  toutes les composantes.
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
CLumiere::CLumiere(void)
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

   pos_[0] = 0.0;
   pos_[1] = 0.0;
   pos_[2] = 0.0;
   pos_[3] = 1.0;
   estAllumee_ = true;

   spotDir_[0] =  0.0;
   spotDir_[1] =  0.0;
   spotDir_[2] = -1.0;

   spotExp_    = 0.0;
   spotCutoff_ = 180.0;

   constAtt_ = 1.0;
   linAtt_   = 0.0;
   quadAtt_  = 0.0;
}



///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CLumiere \n
///
///  Contructeur d'une lumi�re sp�cifique.
///
///  @param [in]       lumID   GLuint   l'Identifiant de la lumiere
///  @param [in]       KAr     composante ambiante (rouge)
///  @param [in]       KAg     composante ambiante (verte)
///  @param [in]       KAb     composante ambiante (bleue)
///  @param [in]       KDr     composante diffuse (rouge)
///  @param [in]       KDg     composante diffuse (verte)
///  @param [in]       KDb     composante diffuse (bleue)
///  @param [in]       KSr     composante sp�culaire (rouge)
///  @param [in]       KSg     composante sp�culaire (verte)
///  @param [in]       KSb     composante sp�culaire (bleue)
///  @param [in]       KEr     composante �mettrice (rouge)
///  @param [in]       KEg     composante �mettrice (verte)
///  @param [in]       KEb     composante �mettrice (bleue)
///  @param [in]       posX    position de la lumi�re en X
///  @param [in]       posY    position de la lumi�re en Y
///  @param [in]       posZ    position de la lumi�re en Z
///  @param [in]       posW = 1,000000  [=1,000000]  position de la lumi�re en W (directionnelle = 0.0, orient�e = 1.0)
///  @param [in]       estActivee indique si la lumi�re s'active (s'allume) d�s la construction
///  @param [in]       spotDirX   [0.0]     la direction en X du "spot" le cas �ch�ant
///  @param [in]       spotDirY   [0.0]     la direction en Y du "spot" le cas �ch�ant
///  @param [in]       spotDirZ   [-1.0]    la direction en Z du "spot" le cas �ch�ant
///  @param [in]       spotExp    [0.0]     l'exposant du "spot" le cas �ch�ant
///  @param [in]       spotCutoff [180.0]  l'angle de coupure du "spot" le cas �ch�ant
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
CLumiere::CLumiere(GLfloat KAr, GLfloat KAg, GLfloat KAb, GLfloat KDr, GLfloat KDg, GLfloat KDb, GLfloat KSr, GLfloat KSg, GLfloat KSb, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat posW, bool estActivee, GLfloat spotDirX, GLfloat spotDirY, GLfloat spotDirZ, GLfloat spotExp, GLfloat spotCutoff)
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

   pos_[0] = posX;
   pos_[1] = posY;
   pos_[2] = posZ;
   pos_[3] = posW;
   estAllumee_ = estActivee;

   spotDir_[0] =  spotDirX;
   spotDir_[1] =  spotDirY;
   spotDir_[2] =  spotDirZ;

   spotExp_    = spotExp;
   spotCutoff_  = spotCutoff;

   constAtt_ = 1.0;
   linAtt_   = 0.0;
   quadAtt_  = 0.0;
}



CLumiere::~CLumiere(void)
{
}