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

// Includes C
#include <stdio.h>
#include <time.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Includes del juego
#include "includes.h"





// Funcion AiCheckRight();
u8 AiCheckRight(s32 x, s32 y, u8 add) {

	// Variables
	s32 pos_x = (x + (add + 8));	// Coordenadas
	s32 pos_y = 0;
	u8 n = 0;				// Uso general
	u8 wall = 0;			// Bitmask de muros
	u8 steep = 0;			// Bitmask de escalones
	u8 result = AI_CAIR;	// Resultado

	// Analiza los tiles (BITMASK)
	for (n = 0; n < 8; n ++) {
		pos_y = (y - (n << 3) + 32);
		switch (NF_GetTile(MAINMAP_SLOT, pos_x, pos_y)) {
			case T_WALL:
				wall |= BIT(n);
				break;
			case T_STEEP:
				steep |= BIT(n);
				break;
			default:
				break;
		}
	}

	// Calcula el resultado
	if (wall != 0) {
		if (((wall & 0x0f) != 0) && ((wall >> 4) == 0)) {
			result = AI_CHALFWALL;
		} else {
			result = AI_CWALL;
		}
	}
	if ((steep & 0x0f) != 0) result = AI_CSTEEP;

	// Devuelve el resultado
	return result;

}


// Funcion AiCheckLeft();
u8 AiCheckLeft(s32 x, s32 y, u8 add) {

	// Variables
	s32 pos_x = (x - (add + 8));	// Coordenadas
	s32 pos_y = 0;
	u8 n = 0;				// Uso general
	u8 wall = 0;			// Bitmask de muros
	u8 steep = 0;			// Bitmask de escalones
	u8 result = AI_CAIR;	// Resultado

	// Analiza los tiles (BITMASK)
	for (n = 0; n < 8; n ++) {
		pos_y = (y - (n << 3) + 32);
		switch (NF_GetTile(MAINMAP_SLOT, pos_x, pos_y)) {
			case T_WALL:
				wall |= BIT(n);
				break;
			case T_STEEP:
				steep |= BIT(n);
				break;
			default:
				break;
		}
	}

	// Calcula el resultado
	if (wall != 0) {
		if (((wall & 0x0f) != 0) && ((wall >> 4) == 0)) {
			result = AI_CHALFWALL;
		} else {
			result = AI_CWALL;
		}
	}
	if ((steep & 0x0f) != 0) result = AI_CSTEEP;

	// Devuelve el resultado
	return result;

}



// Funcion AiCheckBottom();
u8 AiCheckBottom(s32 x, s32 y, u8 add) {

	// Variables
	s32 pos_x = 0;			// Coordenadas
	s32 pos_y = (y + (add + 1));
	u8 n = 0;				// Uso general
	u8 wall = 0;			// Bitmask de muros
	u8 steep = 0;			// Bitmask de escalones
	u8 stair = 0;			// Bitmask de las escaleras
	u8 result = AI_CAIR;	// Resultado

	// Analiza los tiles (BITMASK)
	for (n = 0; n < 8; n ++) {
		pos_x = (x - (n << 3) + 32);
		switch (NF_GetTile(MAINMAP_SLOT, pos_x, pos_y)) {
			case T_WALL:
				wall |= BIT(n);
				break;
			case T_STEEP:
				steep |= BIT(n);
				break;
			case T_STAIR:
				stair |= BIT(n);
			default:
				break;
		}
	}

	// Calcula el resultado
	if ((wall != 0) && (stair == 0)) {
		result = AI_CFLOOR;							// Suelo completo por defecto
		if (wall == 0x07) result = AI_CRIGHTFLOOR;	// Suelo a la derecha
		if (wall == 0xe0) result = AI_CLEFTFLOOR;	// Suelo a la izquierda
	}
	if (steep != 0) {
		if ((steep & 0x18) == 0x18) {
			result = AI_CSTEEP;
		} else {
			result = AI_CHALFSTEEP;
		}
	}
	if ((stair & 0x7e) == 0x7e) {
		result = AI_CSTAIR;
	} else {
		if (wall != 0) result = AI_CFLOOR;
	}
	
	// Devuelve el resultado
	return result;

}



// Funcion AiCheckTop();
u8 AiCheckTop(s32 x, s32 y, u8 add) {

	// Variables
	s32 pos_x = 0;			// Coordenadas
	s32 pos_y = (y - (add + 1));
	u8 n = 0;				// Uso general
	u8 wall = 0;			// Bitmask de muros
	u8 steep = 0;			// Bitmask de escalones
	u8 stair = 0;			// Bitmask de las escaleras
	u8 result = AI_CAIR;	// Resultado

	// Analiza los tiles (BITMASK)
	for (n = 0; n < 8; n ++) {
		pos_x = (x - (n << 3) + 32);
		switch (NF_GetTile(MAINMAP_SLOT, pos_x, pos_y)) {
			case T_WALL:
				wall |= BIT(n);
				break;
			case T_STEEP:
				steep |= BIT(n);
				break;
			case T_STAIR:
				stair |= BIT(n);
			default:
				break;
		}
	}

	// Calcula el resultado
	if (steep != 0) result = AI_CSTEEP;
	if ((wall & 0x18) == 0x18)  result = AI_CWALL;
	if ((stair & 0x7e) == 0x7e) result = AI_CSTAIR;

	// Devuelve el resultado
	return result;

}

