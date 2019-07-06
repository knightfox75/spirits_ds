#ifndef __CAMERA_H__
#define __CAMERA_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del sistema de camaras

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



// Funcion CameraStart();
void CameraStart(void);
// Parametros iniciales de las dos camaras



// Funcion CameraMain();
void CameraMain(void);
// Control general de las camaras



// Funcion CameraNormal();
void CameraNormal(void);
// Sistema de camaras en condiciones normales



// Funcion CameraMinimap();
void CameraMinimap(void);
// Sistema de camaras con el minimapa



// Funcion CameraView();
void CameraView(u8 screen, s32 pos_x, s32 pos_y);
// Analiza que Sprites estan en pantalla



// Funcion GetStage();
extern u8 GetStage(s32 pos_x, s32 pos_y);
// Devuelve la pantalla correspondiente a las coordenadas dadas



// Funcion CameraUpdateBg();
void CameraUpdateBg(void);
// Actualiza los fondos en pantalla



// Funcion CameraUpdateBg8bits();
void CameraUpdateBg8bits(u8 screen);
// Actualizacion de fondo en modo 8 bits



// Funcion CameraUpdateBgHq();
void CameraUpdateBgHq(u8 screen);
// Actualizacion de fondo en modo HQ



// Funcion SubcamControl();
void SubcamControl(void);
// Control del Objeto que sigue la subcam



#endif