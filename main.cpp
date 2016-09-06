///////////////////////////////////////////////////////////////////////////////
///  @file main.cpp
///  @brief   le main du programme ProjetNuanceur pour le cours INF8702 de Polytechnique
///  @author  Frédéric Plourde (2007)
///  @author  Félix Gingras Harvey (2016)
///  @date    2007 / 2016
///  @version 2.0
///
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/matrix_inverse.hpp>
#include <gtx/transform.hpp>
#include <gtx/matrix_cross_product.hpp>
#include "textfile.h"
#include "GrilleQuads.h"
#include "Cst.h"
#include "Var.h"
#include "NuanceurProg.h"
#include "Materiau.h"
#include "Texture2D.h"
#include "Modele3DOBJ.h"
#include "Skybox.h"
#include "Gazon.h"


///////////////////////////////////////////////
// LES OBJETS                                //
///////////////////////////////////////////////

// les programmes de nuanceurs
CNuanceurProg progNuanceurCarte("Nuanceurs/carteSommets.glsl", "Nuanceurs/carteFragments.glsl", false);
CNuanceurProg progNuanceurSkybox("Nuanceurs/skyBoxSommets.glsl", "Nuanceurs/skyBoxFragments.glsl", false);
CNuanceurProg progNuanceurGazon("Nuanceurs/gazonSommets.glsl", "Nuanceurs/gazonFragments.glsl", false);

// les différents matériaux utilisés dans le programme
CMateriau front_mat_ambiant_model(0.1, 0.1, 0.1, 1.0, 0.9, 0.8, 1.0, 1.0, 0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0, 100.0);
CMateriau back_mat_ambiant_model(0.1, 0.1, 0.1, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 5.0);
CMateriau nurbs_mat_ambiant_model(0.8, 0.8, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);

// Les objets 3D graphiques (à instancier plus tard parce que les textures demandent le contexte graphique)
CGrilleQuads *cartePoly;
CGazon * gazon;
//CGrilleQuads *gazon;
CSkybox *skybox;


// Vecteurs caméra
glm::vec3 cam_position = glm::vec3(0, 0, -25);
glm::vec3 direction;
glm::vec3 cam_right;
glm::vec3 cam_up;

// Angle horizontale de la caméra: vers les Z
float horizontalAngle = 0.f;
// Angle vertical: vers l'horizon
float verticalAngle = 0.f;
// "Field of View" initial
float initialFoV = 45.0f;

float vitesseCamera = 15.0f; // 15 unités / seconde
float vitesseSouris = 0.05f;

double sourisX = 0;
double sourisY = 0;

///////////////////////////////////////////////
// PROTOTYPES DES FONCTIONS DU MAIN          //
///////////////////////////////////////////////
void initialisation (void);
void dessinerSkybox(void);
void dessinerScene(void);
void dessinerCarte(void);
void dessinerGazon(void);
void attribuerValeursLumieres(GLuint progNuanceur);
void clavier(GLFWwindow *fenetre, int touche, int scancode, int action, int mods);
void mouvementSouris(GLFWwindow* window, double deltaT, glm::vec3& direction, glm::vec3& right, glm::vec3& up);
void redimensionnement(GLFWwindow *fenetre, int w, int h);
void rafraichirCamera(GLFWwindow* window, double deltaT);
void compilerNuanceurs();
void chargerBruitPerlin();

