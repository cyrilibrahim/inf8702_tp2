///////////////////////////////////////////////////////////////////////////////
///  @file Lumiere.h
///  @author  Fr�d�ric Plourde 
///  @brief   D�clare la classe CLumiere qui encapsule une glLight
///  @date    2007-12-11
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include  <GL/glew.h>


// define utilis� pour l'appel aux modificateurs ("modifier...") sans devoir sp�cifier les 3 composantes
#define NO_OP  -1     


///////////////////////////////////////////////////////////////////////////////
///  @class CLumiere
///  @brief Cette classe encapsule une lumi�re openGL
///  et permet de l'activer et d'en changer ais�ment les param�tres.
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
class CLumiere
{
public:
   /// constructeur par d�faut
   CLumiere(void);
   /// constructeur sp�cifique
   CLumiere(GLfloat KAr, GLfloat KAg, GLfloat KAb, GLfloat KDr, GLfloat KDg, GLfloat KDb, GLfloat KSr, GLfloat KSg, GLfloat KSb, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat posW = 1.0, bool estActivee = true, GLfloat spotDirX = 0.0, GLfloat spotDirY = 0.0, GLfloat spotDirZ = -1.0, GLfloat spotExp = 0.0, GLfloat spotCutoff = 180.0);
   /// destructeur par d�faut
   ~CLumiere(void);  

   //////////////////////////////////////////
   // Les Accesseurs...                     /
   //////////////////////////////////////////
   /// obtient les quatre composantes RGBA de KA
   inline void obtenirKA(GLfloat KA[3]) const;
   /// modifie les quatre composantes RGBA de KA
   inline void modifierKA(GLfloat KAr, GLfloat KAg, GLfloat KAb);
   /// obtient les quatre composantes RGBA de KD
   inline void obtenirKD(GLfloat KD[3]) const;
   /// modifie les quatre composantes RGBA de KD
   inline void modifierKD(GLfloat KDr, GLfloat KDg, GLfloat KDb);
   /// obtient les quatre composantes RGBA de KS
   inline void obtenirKS(GLfloat KS[3]) const;
   /// modifie les quatre composantes RGBA de KS
   inline void modifierKS(GLfloat KSr, GLfloat KSg, GLfloat KSb);
   /// obtient la position de la lumi�re
   inline void obtenirPos(GLfloat pos[4]) const;
   /// modifie la position de la lumi�re
   inline void modifierPos(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0);
   /// obtient la direction de la lumi�re
   inline void obtenirSpotDir(GLfloat spotDir[3]);
   /// modifie la direction de la lumi�re
   inline void modifierSpotDir(GLfloat x, GLfloat y, GLfloat z);
   /// obtient le spotCutoff
   inline GLfloat obtenirSpotCutOff();
   inline GLfloat obtenirSpotCutOffCos();
   /// obtient le spotExp
   inline GLfloat obtenirSpotExp();
   /// obtient le coefficient d'att�nuation constante
   inline GLfloat obtenirConsAtt();
   /// modifie le coeffcient d'att�nuation constante
   inline void modifierConstAtt(GLfloat constAtt);
   /// obtient le coefficient d'att�nuation lin�aire
   inline GLfloat obtenirLinAtt();
   /// modifie le coeffcient d'att�nuation lin�aire
   inline void modifierLinAtt(GLfloat linAtt);
   /// obtient le coefficient d'att�nuation quadratique
   inline GLfloat obtenirQuadAtt();
   /// modifie le coeffcient d'att�nuation quadratique
   inline void modifierQuadAtt(GLfloat quadAtt);
   /// obtient l'�tat de la lumi�re (allum�e ou �teinte)
   inline bool estAllumee() const;
   /// modifie l'�tat de la lumi�re � "allum�e"
   inline void allumer();
   /// modifie l'�tat de la lumi�re � "�teinte"
   inline void eteindre();

private:
   /// l'identifiant de la lumi�re OPENGL associ�e.
   GLenum lumKD_;

   /// indique si la lumi�re est allum�e (true) ou �teinte (false)   
   bool estAllumee_;  

   /// composante ambiante [R,G,B,A]
   GLfloat KA_[4];         
   /// composante diffuse [R,G,B,A]
   GLfloat KD_[4];      
   /// composante sp�culaire [R,G,B,A]
   GLfloat KS_[4];        

   /// position de la lumi�re [X,Y,Z,W]
   GLfloat pos_[4]; 

   /// la direction du "spot" [X,Y,Z] (le cas �ch�ant, sinon = (0,0,0)
   GLfloat spotDir_[3];

   /// l'exposant du faisceau du "spot" (le cas �ch�ant, sinon = 1.0)
   GLfloat spotExp_;

   /// l'angle de coupure du "spot" (le cas �ch�ant, sinon = 180)
   GLfloat spotCutoff_;

   GLfloat spotCutoffCos_;

