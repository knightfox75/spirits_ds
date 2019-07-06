#ifndef __DRAGON_H__
#define __DRAGON_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del evento
	"Guarida del Dragon"

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





// Funcion DragonEyeMain();
void DragonEyeMain(void);
// Gestion del evento "Guarida del Dragon"



// Funcion DragonEyeAnimation();
void DragonEyeAnimation(void);
// Animacion de los ojos el dragon



// Funcion DragonEyeCamHide();
void DragonEyeCamHide(u8 screen, u8 stage);
// Oculta los ojos del dragon



// Funcion DragonEyeCamShow();
void DragonEyeCamShow(u8 screen, u8 stage);
// Muestra los ojos del dragon





#endif