// le main
int main(int argc,char *argv[])
{
	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERREUR: impossible d'initialiser GLFW3\n");
		return 1;
	}

	GLFWwindow* fenetre = glfwCreateWindow(CVar::currentW , CVar::currentH, "INF8702 - Labo", NULL, NULL);
	if (!fenetre) {
		fprintf(stderr, "ERREUR: impossibe d'initialiser la fenêtre avec GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwSetWindowPos(fenetre, 600, 100);

	// Rendre le contexte openGL courrant celui de la fenêtre
	glfwMakeContextCurrent(fenetre);

	// Combien d'updates d'écran on attend après l'appel à glfwSwapBuffers()
	// pour effectivement échanger les buffers et retourner
	glfwSwapInterval(1);

	// Définir la fonction clavier
	glfwSetKeyCallback(fenetre, clavier);

	// Reset mouse position for next frame
	glfwSetCursorPos(fenetre, CVar::currentW / 2, CVar::currentH / 2);

	// Définire le comportement du curseur
	glfwSetInputMode(fenetre, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Définir la fonction de redimensionnement
	glfwSetWindowSizeCallback(fenetre, redimensionnement);
	
	// vérification de la version 4.X d'openGL
	glewInit();
	if (glewIsSupported("GL_VERSION_4_5"))
		printf("Pret pour OpenGL 4.5\n\n");
	else {
		printf("\nOpenGL 4.5 n'est pas supporte! \n");
		exit(1);
	}

	// Specifier le context openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // recueillir des informations sur le système de rendu
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Materiel de rendu graphique: %s\n", renderer);
	printf("Plus récente vversion d'OpenGL supportee: %s\n\n", version);

    GLint max;
    glGetIntegerv(GL_MAX_TEXTURE_UNITS, &max);
    printf("GL_MAX_TEXTURE_UNITS = %d\n", max);

    glGetIntegerv(GL_MAX_VARYING_FLOATS, &max);
    printf("GL_MAX_VARYING_FLOATS = %d\n\n", max);


	if (!glfwExtensionSupported ("GL_EXT_framebuffer_object") ){
        printf("Objets 'Frame Buffer' NON supportes! :( ... Je quitte !\n");
        exit (1);
    } else {
        printf("Objets 'Frame Buffer' supportes :)\n\n");
    }


    // compiler et lier les nuanceurs
    compilerNuanceurs();

    // initialisation de variables d'état openGL et création des listes
    initialisation();
	
	double dernierTemps = glfwGetTime();
	int nbFrames = 0;
	
    // boucle principale de gestion des evenements
	while (!glfwWindowShouldClose(fenetre))
	{
		glfwPollEvents();

		//Temps ecoule en secondes depuis l'initialisation de GLFW
		double temps = glfwGetTime();
		double deltaT = temps - CVar::temps;
		CVar::temps = temps;

		nbFrames++;
		// Si ça fait une seconde que l'on a pas affiché les infos
		if (temps - dernierTemps >= 1.0){
			if (CVar::showDebugInfo){
				printf("%f ms/frame\n", 1000.0 / double(nbFrames));
				printf("Position: (%f,%f,%f)\n", cam_position.x, cam_position.y, cam_position.z);
			}
			nbFrames = 0;
			dernierTemps += 1.0;
		}
		
		// Rafraichir le point de vue selon les input clavier et souris
		rafraichirCamera(fenetre, deltaT);
		
		// Afficher nos modèlests
		dessinerScene();

		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(fenetre);

	}
	// close GL context and any other GLFW resources
	glfwTerminate();

    // on doit faire le ménage... !
	delete gazon;
	delete CVar::lumieres[ENUM_LUM::LumPonctuelle];
	delete CVar::lumieres[ENUM_LUM::LumDirectionnelle];
	delete CVar::lumieres[ENUM_LUM::LumSpot];
	delete cartePoly;
	delete skybox;
	

    // le programme n'arrivera jamais jusqu'ici
    return EXIT_SUCCESS;
}



// initialisation d'openGL
void initialisation (void) {
	////////////////////////////////////////////////////
	// CONSTRUCTION DES LUMIÈRES
	////////////////////////////////////////////////////

	// LUMIÈRE PONCTUELLE ORKENTÉE (enum : LumPonctuelle - 0)
	CVar::lumieres[ENUM_LUM::LumPonctuelle] = new CLumiere(0.1f, 0.1f, 0.1f, 0.4f, 0.4f, 0.9f, 0.7f, 0.7f, 0.7f, 0.0f, -3.0f, -10.0f, 1.0f, true);
	CVar::lumieres[ENUM_LUM::LumPonctuelle]->modifierConstAtt(0.4);
	CVar::lumieres[ENUM_LUM::LumPonctuelle]->modifierLinAtt(0.0);
	CVar::lumieres[ENUM_LUM::LumPonctuelle]->modifierQuadAtt(0.0);

	// LUMIÈRE SPOT (enum : LumSpot - 1)
	CVar::lumieres[ENUM_LUM::LumSpot] = new CLumiere(0.2f, 0.2f, 0.2f, 0.9f, 0.8f, 0.4f, 1.0f, 1.0f, 1.0f, 10.0f, 10.0f, -10.0f, 1.0f, true, -0.5f, -1.0f, 1.0f, 0.f, 30.0);

	// LUMIÈRE DIRECTIONNELLE (enum : LumDirectionnelle - 2)
	CVar::lumieres[ENUM_LUM::LumDirectionnelle] = new CLumiere(0.1f, 0.1f, 0.1f, 0.8f, 0.8f, 0.8f, 0.4f, 0.4f, 0.4f, 5.0f, -5.0f, 5.0f, 0.0f, true);

	// les noms de fichier de la texture de la carte.
	std::vector<char*> texturesCarte;
	texturesCarte.push_back("textures/cartePolyRecto.bmp");
	texturesCarte.push_back("textures/cartePolyVerso.bmp");

	// charger la texture de perlin
	chargerBruitPerlin();

	cartePoly = new CGrilleQuads(&texturesCarte, 20.f, 12.f, 25, 25, 1.0f, false, true);
	// lier les attributs des nuanceurs
	//glBindAttribLocation(progNuanceurCarte.getProg(), CCst::indexTangente, "Tangent");

	// construire le skybox avec les textures
	skybox = new CSkybox("textures/uffizi_cross_LDR.bmp", CCst::grandeurSkybox);

	// Construire un plan pour le gazon
	//gazon = new CGrilleQuads("textures/gazon.bmp", 2000.f, 500.f, 50, 50, 1.0f, true, false);
	//gazon->modifierRepeatTexture(true);

	//gazon->modifierEchelle(10.0f);
	gazon = new CGazon("textures/gazon.bmp", 1.0f, 1.0f);
	

	// fixer la couleur de fond
	glClearColor(0.0, 0.0, 0.5, 1.0);

	// activer les etats openGL
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	// fonction de profondeur
	glDepthFunc(GL_LEQUAL);
}

void dessinerCarte(void)
{
	GLenum err = 0;
	progNuanceurCarte.activer();
	// Création d'une matrice-modèle.
	// Défini la translation/rotaion/grandeur du modèle.
	float scale = cartePoly->obtenirEchelle();
	glm::vec3 s(1, 1, 1);
	glm::mat4 scalingMatrix = glm::scale(s);

	glm::mat4 rotationMatrix;
	
	glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	float a = glm::radians(180.f);
	rotationMatrix *= glm::rotate(a, rotationAxis);

	if (CVar::isRotating)
	{
		a = CVar::temps;
		rotationAxis = glm::vec3(0.f, 1.0f, 0.f);
		rotationMatrix *= glm::rotate(a, rotationAxis);
	}
	
	glm::vec3 t(0.f, 0.f, 0.f);
	glm::mat4 translationMatrix = glm::translate(t);

	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	// Matrice Model-Vue-Projection:
	glm::mat4 mv = CVar::vue * modelMatrix;

	// Matrice Model-Vue-Projection:
	glm::mat4 mvp = CVar::projection * CVar::vue * modelMatrix;

	// Matrice pour normales (world matrix):
	glm::mat3 mv_n = glm::inverseTranspose(glm::mat3(CVar::vue * modelMatrix));
	err = glGetError();
	GLuint handle;

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "M");
	glUniformMatrix4fv(handle, 1, GL_FALSE, &modelMatrix[0][0]);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "V");
	glUniformMatrix4fv(handle, 1, GL_FALSE, &CVar::vue[0][0]);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "MVP");
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mvp[0][0]);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "MV");
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mv[0][0]);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "MV_N");
	glUniformMatrix3fv(handle, 1, GL_FALSE, &mv_n[0][0]);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "time");
	glUniform1f(handle, CVar::temps);
	
	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "animOn");
	glUniform1i(handle, (int)CVar::animModeleOn);
	err = glGetError();

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "perlinOn");
	glUniform1i(handle, (int)CVar::perlinOn);
	err = glGetError();

	////////////////    Fournir les valeurs de matériaux: //////////////////////////
	GLfloat component[4];
	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "frontMat.Ambient");
	front_mat_ambiant_model.obtenirKA(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "frontMat.Diffuse");
	front_mat_ambiant_model.obtenirKD(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "frontMat.Specular");
	front_mat_ambiant_model.obtenirKS(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "frontMat.Exponent");
	front_mat_ambiant_model.obtenirKE(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "frontMat.Shininess");
	glUniform1f(handle, front_mat_ambiant_model.obtenirShininess());

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "backMat.Ambient");
	back_mat_ambiant_model.obtenirKA(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "backMat.Diffuse");
	back_mat_ambiant_model.obtenirKD(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "backMat.Specular");
	back_mat_ambiant_model.obtenirKS(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "backMat.Exponent");
	back_mat_ambiant_model.obtenirKE(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "backMat.Shininess");
	glUniform1f(handle, back_mat_ambiant_model.obtenirShininess());

	/////////////////////////////////////////////////////////////////////////////////////

	attribuerValeursLumieres(progNuanceurCarte.getProg());
	err = glGetError();
	// ajouts d'autres uniforms
	if (CVar::lumieres[ENUM_LUM::LumPonctuelle]->estAllumee()) 
		progNuanceurCarte.uniform1("pointLightOn", 1);
	else
		progNuanceurCarte.uniform1("pointLightOn", 0);

	if (CVar::lumieres[ENUM_LUM::LumDirectionnelle]->estAllumee())
		progNuanceurCarte.uniform1("dirLightOn", 1);
	else
		progNuanceurCarte.uniform1("dirLightOn", 0);

	if (CVar::lumieres[ENUM_LUM::LumSpot]->estAllumee()) 
		progNuanceurCarte.uniform1("spotLightOn", 1);
	else
		progNuanceurCarte.uniform1("spotLightOn", 0);
	err = glGetError();

	//glVertexAttrib3f(CCst::indexTangente, 0.0, 0.0, 1.0);
	handle = glGetUniformLocation(progNuanceurCarte.getProg(), "Tangent");
	glUniform3f(handle, -1.0f, 1.0f, 0.0f);

	err = glGetError();
	cartePoly->dessiner();
	err = glGetError();
}

