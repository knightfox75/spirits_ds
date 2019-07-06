#ifndef __HOWTOENGINE_H__
#define __HOWTOENGINE_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del manual - Engine

	Requiere DevkitARM
	Requiere NightFox's Lib

	Codigo por NightFox
	http://www.nightfoxandco.com
	Inicio 02 de Septiembre del 2011

	(c)2008 - 2012 NightFox & Co.

-------------------------------------------------
*/



/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes propietarios NDS
#include <nds.h>





// Funcion HowToEngine();
void HowToEngine(u16 camera);
// Engine de la simulacion



// Funcion HowToCamera();
void HowToCamera(s32 pos_x, s32 pos_y);
// Camara de la simulacion



// Funcion HowToUpdateBg();
void HowToUpdateBg(void);
// Actualiza los fondos en la simulacion



// Funcion HowToKeypadOverride();
void HowToKeypadOverride(void);
// Resetea el teclado



// TutorialGetTextPage();
void TutorialGetTextPage(void);
// Prepara el texto de la siguiente pagina del tutorial



// Funcion TutorialWritePage();
void TutorialWritePage(void);
// Escribe una pagina de texto






#endif