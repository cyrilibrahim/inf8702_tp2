///////////////////////////////////////////////////////////////////////////////
///  @file Materiau.h
///  @author  Frédéric Plourde
///  @brief   Déclare la classe CMateriau qui encapsule un glMaterial
///  @date    2007-12-13
///  @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <GL/glew.h>

///////////////////////////////////////////////////////////////////////////////
///  @class CMateriau
///  @brief Cette classe encapsule un matériau openGL (GLMaterial) avec
///         toutes ses composantes de couleur et permet de l'appliquer
///         aisément
///
///  @author Frédéric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
class CMateriau
{
public:
   /// constructeur par défaut
   CMateriau(void);
   /// constructeur spécifique
   CMateriau(GLfloat KAr, GLfloat KAg, GLfloat KAb, GLfloat KAa, GLfloat KDr, GLfloat KDg, GLfloat KDb, GLfloat KDa, GLfloat KSr, GLfloat KSg, GLfloat KSb, GLfloat KSa, GLfloat KEr, GLfloat KEg, GLfloat KEb, GLfloat KEa, GLfloat shini = 1.0);
   /// destructeur par défaut
   ~CMateriau(void);

   //////////////////////////////////////////
   // Les Accesseurs...                     /
   //////////////////////////////////////////
   /// obtient les quatre composantes RGBA de KA
   inline void obtenirKA(GLfloat KA[4]) const;
   /// modifie les quatre composantes RGBA de KA
   inline void modifierKA(GLfloat KAr, GLfloat KAg, GLfloat KAb, GLfloat KAa);
   /// obtient les quatre composantes RGBA de KD
   inline void obtenirKD(GLfloat KD[4]) const;
   /// modifie les quatre composantes RGBA de KD
   inline void modifierKD(GLfloat KDr, GLfloat KDg, GLfloat KDb, GLfloat KDa);
   /// obtient les quatre composantes RGBA de KS
   inline void obtenirKS(GLfloat KS[4]) const;
   /// modifie les quatre composantes RGBA de KS
   inline void modifierKS(GLfloat KSr, GLfloat KSg, GLfloat KSb, GLfloat KSa);
   /// obtient les quatre composantes RGBA de KE
   inline void obtenirKE(GLfloat KE[4]) const;
   /// modifie les quatre composantes RGBA de KE
   inline void modifierKE(GLfloat KEr, GLfloat KEg, GLfloat KEb, GLfloat KEa);
   /// obtient l'exposant spéculaire
   inline GLfloat obtenirShininess();
   /// modifie l'exposant spéculaire 
   inline void modifierShininess(GLfloat shini);

private:
   /// composante ambiante [R,G,B,A]
   GLfloat KA_[4];         
   /// composante diffuse [R,G,B,A]
   GLfloat KD_[4];      
   /// composante spéculaire [R,G,B,A]
   GLfloat KS_[4];      
   /// composante émettrice [R,G,B,A]
   GLfloat KE_[4];

   /// l'exposant spéculaire du matériau (cos(phi)^shini)
   GLfloat shini_;
};


////////////////////////////////
// Définitions inline
////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirKA \n
///
///  obtient les quatre composantes RGBA de KA
///
///  @param [in]       KA GLfloat[]
///  @author Frédéric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CMateriau::obtenirKA(GLfloat KA[4]) const
{
   KA[0] = KA_[0];
   KA[1] = KA_[1];
   KA[2] = KA_[2];
   KA[3] = KA_[3];
}


///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierKA \n
///
///  // modifie les quatre composantes RGBA de KA
///
///  @param [in]       KAr GLfloat    composante Rouge
///  @param [in]       KAg GLfloat    composante Verte
///  @param [in]       KAb GLfloat    composante Bleue
///  @param [in]       KAa GLfloat    composante alpha
///
///  @author Frédéric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CMateriau::modifierKA(GLfloat KAr, GLfloat KAg, GLfloat KAb, GLfloat KAa)
{
   KA_[0] = KAr;
   KA_[1] = KAg;
   KA_[2] = KAb;
   KA_[3] = KAa;
}


