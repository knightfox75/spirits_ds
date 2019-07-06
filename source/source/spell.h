#ifndef __SPELL_H__
#define __SPELL_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del hechizo

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





// Funcion SpellCamHide();
void SpellCamHide(u8 screen, u8 stage);
// Oculta el hechizo si es necesario



// Funcion SpellCamShow();
void SpellCamShow(u8 screen, u8 stage);
// Muestra el hechizo si es necesario



// Funcion SpellMain();
void SpellMain(void);
// Nucleo de ejecucion del lanzamiento de hechizos



// Funcion SpellShot();
void SpellShot(void);
// Gestiona si puedes disparar el hechizo



// Funcion SpellCreate();
void SpellCreate(void);
// Crea el hechizo y lanzalo hacia adelante



// Funcion SpellMove();
void SpellMove(void);
// Mueve el hechizo





#endif
