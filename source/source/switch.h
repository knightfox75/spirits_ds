#ifndef __SWITCH_H__
#define __SWITCH_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del sistema de interruptores

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




// Funcion SwitchGetSpriteId();
extern u16 SwitchGetSpriteId(u8 screen);
// Devuelve una ID de sprite libre



// Funcion SwitchFreeSpriteId();
void SwitchFreeSpriteId(u8 screen, u16 id);
// Libera la ID del sprite



// Funcion CameraSwitchHide();
void CameraSwitchHide(u8 screen, u8 stage);
// Gestiona si desaparecen los interruptores en alguna camara



// Funcion CameraSwitchShow();
void CameraSwitchShow(u8 screen, u8 stage);
// Gestiona si aparecen los interruptores en alguna camara





#endif