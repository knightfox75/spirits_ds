#ifndef __PRINCESS_H__
#define __PRINCESS_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los NPC
	(Princesa)

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





// Funcion PrincessCamHide();
void PrincessCamHide(u8 screen, u8 stage);
// Oculta la princesa



// Funcion PrincessCamShow();
void PrincessCamShow(u8 screen, u8 stage);
// Muestra la princesa



// Funcion PrincessCheckRight();
extern u16 PrincessCheckRight(s8 add);
// Devuelve el tile mas significativo a la derecha



// Funcion PrincessCheckLeft();
extern u16 PrincessCheckLeft(s8 add);
// Devuelve el tile mas significativo a la izquierda



// Funcion PrincessCheckUp();
extern u16 PrincessCheckUp(s8 add);
// Devuelve el tile mas significativo encima



// Funcion PrincessCheckDown();
extern u16 PrincessCheckDown(s8 add);
// Devuelve el tile mas significativo de debajo



// Funcion PrincessFall();
void PrincessFall(void);
// Ejecuta: Caida



// Funcion PrincessStairs();
void PrincessStairs(void);
// Ejecuta: Muevete por las escaleras



// Funcion PrincessJump();
void PrincessJump(void);
// Ejecuta: Salta



// Funcion PrincessWalk();
void PrincessWalk(void);
// Ejecuta: Anda



// Funcion PrincessAdjustPosition();
void PrincessAdjustPosition(void);
// Ajusta la princesa para que no traviese ningun muro, puerta, etc.



// Funcion PrincessAnimation();
void PrincessAnimation(void);
// Animacion de la princesa



// Funcion PrincessMove();
void PrincessMove(void);
// Mueve a la princesa





#endif
