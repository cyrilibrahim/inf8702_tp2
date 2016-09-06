///////////////////////////////////////////////////////////////////////////////
///  @file Var.cpp
///  @author  Frédéric Plourde 
///  @author  Félix Gingras Harvey
///  @brief   Déclare les VARIABLES GLOBALES du programme
///  @date    2007 - 2016
///  @version 2.0
///
///////////////////////////////////////////////////////////////////////////////
#include "Cst.h"
#include "Var.h"

SINGLETON_DECLARATION_CPP(CVar);

int     CVar::g_nWindowID;
int     CVar::currentW				= 1280;
int     CVar::currentH				= 720;

int     CVar::axesOn                = true;  
int     CVar::fogOn                 = true;   
int     CVar::animModeleOn          = false; 
int     CVar::rotAutoOn             = false;       
int     CVar::perlinOn              = true;  

int     CVar::minFilter             = 0;
int     CVar::magFilter             = 0;

bool    CVar::isPerspective         = true;
bool    CVar::isRotating			= false;
bool    CVar::mouseControl			= true;


std::vector<CLumiere*> CVar::lumieres = std::vector<CLumiere*>(CCst::nbLumieresOpenGL);
bool    CVar::pointLightOn			= true;
bool    CVar::dirLightOn			= true;
bool    CVar::spotLightOn			= true;
bool    CVar::showDebugInfo			= false;

double  CVar::theta                 = DEG2RAD(270.0f);
double  CVar::phi                   = DEG2RAD(90.0f);
double  CVar::rho                   = 30.0;  

float   CVar::x;
float   CVar::y;
float   CVar::z;

float   CVar::angleRotX             = 0.0f;
float   CVar::angleRotY             = 0.0f;
float   CVar::angleRotZ             = 0.0f;

bool    CVar::premierMouvement      = true;
double  CVar::dernierX				= 0; 
double  CVar::dernierY				= 0;
double	CVar::temps					= 0;

glm::mat4 CVar::vue					= glm::mat4();
glm::mat4 CVar::projection			= glm::mat4();

GLuint  CVar::listeAffModele;

GLuint  CVar::perlinTex             = 0;