void dessinerGazon()
{
	progNuanceurGazon.activer();
	// Création d'une matrice-modèle.
	glm::vec3 t1(-3.5f, -1.5f, 0.f);
	glm::mat4 translationMatrix1 = glm::translate(t1);

	glm::vec3 s(CCst::largeurGazon, CCst::longueurGazon, CCst::hauteurGazon);
	glm::mat4 scalingMatrix = glm::scale(s);

	glm::mat4 rotationMatrix;

	glm::vec3 rotationAxis(1.0f, 0.0f, 0.0f);
	float a = glm::radians(-90.0f);
	rotationMatrix = glm::rotate(a, rotationAxis);

	glm::vec3 t2(0.f, -20.f, 0.f);
	glm::mat4 translationMatrix2 = glm::translate(t2);

	glm::mat4 modelMatrix = translationMatrix2 * rotationMatrix * scalingMatrix * translationMatrix1;

	// Matrice Model-Vue-Projection:
	glm::mat4 mv = CVar::vue * modelMatrix;

	// Matrice Model-Vue-Projection:
	glm::mat4 mvp = CVar::projection * CVar::vue * modelMatrix;

	// Matrice pour normales (world matrix):
	glm::mat3 mv_n = glm::inverseTranspose(glm::mat3(CVar::vue * modelMatrix));
	GLuint handle;

	handle = glGetUniformLocation(progNuanceurGazon.getProg(), "M");
	glUniformMatrix4fv(handle, 1, GL_FALSE, &modelMatrix[0][0]);

	handle = glGetUniformLocation(progNuanceurGazon.getProg(), "V");
	glUniformMatrix4fv(handle, 1, GL_FALSE, &CVar::vue[0][0]);

	handle = glGetUniformLocation(progNuanceurGazon.getProg(), "MVP");
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mvp[0][0]);

	handle = glGetUniformLocation(progNuanceurGazon.getProg(), "MV");
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mv[0][0]);

	handle = glGetUniformLocation(progNuanceurGazon.getProg(), "MV_N");
	glUniformMatrix3fv(handle, 1, GL_FALSE, &mv_n[0][0]);


	////////////////    Fournir les valeurs de matériaux: //////////////////////////
	GLfloat component[4];
	handle = glGetUniformLocation(progNuanceurGazon.getProg(), "Material.Ambient");
	nurbs_mat_ambiant_model.obtenirKA(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurGazon.getProg(), "Material.Diffuse");
	nurbs_mat_ambiant_model.obtenirKD(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurGazon.getProg(), "Material.Specular");
	nurbs_mat_ambiant_model.obtenirKS(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurGazon.getProg(), "Material.Exponent");
	nurbs_mat_ambiant_model.obtenirKE(component);
	glUniform4fv(handle, 1, component);

	handle = glGetUniformLocation(progNuanceurGazon.getProg(), "Material.Shininess");
	glUniform1f(handle, nurbs_mat_ambiant_model.obtenirShininess());

	///////////////////////////////////////////////////////////////////////////////////

	attribuerValeursLumieres(progNuanceurGazon.getProg());
	
	// ajouts d'autres uniforms
	if (CVar::lumieres[ENUM_LUM::LumPonctuelle]->estAllumee())
		progNuanceurGazon.uniform1("pointLightOn", 1);
	else
		progNuanceurGazon.uniform1("pointLightOn", 0);

	if (CVar::lumieres[ENUM_LUM::LumDirectionnelle]->estAllumee())
		progNuanceurGazon.uniform1("dirLightOn", 1);
	else
		progNuanceurGazon.uniform1("dirLightOn", 0);

	if (CVar::lumieres[ENUM_LUM::LumSpot]->estAllumee())
		progNuanceurGazon.uniform1("spotLightOn", 1);
	else
		progNuanceurGazon.uniform1("spotLightOn", 0);

	gazon->dessiner();
}

