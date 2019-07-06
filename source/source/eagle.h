#ifndef __EAGLE_H__
#define __EAGLE_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los NPC
	(Aguila)

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





// Funcion EagleCamHide();
void EagleCamHide(u8 screen, u8 stage);
// Oculta la Aguila



// Funcion EagleCamShow();
void EagleCamShow(u8 screen, u8 stage);
// Muestra la Aguila



// Funcion EagleCheckRight();
extern u16 EagleCheckRight(s8 add);
// Devuelve el tile mas significativo a la derecha



// Funcion EagleCheckLeft();
extern u16 EagleCheckLeft(s8 add);
// Devuelve el tile mas significativo a la izquierda



// Funcion EagleCheckUp();
extern u16 EagleCheckUp(s8 add);
// Devuelve el tile mas significativo encima



// Funcion EagleCheckDown();
extern u16 EagleCheckDown(s8 add);
// Devuelve el tile mas significativo de debajo



// Funcion EagleFly();
void EagleFly(void);
// Ejecuta: Vuela



// Funcion EagleAdjustPosition();
void EagleAdjustPosition(void);
// Ajusta la aguila para que no traviese ningun muro, puerta, etc.



// Funcion EagleAnimation();
void EagleAnimation(void);
// Animacion de la aguila



// Funcion EagleMove();
void EagleMove(void);
// Mueve a la aguila





#endif
