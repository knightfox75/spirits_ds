#ifndef __AI_H__
#define __AI_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la IA de los NPC

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





// Funcion AiCheckRight();
extern u8 AiCheckRight(s32 x, s32 y, u8 add);
// Analiza lo que tienes a la derecha



// Funcion AiCheckLeft();
extern u8 AiCheckLeft(s32 x, s32 y, u8 add);
// Analiza lo que tienes a la izquierda



// Funcion AiCheckBottom();
extern u8 AiCheckBottom(s32 x, s32 y, u8 add);
// Analiza lo que tienes en los pies



// Funcion AiCheckTop();
u8 AiCheckTop(s32 x, s32 y, u8 add);
// Analiza lo que tienes en la cabeza





#endif