void dessinerSkybox()
{

	// Ajouter une modification dans la matrice Modèle pour éliminer les artéfacts de perspectives.
	// ...
	progNuanceurSkybox.activer();

	glm::vec3 s(CCst::grandeurSkybox, CCst::grandeurSkybox, CCst::grandeurSkybox);
	glm::mat4 scalingMatrix = glm::scale(s);

	// Effectuer la rotation pour être dans le même sense que le gazon et la caméra (Y+ = UP)
	glm::mat4 rotationMatrix;
	glm::vec3 rotationAxis(1.0f, 0.0f, 0.0f);
	float a = glm::radians(-90.f);
	rotationMatrix = glm::rotate(a, rotationAxis);

	glm::mat4 translationMatrix = glm::translate(glm::vec3(0.0f,0.0f,0.0f));
	
	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	// Matrice Model-Vue-Projection:
	glm::mat4 mvp = CVar::projection * CVar::vue * modelMatrix;

	GLuint handle;

	handle = glGetUniformLocation(progNuanceurSkybox.getProg(), "MVP");
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mvp[0][0]);

	skybox->dessiner();
}


void dessinerScene()
{
	// À compléter
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	// Décommenter pour afficher!
	// dessinerSkybox();

	dessinerGazon();

	// Décommenter pour afficher!
	// dessinerCarte();


    // flush les derniers vertex du pipeline graphique
    glFlush();
}



