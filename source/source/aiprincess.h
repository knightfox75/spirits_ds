#ifndef __AIPRINCESS_H__
#define __AIPRINCESS_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la IA de la Princesa

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





// Funcion PrincessAi();
void PrincessAi(void);
// IA de la princesa



// Funcion PrincessAiDetectFall();
void PrincessAiDetectFall(void);
// Detecta si estas cayendo y ajusta la IA



// Funcion PrincessAiFall();
void PrincessAiFall(void);
// IA, princesa cayendo



// Funcion PrincessAiWalkRight();
void PrincessAiWalkRight(void);
// IA, princesa andando a la derecha



// Funcion PrincessAiWalkLeft();
void PrincessAiWalkLeft(void);
// IA, princesa andando a la izquierda



// Funcion PrincessAiCheckStairs();
void PrincessAiCheckStairs(u8 floor, u8 ceil);
// Analisis de IA, escaleras y bajada de escalones



// Funcion PrincessAiJump();
void PrincessAiJump(void);
// IA, princesa saltando



// Funcion PrincessAiDownStairs();
void PrincessAiDownStairs(void);
// IA, princesa bajando las escaleras



// Funcion PrincessAiUpStairs();
void PrincessAiUpStairs(void);
// IA, princesa subiendo las escaleras



// Funcion PrincessAiUpSteepsRight();
void PrincessAiUpSteepsRight(void);
// IA, princesa subiendo los escalones a la derecha



// Funcion PrincessAiUpSteepsLeft();
void PrincessAiUpSteepsLeft(void);
// IA, princesa subiendo los escalones a la izquierda



// Funcion PrincessAiDownSteeps();
void PrincessAiDownSteeps(void);
// IA, princesa bajando los escalones



// Funcion PrincessAiStage7();
void PrincessAiStage7(void);
// IA, movimiento especial para pasar del stage 7 al 6





#endif