   /// le coefficient d'att�nuantion constante (n'est PAS sp�cifiable � la construction)
   GLfloat constAtt_;

   /// le coefficient d'att�nuation lin�aire (n'est PAS sp�cifiable � la construction)
   GLfloat linAtt_;

   /// le coefficient d'att�nuation quadratique (n'est PAS sp�cifiable � la construction)
   GLfloat quadAtt_;
   
};


////////////////////////////////
// D�finitions inline
////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirKA \n
///
///  obtient les quatre composantes RGBA de KA
///
///  @param [in]       KA[3] les trois composantes RGB de KA
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::obtenirKA(GLfloat KA[3]) const
{
   KA[0] = KA_[0];
   KA[1] = KA_[1];
   KA[2] = KA_[2];
}


///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierKA \n
///
///  // modifie les quatre composantes RGBA de KA
///
///  @param [in]       KAr GLfloat    composante Rouge (peut �tre NO_OP pour garder ancienne valeur).
///  @param [in]       KAg GLfloat    composante Verte (peut �tre NO_OP pour garder ancienne valeur).
///  @param [in]       KAb GLfloat    composante Bleue (peut �tre NO_OP pour garder ancienne valeur).
///
///  @remark les arguments peuvent �tre mis � NO_OP � l'appel pour emp�cher qu'ils soient modifi�s.
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::modifierKA(GLfloat KAr, GLfloat KAg, GLfloat KAb)
{
   if (KAr != NO_OP) KA_[0] = KAr;
   if (KAg != NO_OP) KA_[1] = KAg;
   if (KAb != NO_OP) KA_[2] = KAb;
}


///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirKD \n
///
///  obtient les quatre composantes RGBA de KD
///
///  @param [in]       KD[3] les trois composantes RGB de KD
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::obtenirKD(GLfloat KD[3]) const
{
   KD[0] = KD_[0];
   KD[1] = KD_[1];
   KD[2] = KD_[2];
}


///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierKD \n
///
///  // modifie les quatre composantes RGBA de KD
///
///  @param [in]       KDr GLfloat    composante Rouge (peut �tre NO_OP pour garder ancienne valeur).
///  @param [in]       KDg GLfloat    composante Verte (peut �tre NO_OP pour garder ancienne valeur).
///  @param [in]       KDb GLfloat    composante Bleue (peut �tre NO_OP pour garder ancienne valeur).
///
///  @remark les arguments peuvent �tre mis � NO_OP � l'appel pour emp�cher qu'ils soient modifi�s.
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::modifierKD(GLfloat KDr, GLfloat KDg, GLfloat KDb)
{
   if (KDr != NO_OP) KD_[0] = KDr;
   if (KDg != NO_OP) KD_[1] = KDg;
   if (KDb != NO_OP) KD_[2] = KDb;
}


///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirKS \n
///
///  obtient les quatre composantes RGBA de KA
///
///  @param [in]       KS[3] les trois composantes RGB de KS
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::obtenirKS(GLfloat KS[3]) const
{
   KS[0] = KS_[0];
   KS[1] = KS_[1];
   KS[2] = KS_[2];
}


///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierKS \n
///
///  // modifie les quatre composantes RGBA de KS
///
///  @param [in]       KSr GLfloat    composante Rouge (peut �tre NO_OP pour garder ancienne valeur).
///  @param [in]       KSg GLfloat    composante Verte (peut �tre NO_OP pour garder ancienne valeur).
///  @param [in]       KSb GLfloat    composante Bleue (peut �tre NO_OP pour garder ancienne valeur).
///
///  @remark les arguments peuvent �tre mis � NO_OP � l'appel pour emp�cher qu'ils soient modifi�s.
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::modifierKS(GLfloat KSr, GLfloat KSg, GLfloat KSb)
{
   if (KSr != NO_OP) KS_[0] = KSr;
   if (KSg != NO_OP) KS_[1] = KSg;
   if (KSb != NO_OP) KS_[2] = KSb;
}


///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirPos \n
///
///  obtient les quatre composantes de la position de la lumi�re
///
///  @param [in]       pos[3] les quatre composantes euclidiennes de la position
///  @author Fr�d�ric Plourde 
///  @date   2008-03-31
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::obtenirPos(GLfloat pos[4]) const
{
   pos[0] = pos_[0];
   pos[1] = pos_[1];
   pos[2] = pos_[2];
   pos[3] = pos_[3];
}


///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierPos \n
///  Modifie la position de la lumi�re
///
///  @param [in]       x GLfloat    la composante en x
///  @param [in]       y GLfloat    la composante en y
///  @param [in]       z GLfloat    la composante en z
///  @param [in]       w GLfloat [=1.000000]    la composante en w (pour les lumi�res ponctuelles)
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-03-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::modifierPos(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
   pos_[0] = x;
   pos_[1] = y;
   pos_[2] = z;
   pos_[3] = w;
}


