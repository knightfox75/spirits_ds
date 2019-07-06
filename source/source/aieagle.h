#ifndef __AIEAGLE_H__
#define __AIEAGLE_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la IA de la Aguila

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





// Funcion EagleAi();
void EagleAi(void);
// IA de la Aguila



// Funcion EagleAiTakeDecision();
void EagleAiTakeDecision(void);
// Toma las decisiones adecuadas



// Funcion AiEagleCheckBottom();
extern u8 AiEagleCheckBottom(s32 x, s32 y);
// Analiza los tiles inferiores



// Funcion AiEagleCheckTop();
extern u8 AiEagleCheckTop(s32 x, s32 y);
// Analiza los tiles superiores



// Funcion EagleAiFlyRight();
void EagleAiFlyRight(void);
// Vuela a la derecha



// Funcion EagleAiFlyLeft();
void EagleAiFlyLeft(void);
// Vuela a la izquierda



// Funcion EagleAiFlyDown();
void EagleAiFlyDown(void);
// Vuela hacia abajo



// Funcion EagleAiFlyUp();
void EagleAiFlyUp(void);
// Vuela hacia arriba





#endif