///////////////////////////////////////////////////////////////////////////////
///  global public  clavier \n
///
///  fonction de rappel pour la gestion du clavier
///
///  @param [in]       pointeur GLFWwindow	Référence à la fenetre GLFW
///  @param [in]       touche	int			ID de la touche
///  @param [in]       scancode int			Code spécifique à la plateforme et à l'ID
///  @param [in]       action	int			Action appliquée à la touche
///  @param [in]       mods		int			Modifier bits
///
///  @return Aucune
///
///  @author Félix G. Harvey 
///  @date   2016-06-03
///
///////////////////////////////////////////////////////////////////////////////
void clavier(GLFWwindow* fenetre, int touche, int scancode, int action, int mods)
{

	switch (touche) {
	case GLFW_KEY_Q:{
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(fenetre, GL_TRUE);
		break;
	}
	case  GLFW_KEY_ESCAPE:{
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(fenetre, GL_TRUE);
		break;
	}
	case  GLFW_KEY_P:{
		if (action == GLFW_PRESS){
			if (CVar::isPerspective)
				CVar::isPerspective = false;
			else
				CVar::isPerspective = true;
		}
		break;
	}
	case  GLFW_KEY_R:{
		if (action == GLFW_PRESS){
			if (CVar::isRotating)
				CVar::isRotating = false;
			else
				CVar::isRotating = true;
		}
		break;
	}
	case  GLFW_KEY_I:{
		if (action == GLFW_PRESS){
			if (CVar::showDebugInfo)
				CVar::showDebugInfo = false;
			else
				CVar::showDebugInfo = true;
		}
		break;
	}
	case  GLFW_KEY_E:{
		if (action == GLFW_PRESS){
			if (CVar::animModeleOn)
				CVar::animModeleOn = false;
			else
				CVar::animModeleOn = true;
		}
		break;
	}
	case  GLFW_KEY_X: {
		if (action == GLFW_PRESS) {
			if (CVar::perlinOn)
				CVar::perlinOn = false;
			else
				CVar::perlinOn = true;
		}
		break;
	}
	case  GLFW_KEY_C:{
		if (action == GLFW_PRESS){
			if (CVar::mouseControl){
				CVar::mouseControl = false;
				glfwSetInputMode(fenetre, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}	
			else{
				CVar::mouseControl = true;
				glfwSetInputMode(fenetre, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			}		
		}

		break;
	}
	case  GLFW_KEY_1:{
		if (action == GLFW_PRESS){
			if (CVar::lumieres[ENUM_LUM::LumDirectionnelle]->estAllumee())
				CVar::lumieres[ENUM_LUM::LumDirectionnelle]->eteindre();
			else
				CVar::lumieres[ENUM_LUM::LumDirectionnelle]->allumer();
		}

		break;
	}
	case  GLFW_KEY_2:{
		if (action == GLFW_PRESS){
			if (CVar::lumieres[ENUM_LUM::LumPonctuelle]->estAllumee())
				CVar::lumieres[ENUM_LUM::LumPonctuelle]->eteindre();
			else
				CVar::lumieres[ENUM_LUM::LumPonctuelle]->allumer();
		}
		break;
	}
	case  GLFW_KEY_3:{
		if (action == GLFW_PRESS){
			if (CVar::lumieres[ENUM_LUM::LumSpot]->estAllumee())
				CVar::lumieres[ENUM_LUM::LumSpot]->eteindre();
		else
			CVar::lumieres[ENUM_LUM::LumSpot]->allumer();
		}
		break;
	}

	// permuter le minFilter
	case GLFW_KEY_N:
	{
		if (action == GLFW_PRESS) {
			if (CVar::minFilter >= 5)
				CVar::minFilter = 0;
			else
				CVar::minFilter++;
		}
		break;
	}

	// permuter le magFilter
	case GLFW_KEY_M:
	{
		if (action == GLFW_PRESS) {
			if (CVar::magFilter >= 1)
				CVar::magFilter = 0;
			else
				CVar::magFilter++;
		}
		break;
	}

	}

}




///////////////////////////////////////////////////////////////////////////////
///  global public  redimensionnement \n
///
///  fonction de rappel pour le redimensionnement de la fenêtre graphique
///
///  @param [in]       w GLsizei    nouvelle largeur "w" en pixels
///  @param [in]       h GLsizei    nouvelle hauteur "h" en pixels
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2007-12-14
///
///////////////////////////////////////////////////////////////////////////////
void redimensionnement(GLFWwindow* fenetre, int w, int h)
{
    CVar::currentW = w;
    CVar::currentH = h;
    glViewport(0, 0, w, h);
    dessinerScene();
}

void attribuerValeursLumieres(GLuint progNuanceur)
{
	GLenum error = glGetError();

	//Handle pour attribut de lumiere
	GLuint li_handle;

	li_handle = glGetUniformLocation(progNuanceur, "dirLightOn");
	error = glGetError();
	glUniform1i(li_handle, CVar::lumieres[ENUM_LUM::LumDirectionnelle]->estAllumee());
	error = glGetError();
	li_handle = glGetUniformLocation(progNuanceur, "pointLightOn");
	glUniform1i(li_handle, CVar::lumieres[ENUM_LUM::LumPonctuelle]->estAllumee());
	li_handle = glGetUniformLocation(progNuanceur, "spotLightOn");
	glUniform1i(li_handle, CVar::lumieres[ENUM_LUM::LumSpot]->estAllumee());
	error = glGetError();

	// Fournir les valeurs d'éclairage au nuanceur.
	// Les directions et positions doivent être en référenciel de caméra. 
	for (int i = 0; i < CVar::lumieres.size(); i++)
	{
		//Placeholders pour contenir les valeurs
		GLfloat temp3[3];
		GLfloat temp4[4];
		glm::vec4 pos;
		glm::vec4 pos_cam;

		//Creer un descripteur basé sur l'index de lumière
		std::string begin = "Lights[";
		int l_idx = i;
		std::string end = "]";
		std::string light_desc = begin + std::to_string(l_idx) + end;

		li_handle = glGetUniformLocation(progNuanceur, (light_desc + ".Ambient").c_str());
		CVar::lumieres[i]->obtenirKA(temp3);
		glUniform3fv(li_handle, 1, &temp3[0]);
		error = glGetError();

		li_handle = glGetUniformLocation(progNuanceur, (light_desc + ".Diffuse").c_str());
		CVar::lumieres[i]->obtenirKD(temp3);
		glUniform3fv(li_handle, 1, &temp3[0]);

		li_handle = glGetUniformLocation(progNuanceur, (light_desc + ".Specular").c_str());
		CVar::lumieres[i]->obtenirKS(temp3);
		glUniform3fv(li_handle, 1, &temp3[0]);

		li_handle = glGetUniformLocation(progNuanceur, (light_desc + ".Position").c_str());
		CVar::lumieres[i]->obtenirPos(temp4);

		// Transformer ici la direction/position de la lumière vers un référenciel de caméra
		pos = glm::vec4(temp4[0], temp4[1], temp4[2], temp4[3]);
		pos = CVar::vue * pos;

		temp4[0] = pos.x;
		temp4[1] = pos.y;
		temp4[2] = pos.z;
		temp4[3] = pos.w;
		glUniform4fv(li_handle, 1, &temp4[0]);

		li_handle = glGetUniformLocation(progNuanceur, (light_desc + ".SpotDir").c_str());
		CVar::lumieres[i]->obtenirSpotDir(temp3);
		//Transformer ici la direction du spot
		pos = glm::vec4(temp3[0], temp3[1], temp3[2], 0.0f);
		pos = CVar::vue * pos;
		temp3[0] = pos.x;
		temp3[1] = pos.y;
		temp3[2] = pos.z;
		glUniform3fv(li_handle, 1, &temp3[0]);

		li_handle = glGetUniformLocation(progNuanceur, (light_desc + ".SpotExp").c_str());
		glUniform1f(li_handle, CVar::lumieres[i]->obtenirSpotExp());

		li_handle = glGetUniformLocation(progNuanceur, (light_desc + ".SpotCutoff").c_str());
		glUniform1f(li_handle, CVar::lumieres[i]->obtenirSpotCutOff());

		li_handle = glGetUniformLocation(progNuanceur, (light_desc + ".Attenuation").c_str());
		glUniform3f(li_handle,
			CVar::lumieres[i]->obtenirConsAtt(),
			CVar::lumieres[i]->obtenirLinAtt(),
			CVar::lumieres[i]->obtenirQuadAtt());
	}

}


//////////////////////////////////////////////////////////
////////////  FONCTIONS POUR LA SOURIS ///////////////////
//////////////////////////////////////////////////////////

void mouvementSouris(GLFWwindow* window, double deltaT, glm::vec3& direction, glm::vec3& right, glm::vec3& up)
{
	if (CVar::mouseControl)
	{
		// Déplacement de la souris:
		// Taille actuelle de la fenetre
		int mid_width, mid_height;
		glfwGetWindowSize(window, &mid_width, &mid_height);
		mid_width /= 2;
		mid_height /= 2;

		// Get mouse position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		// Reset mouse position for next frame
		glfwSetCursorPos(window, mid_width, mid_height);

		// Nouvelle orientation
		horizontalAngle += vitesseSouris * deltaT * float(mid_width - xpos);
		verticalAngle += vitesseSouris * deltaT * float(mid_height - ypos);
	}
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		);

	// Right vector
	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
		);

	// Up vector : perpendicular to both direction and right
	up = glm::cross(right, direction);
}

