#ifndef __LAMP_H__
#define __LAMP_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion de las lamparas

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



// Funcion LampCamHide();
void LampCamHide(u8 screen, u8 stage);
// Oculta las lamparas



// Funcion LampCamShow();
void LampCamShow(u8 screen, u8 stage);
// Muestra las lamparas



// Funcion LampEvent();
void LampEvent(void);
// Gestiona los eventos de las lamparas



// Funcion LampActivation();
void LampActivation(void);
// Gestiona la activacion de las lamparas



// Funcion LampTimer();
void LampTimer(void);
// Temporizador de las lamparas activas



// Funcion LampFall();
void LampFall(void);
// Procesa la caida de la lampara



// Funcion LampAnimation();
void LampAnimation(void);
// Procesa la animacion de las lamparas



#endif
