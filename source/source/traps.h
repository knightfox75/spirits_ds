#ifndef __TRAPS_H__
#define __TRAPS_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion de las trampas

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



// Funcion TrapGetSpriteId();
extern u16 TrapGetSpriteId(u8 screen);
// Devuelve una ID de sprite libre



// Funcion TrapFreeSpriteId();
void TrapFreeSpriteId(u8 screen, u16 id);
// Libera la ID del sprite



// Funcion CameraTrapHide();
void CameraTrapHide(u8 screen, u8 stage);
// Gestiona la visivilidad de todos las trampas mobiles

// Funcion TrapRearm();
void TrapRearm(bool force);
// Rearma las trampas fuera del campo de vision

// Funcion CameraTrapShow();
void CameraTrapShow(u8 screen, u8 stage);
// Gestiona la visivilidad de todos las trampas mobiles



// Funcion TrapCam00Hide();
void TrapCam00Hide(u8 screen, u8 stage);
// Visivilidad de la Trampa nº00 - Stage 16

// Funcion TrapCam00Show();
void TrapCam00Show(u8 screen, u8 stage);
// Visivilidad de la Trampa nº00 - Stage 16

// Funcion TrapRearm00();
void TrapRearm00(bool force);
// Rearma la Trampa nº00 - Stage 16



// Funcion TrapCam01Hide();
void TrapCam01Hide(u8 screen, u8 stage);
// Visivilidad de la Trampa nº01 - Stage 17

// Funcion TrapCam01Show();
void TrapCam01Show(u8 screen, u8 stage);
// Visivilidad de la Trampa nº01 - Stage 17

// Funcion TrapRearm01();
void TrapRearm01(bool force);
// Rearma la Trampa nº01 - Stage 17

// Funcion TrapRearm02();
void TrapRearm02(bool force);
// Rearma la Trampa nº02 - Stage 17





#endif