//////////////////////////////////////////////////////////
////////////  FONCTIONS POUR LA CAMÉRA ///////////////////
//////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
///  global public  rafraichirCamera \n
///
///  Fonction de gestion de la position de la caméra en coordonnées sphériques.
///  Elle s'occuper de trouver les coordonnées x et y de la caméra à partir 
///  des theta et phi courants, puis fixe dans openGL la position de la caméra
///  à l'aide de gluLookAt().
///
///  @return Aucune
///
///  @author Frédéric Plourde 
///  @date   2007-12-14
///
///////////////////////////////////////////////////////////////////////////////
void rafraichirCamera(GLFWwindow* fenetre, double deltaT)
{
	mouvementSouris(fenetre, deltaT, direction, cam_right, cam_up);

	// Move forward
	if (glfwGetKey(fenetre, GLFW_KEY_W) == GLFW_PRESS){
		cam_position += direction * (float)deltaT * vitesseCamera;
	}
	// Move backward
	if (glfwGetKey(fenetre, GLFW_KEY_S) == GLFW_PRESS){
		cam_position -= direction * (float)deltaT * vitesseCamera;
	}
	// Strafe right
	if (glfwGetKey(fenetre, GLFW_KEY_D) == GLFW_PRESS){
		cam_position += cam_right * (float)deltaT * vitesseCamera;
		}
	// Strafe left
	if (glfwGetKey(fenetre, GLFW_KEY_A) == GLFW_PRESS){
		cam_position -= cam_right * (float)deltaT * vitesseCamera;
	}

	//Matrice de projection:
	float ratio = (float)CVar::currentW / (float)CVar::currentH;
	if (CVar::isPerspective){
		// Caméra perspective: 
		// 
		
		CVar::projection = glm::perspective(glm::radians(45.0f), ratio, 0.001f, 3000.0f);
	}
	else
	{
		// Caméra orthographique :
		CVar::projection = glm::ortho(-5.0f*ratio, 5.0f*ratio,-5.0f, 5.0f, 0.001f, 3000.0f); // In world coordinates
	}

	// Matrice de vue:
	CVar::vue = glm::lookAt(
		cam_position,				// Position de la caméra
		cam_position + direction,   // regarde vers position + direction
		cam_up                  // Vecteur "haut"
		);
}


