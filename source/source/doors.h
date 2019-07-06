#ifndef __DOORS_H__
#define __DOORS_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion de las puertas

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



// Funcion DoorGetSpriteId();
extern u16 DoorGetSpriteId(u8 screen);
// Devuelve una ID de sprite libre



// Funcion DoorFreeSpriteId();
void DoorFreeSpriteId(u8 screen, u16 id);
// Libera la ID del sprite



// Funcion CameraDoorHide();
void CameraDoorHide(u8 screen, u8 stage);
// Gestiona la visivilidad de todas las puertas

// Funcion CameraDoorShow();
void CameraDoorShow(u8 screen, u8 stage);
// Gestiona la visivilidad de todas las puertas



// Funcion DoorCam00Hide();
void DoorCam00Hide(u8 screen, u8 stage);
// Visivilidad de la Puerta nº00 - Stage 01

// Funcion DoorCam00Show();
void DoorCam00Show(u8 screen, u8 stage);
// Visivilidad de la Puerta nº00 - Stage 01



// Funcion DoorCam01Hide();
void DoorCam01Hide(u8 screen, u8 stage);
// Visivilidad de la Puerta nº01 - Stage 04

// Funcion DoorCam01Show();
void DoorCam01Show(u8 screen, u8 stage);
// Visivilidad de la Puerta nº01 - Stage 04



// Funcion DoorCam02Hide();
void DoorCam02Hide(u8 screen, u8 stage);
// Visivilidad de la Puerta nº02 - Stage 05

// Funcion DoorCam02Show();
void DoorCam02Show(u8 screen, u8 stage);
// Visivilidad de la Puerta nº02 - Stage 05



// Funcion DoorCam03Hide();
void DoorCam03Hide(u8 screen, u8 stage);
// Visivilidad de la Puerta nº03 - Stage 07

// Funcion DoorCam03Show();
void DoorCam03Show(u8 screen, u8 stage);
// Visivilidad de la Puerta nº03 - Stage 07



// Funcion DoorCam04Hide();
void DoorCam04Hide(u8 screen, u8 stage);
// Visivilidad de la Puerta nº04 - Stage 14

// Funcion DoorCam04Show();
void DoorCam04Show(u8 screen, u8 stage);
// Visivilidad de la Puerta nº04 - Stage 14



// Funcion DoorCam05Hide();
void DoorCam05Hide(u8 screen, u8 stage);
// Visivilidad de la Puerta nº04 - Stage 14

// Funcion DoorCam05Show();
void DoorCam05Show(u8 screen, u8 stage);
// Visivilidad de la Puerta nº04 - Stage 14



// Funcion DoorCam06Hide();
void DoorCam06Hide(u8 screen, u8 stage);
// Visivilidad de la Puerta nº06 - Stage 17

// Funcion DoorCam06Show();
void DoorCam06Show(u8 screen, u8 stage);
// Visivilidad de la Puerta nº06 - Stage 17





#endif