///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirSpotDir \n
///
///  obtient les trois composantes de la direction de la lumi�re
///
///  @param [in]       spotDir[3] les trois composantes euclidiennes de la direction
///  @author Fr�d�ric Plourde 
///  @date   2008-03-31
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::obtenirSpotDir(GLfloat spotDir[3])
{
   spotDir[0] = spotDir_[0];
   spotDir[1] = spotDir_[1];
   spotDir[2] = spotDir_[2];
}


///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierSpotDir \n
///  Modifie la direction d'illumination de la lumi�re (pour les spots)
///
///  @param [in]       x GLfloat    la composante en x
///  @param [in]       y GLfloat    la composante en y
///  @param [in]       z GLfloat    la composante en z
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2008-03-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::modifierSpotDir(GLfloat x, GLfloat y, GLfloat z)
{
   spotDir_[0] = x;
   spotDir_[1] = y;
   spotDir_[2] = z;
}



///////////////////////////////////////////////////////////////////////////////
///  inline public constant  estAllumee \n
///
///  Interroge l'�tat de la lumi�re (allum�e ou �teinte)
///
///  @return bool  : l'�tat de la lumi�re (true = allum�e, false = �teinte).
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline bool CLumiere::estAllumee() const
{
   return estAllumee_;
}




///////////////////////////////////////////////////////////////////////////////
///  inline public  allumer \n
///
///  Modifie l'�tat de la lumi�re � "allum�e"
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::allumer()
{
   estAllumee_ = true;
}



///////////////////////////////////////////////////////////////////////////////
///  inline public  eteindre \n
///
///  Modifie l'�tat de la lumi�re � "�teinte"
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::eteindre()
{
   estAllumee_ = false;
}



///////////////////////////////////////////////////////////////////////////////
///  global inline public  obtenirSpotCutOff \n
///
///  obtient le spotCutOff
///
///  @return GLfloat : le spotCutOff
///
///  @author Fr�d�ric Plourde 
///  @date   2008-03-31
///
///////////////////////////////////////////////////////////////////////////////
inline GLfloat CLumiere::obtenirSpotCutOff()
{
   return this->spotCutoff_;
}

inline GLfloat CLumiere::obtenirSpotCutOffCos()
{
   return this->spotCutoffCos_;
}

///////////////////////////////////////////////////////////////////////////////
///  global inline public  obtenirExp \n
///
///  obtient le spotExp
///
///  @return GLfloat : le spotExp
///
///  @author Fr�d�ric Plourde 
///  @date   2008-03-31
///
///////////////////////////////////////////////////////////////////////////////
inline GLfloat CLumiere::obtenirSpotExp()
{
	return this->spotExp_;
}


///////////////////////////////////////////////////////////////////////////////
///  global inline public  obtenirConsAtt \n
///
///  obtient le coefficient d'att�nuation constante
///
///  @return GLfloat : le coefficient d'att�nuation constante
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
inline GLfloat CLumiere::obtenirConsAtt()
{
   return constAtt_;
}





///////////////////////////////////////////////////////////////////////////////
///  global inline public  modifierConstAtt \n
///
///  modifie le coeffcient d'att�nuation constante
///
///  @param [in]     constAtt GLfloat  : le coeffcient d'att�nuation constante
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::modifierConstAtt(GLfloat constAtt)
{
   constAtt_ = constAtt;
}





///////////////////////////////////////////////////////////////////////////////
///  global inline public  obtenirLinAtt \n
///
///  obtient le coefficient d'att�nuation lin�aire
///
///  @return GLfloat : le coefficient d'att�nuation lin�aire
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
inline GLfloat CLumiere::obtenirLinAtt()
{
   return linAtt_;
}





///////////////////////////////////////////////////////////////////////////////
///  global inline public  modifierLinAtt \n
///
///  modifie le coeffcient d'att�nuation lin�aire
///
///  @param [in]   linAtt GLfloat  : le coeffcient d'att�nuation lin�aire
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::modifierLinAtt(GLfloat linAtt)
{
   linAtt_ = linAtt;
}





///////////////////////////////////////////////////////////////////////////////
///  global inline public  obtenirQuadAtt \n
///
///  obtient le coefficient d'att�nuation quadratique
///
///  @return GLfloat : le coefficient d'att�nuation quadratique
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
inline GLfloat CLumiere::obtenirQuadAtt()
{
   return quadAtt_;
}





///////////////////////////////////////////////////////////////////////////////
///  global inline public  modifierQuadAtt \n
///
///  modifie le coeffcient d'att�nuation quadratique
///
///  @param [in]  quadAtt GLfloat  :  le coeffcient d'att�nuation quadratique
///
///  @return Aucune
///
///  @author Fr�d�ric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
inline void CLumiere::modifierQuadAtt(GLfloat quadAtt)
{
   quadAtt_ = quadAtt;
}
