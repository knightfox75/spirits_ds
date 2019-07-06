#ifndef __CREDITS_H__
#define __CREDITS_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Creditos

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




// Funcion Credits();
void Credits(void);
// Nucleo de los creditos



// Funcion CreditsLoadFiles();
void CreditsLoadFiles(void);
// Carga los archivos



// Funcion CreditsCreate();
void CreditsCreate(void);
// Crea los fondos y demas elementos



// Funcion CreditsLoadText();
extern u32 CreditsLoadText(const char* file);
// Carga el archivo de creditos



// Funcion CreditsKernel();
void CreditsKernel(u32 height);
// Motor de los creditos



// Funcion CreditsBlending();
void CreditsBlending(void);
// Efecto blending





#endif
