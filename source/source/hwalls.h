#ifndef __HWALLS_H__
#define __HWALLS_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion de muros mobiles

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



// Funcion HwallGetSpriteId();
extern u16 HwallGetSpriteId(u8 screen);
// Devuelve una ID de sprite libre



// Funcion HwallFreeSpriteId();
void HwallFreeSpriteId(u8 screen, u16 id);
// Libera la ID del sprite



// Funcion CameraHwallHide();
void CameraHwallHide(u8 screen, u8 stage);
// Gestiona la visivilidad de todos los muros mobiles

// Funcion CameraHwallShow();
void CameraHwallShow(u8 screen, u8 stage);
// Gestiona la visivilidad de todos los muros mobiles



// Funcion HwallCam00Hide();
void HwallCam00Hide(u8 screen, u8 stage);
// Visivilidad del Muro nº00 - Stage 16

// Funcion HwallCam00Show();
void HwallCam00Show(u8 screen, u8 stage);
// Visivilidad del Muro nº00 - Stage 16



// Funcion HwallCam01Hide();
void HwallCam01Hide(u8 screen, u8 stage);
// Visivilidad del Muro nº01 - Stage 16

// Funcion HwallCam01Show();
void HwallCam01Show(u8 screen, u8 stage);
// Visivilidad del Muro nº01 - Stage 16

// Funcion HwallCam02Hide();
void HwallCam02Hide(u8 screen, u8 stage);
// Visivilidad del Muro nº02 - Stage 16

// Funcion HwallCam02Show();
void HwallCam02Show(u8 screen, u8 stage);
// Visivilidad del Muro nº02 - Stage 16



// Funcion HwallCam03Hide();
void HwallCam03Hide(u8 screen, u8 stage);
// Visivilidad del Muro nº03 - Stage 17

// Funcion HwallCam03Show();
void HwallCam03Show(u8 screen, u8 stage);
// Visivilidad del Muro nº03 - Stage 17



#endif