///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirKD \n
///
///  obtient les quatre composantes RGBA de KD
///
///  @param [in]       KA GLfloat[]
///  @author Frédéric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CMateriau::obtenirKD(GLfloat KD[4]) const
{
   KD[0] = KD_[0];
   KD[1] = KD_[1];
   KD[2] = KD_[2];
   KD[3] = KD_[3];
}


///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierKD \n
///
///  // modifie les quatre composantes RGBA de KD
///
///  @param [in]       KDr GLfloat    composante Rouge 
///  @param [in]       KDg GLfloat    composante Verte
///  @param [in]       KDb GLfloat    composante Bleue
///  @param [in]       KDa GLfloat    composante alpha
///
///  @author Frédéric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CMateriau::modifierKD(GLfloat KDr, GLfloat KDg, GLfloat KDb, GLfloat KDa)
{
   KD_[0] = KDr;
   KD_[1] = KDg;
   KD_[2] = KDb;
   KD_[3] = KDa;
}


///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirKS \n
///
///  obtient les quatre composantes RGBA de KA
///
///  @param [in]       KA GLfloat[]
///  @author Frédéric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CMateriau::obtenirKS(GLfloat KS[4]) const
{
   KS[0] = KS_[0];
   KS[1] = KS_[1];
   KS[2] = KS_[2];
   KS[3] = KS_[3];
}


///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierKS \n
///
///  // modifie les quatre composantes RGBA de KS
///
///  @param [in]       KSr GLfloat    composante Rouge
///  @param [in]       KSg GLfloat    composante Verte
///  @param [in]       KSb GLfloat    composante Bleue
///  @param [in]       KSa GLfloat    composante alpha
///
///  @author Frédéric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CMateriau::modifierKS(GLfloat KSr, GLfloat KSg, GLfloat KSb, GLfloat KSa)
{
   KS_[0] = KSr;
   KS_[1] = KSg;
   KS_[2] = KSb;
   KS_[3] = KSa;
}


///////////////////////////////////////////////////////////////////////////////
///  inline public constant  obtenirKE \n
///
///  obtient les quatre composantes RGBA de KE
///
///  @param [in]       KE GLfloat[]
///  @author Frédéric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CMateriau::obtenirKE(GLfloat KE[4]) const
{
   KE[0] = KE_[0];
   KE[1] = KE_[1];
   KE[2] = KE_[2];
   KE[3] = KE_[3];
}


///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierKE \n
///
///  // modifie les quatre composantes RGBA de KE
///
///  @param [in]       KEr GLfloat    composante Rouge
///  @param [in]       KEg GLfloat    composante Verte
///  @param [in]       KEb GLfloat    composante Bleue
///  @param [in]       KEa GLfloat    composante alpha
///
///  @author Frédéric Plourde 
///  @date   2007-12-11
///
///////////////////////////////////////////////////////////////////////////////
inline void CMateriau::modifierKE(GLfloat KEr, GLfloat KEg, GLfloat KEb, GLfloat KEa)
{
   KE_[0] = KEr;
   KE_[1] = KEg;
   KE_[2] = KEb;
   KE_[3] = KEa;
}





///////////////////////////////////////////////////////////////////////////////
///  inline public  obtenirShininess \n
///
///  Obtient d'exposant spéculaire du matériau (cos(phi)^shini)
///
///  @return GLfloat : exposant spéculaire du matériau
///
///  @author Frédéric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
inline GLfloat CMateriau::obtenirShininess()
{
   return shini_;
}





///////////////////////////////////////////////////////////////////////////////
///  inline public  modifierShininess \n
///
///  Modifie l'exposant spéculaire du matériau (cos(phi)^shini)
///
///  @param [in]       shini GLfloat  : l'exposant spéculaire du matériau
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2007-12-13
///
///////////////////////////////////////////////////////////////////////////////
inline void CMateriau::modifierShininess(GLfloat shini)
{
   shini_ = shini;
}