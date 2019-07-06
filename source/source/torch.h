#ifndef __TORCH_H__
#define __TORCH_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del sistema de antorchas

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




// Funcion TorchGetSpriteId();
extern u16 TorchGetSpriteId(u8 screen);
// Devuelve una ID de sprite libre



// Funcion TorchFreeSpriteId();
void TorchFreeSpriteId(u8 screen, u16 id);
// Libera la ID del sprite



// Funcion CameraTorchHide();
void CameraTorchHide(u8 screen, u8 stage);
// Gestiona si desaparecen los antorchas en alguna camara



// Funcion CameraTorchShow();
void CameraTorchShow(u8 screen, u8 stage);
// Gestiona si aparecen los antorchas en alguna camara



// Funcion TochAnimation();
void TorchAnimation(void);
// Animacion de las antorchas





#endif