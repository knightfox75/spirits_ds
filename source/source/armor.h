#ifndef __ARMOR_H__
#define __ARMOR_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los NPC
	(Armadura)

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





// Funcion ArmorCamHide();
void ArmorCamHide(u8 screen, u8 stage);
// Oculta la Armadura



// Funcion ArmorCamShow();
void ArmorCamShow(u8 screen, u8 stage);
// Muestra la Armadura



// Funcion ArmorCheckRight();
extern u16 ArmorCheckRight(s8 add);
// Devuelve el tile mas significativo a la derecha



// Funcion ArmorCheckLeft();
extern u16 ArmorCheckLeft(s8 add);
// Devuelve el tile mas significativo a la izquierda



// Funcion ArmorCheckUp();
extern u16 ArmorCheckUp(s8 add);
// Devuelve el tile mas significativo encima



// Funcion ArmorCheckDown();
extern u16 ArmorCheckDown(s8 add);
// Devuelve el tile mas significativo de debajo



// Funcion ArmorFall();
void ArmorFall(void);
// Ejecuta: Caida



// Funcion ArmorStairs();
void ArmorStairs(void);
// Ejecuta: Muevete por las escaleras



// Funcion ArmorJump();
void ArmorJump(void);
// Ejecuta: Salta



// Funcion ArmorWalk();
void ArmorWalk(void);
// Ejecuta: Anda



// Funcion ArmorAdjustPosition();
void ArmorAdjustPosition(void);
// Ajusta la armadura para que no traviese ningun muro, puerta, etc.



// Funcion ArmorAnimation();
void ArmorAnimation(void);
// Animacion de la armadura



// Funcion ArmorMove();
void ArmorMove(void);
// Mueve a la armadura





#endif
