#ifndef __FIRETRAP_H__
#define __FIRETRAP_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion de las hogueras

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





// Funcion FiretrapAnim();
void FiretrapAnim(void);
// Animacion de las hogueras



// Funcion FiretrapCamHide();
void FiretrapCamHide(u8 screen, u8 stage);
// Oculta las hogueras



// Funcion FiretrapCamShow();
void FiretrapCamShow(u8 screen, u8 stage);
// Muestra las hogueras






#endif
