#ifndef __ENEMY_H__
#define __ENEMY_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de los enemigos

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



// Funcion EnemyMain();
void EnemyMain(void);
// Engine del control de los enemigos



// Funcion GoulAi();
void GoulAi(void);
// IA de los Gouls



// Funcion PhantomAi();
void PhantomAi(void);
// IA de los Fantasmas


// Funcion WolfAi();
void WolfAi(void);
// IA de los hombres-lobo



// Funcion GoulMove();
void GoulMove(void);
// Mueve a todos los Gouls



// Funcion PhantomMove();
void PhantomMove(void);
// Mueve a todos los Fantasmas



// Funcion WolfMove();
void WolfMove(void);
// Mueve a todos los Lobos



// Funcion EnemyGetSpriteId();
extern u16 EnemyGetSpriteId(u8 screen);
// Devuelve una ID de sprite libre



// Funcion EnemyFreeSpriteId();
void EnemyFreeSpriteId(u8 screen, u16 id);
// Libera la ID del sprite



// Funcion CameraGoulHide();
void CameraGoulHide(u8 screen, u8 stage);
// Gestiona si desaparecen los gouls en alguna camara



// Funcion CameraGoulShow();
void CameraGoulShow(u8 screen, u8 stage);
// Gestiona si aparecen los gouls en alguna camara



// Funcion CameraPhantomHide();
void CameraPhantomHide(u8 screen, u8 stage);
// Gestiona si desaparecen los fantasmas en alguna camara



// Funcion CameraPhantomShow();
void CameraPhantomShow(u8 screen, u8 stage);
// Gestiona si aparecen los fantasmas en alguna camara



// Funcion CameraWolfHide();
void CameraWolfHide(u8 screen, u8 stage);
// Gestiona si desaparecen los lobos en alguna camara



// Funcion CameraWolfShow();
void CameraWolfShow(u8 screen, u8 stage);
// Gestiona si aparecen los lobos en alguna camara



#endif
