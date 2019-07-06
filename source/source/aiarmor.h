#ifndef __AIARMOR_H__
#define __AIARMOR_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la IA de la Armadura

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





// Funcion ArmorAi();
void ArmorAi(void);
// IA de la armadura



// Funcion ArmorAiDetectFall();
void ArmorAiDetectFall(void);
// Detecta si estas cayendo y ajusta la IA



// Funcion ArmorAiFall();
void ArmorAiFall(void);
// IA, armadura cayendo



// Funcion ArmorAiWalkRight();
void ArmorAiWalkRight(void);
// IA, armadura andando a la derecha



// Funcion ArmorAiWalkLeft();
void ArmorAiWalkLeft(void);
// IA, armadura andando a la izquierda



// Funcion ArmorAiCheckStairs();
void ArmorAiCheckStairs(u8 floor, u8 ceil);
// Analisis de IA, escaleras y bajada de escalones



// Funcion ArmorAiJump();
void ArmorAiJump(void);
// IA, armadura saltando



// Funcion ArmorAiDownStairs();
void ArmorAiDownStairs(void);
// IA, armadura bajando las escaleras



// Funcion ArmorAiUpStairs();
void ArmorAiUpStairs(void);
// IA, armadura subiendo las escaleras



// Funcion ArmorAiUpSteepsRight();
void ArmorAiUpSteepsRight(void);
// IA, armadura subiendo los escalones a la derecha



// Funcion ArmorAiUpSteepsLeft();
void ArmorAiUpSteepsLeft(void);
// IA, armadura subiendo los escalones a la izquierda



// Funcion ArmorAiDownSteeps();
void ArmorAiDownSteeps(void);
// IA, armadura bajando los escalones



// Funcion ArmorAiStage7();
void ArmorAiStage7(void);
// IA, movimiento especial para pasar del stage 7 al 6





#endif
