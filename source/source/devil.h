#ifndef __DEVIL_H__
#define __DEVIL_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion del gato y diablo

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





// Funcion DevilMain();
void DevilMain(void);
// Gestion del diablo



// Funcion DevilTimer
void DevilTimer(void);
// Temporizador de actuacion del Diablo



// Funcion DevilGetPos();
extern bool DevilGetPos(void);
// Busca una posicion valida para aparecer



// Funcion DevilCheckBox();
extern bool DevilCheckBox(s32 pos_x, s32 pos_y, s16 width, s16 height);
// Verifica si el cuadrante esta limpio o toca algun muro



// Funcion DevilAnimation
void DevilAnimation(void);
// Control de la animacion del diablo



// Funcion ArrowShot();
void ArrowShot(void);
// Procesa el disparo de la felcha



// Funcion CameraDevilHide();
void CameraDevilHide(u8 screen, u8 stage);
// Oculta al diablo y la flecha



// Funcion CameraDevilShow();
void CameraDevilShow(u8 screen, u8 stage);
// Muestra al diablo y la flecha



// Funcion DevilCamHide();
void DevilCamHide(u8 screen, u8 stage);
// Oculta al diablo si es necesario



// Funcion DevilCamShow();
void DevilCamShow(u8 screen, u8 stage);
// Muestra al diablo si es necesario



// Funcion ArrowCamHide();
void ArrowCamHide(u8 screen, u8 stage);
// Oculta la flecha del diablo si es necesario



// Funcion ArrowCamShow();
void ArrowCamShow(u8 screen, u8 stage);
// Muestra la flecha del diablo si es necesario






#endif