//////////////////////////////////////////////////////////
//////////  FONCTIONS POUR LES NUANCEURS /////////////////
//////////////////////////////////////////////////////////
void compilerNuanceurs () 
{
    // on compiler ici les programmes de nuanceurs qui furent prédéfinis

	progNuanceurCarte.compilerEtLier();
	progNuanceurCarte.enregistrerUniformInteger("frontColorMap", CCst::texUnit_0);
	progNuanceurCarte.enregistrerUniformInteger("backColorMap", CCst::texUnit_1);
	progNuanceurCarte.enregistrerUniformInteger("normalMap", CCst::texUnit_2);

	progNuanceurSkybox.compilerEtLier();
	progNuanceurSkybox.enregistrerUniformInteger("colorMap", CCst::texUnit_0);

	progNuanceurGazon.compilerEtLier();
	progNuanceurGazon.enregistrerUniformInteger("colorMap", CCst::texUnit_0);
}

void chargerBruitPerlin()
{
	// construire la texture
	// calculer la texture de bruit de Perlin
	float* texNoise2D = make2DNoiseArray(CCst::noiseWidth, CCst::noiseHeight, 32, 1);

	// calculer la "normal map"
	vect3D* texNormal2D = compute2DNormalTexture(texNoise2D, CCst::noiseWidth, CCst::noiseHeight);

	// créer la texture
	glGenTextures(1, &CVar::perlinTex);
	glBindTexture(GL_TEXTURE_2D, CVar::perlinTex);

	// aiguiller openGL vers la zone mémoire contenant le graphisme de la texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, CCst::noiseWidth, CCst::noiseHeight, 0, GL_RGB, GL_FLOAT, texNormal2D);

	// libérer l'espace mémoire maintenant que la texture est copiée dans la mémoire vidéo
	if (texNoise2D) {
		free(texNoise2D);
	}

	if (texNormal2D) {
		free(texNormal2D);
	}
}
