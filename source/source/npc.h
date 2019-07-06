#ifndef __NPC_H__
#define __NPC_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los NPC

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





// Funcion CameraNpcHide();
void CameraNpcHide(u8 screen, u8 stage);
// Oculta los NPC



// Funcion CameraNpcShow();
void CameraNpcShow(u8 screen, u8 stage);
// Muestra los NPC



// Funcion NpcMain();
void NpcMain(void);
// Control general de los NPC





#endif
