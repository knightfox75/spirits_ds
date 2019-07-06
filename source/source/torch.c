/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del sistema de antorchas

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

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Includes del juego
#include "includes.h"




// Funcion TorchGetSpriteId();
u16 TorchGetSpriteId(u8 screen) {

	// Variables
	u8 n = 0;
	u8 id = 255;

	// Busca una Id libre y asignala
	for (n = 0; n < TORCH_SPR_NUM; n ++) {
		if (!TORCH_SPR[screen].in_use[n]) {
			id = n;
			TORCH_SPR[screen].in_use[id] = true;
			n = TORCH_SPR_NUM;
		}
	}

	// Devuelve la ID
	return TORCH_SPR[screen].id[id];

}



// Funcion TorchFreeSpriteId();
void TorchFreeSpriteId(u8 screen, u16 id) {

	// Variables
	u8 n = 0;

	// Busca una Id libre y asignala
	for (n = 0; n < TORCH_SPR_NUM; n ++) {
		if (TORCH_SPR[screen].id[n] == id) {
			TORCH_SPR[screen].in_use[n] = false;
			n = TORCH_SPR_NUM;
		}
	}

}



// Funcion CameraTorchHide();
void CameraTorchHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 n = 0;


	/*
	-------------------------------------------------
		Gestion de las antorchas (Elimina ocultos)
	-------------------------------------------------
	*/

	for (n = 0; n < TORCH_NUM; n ++) {
		// Si estas creada...
		if (TORCH[n].created[screen]) {
			// Calcula la posicion del sprite en la pantalla
			spr_x = (TORCH[n].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
			spr_y = (TORCH[n].pos_y - STAGE[stage].stg_top);
			// Calcula si esta en pantalla
			if (
				(spr_x < -16)
				||
				(spr_x > 271)
				||
				(spr_y < -32)
				||
				(spr_y > 223)
				||
				(stage != TORCH[n].stage)
				) {
				// No esta en pantalla
				TORCH[n].on_screen[screen] = false;
				// Destruye el sprite
				TORCH[n].created[screen] = false;
				NF_DeleteSprite(screen, TORCH[n].spr_id[screen]);
				TorchFreeSpriteId(screen, TORCH[n].spr_id[screen]);
				TORCH[n].spr_id[screen] = 255;
			}
		}
	}

}



// Funcion CameraTorchShow();
void CameraTorchShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 n = 0;
	u16 id = 0;


	/*
	-------------------------------------------------
		Gestion de las antorchas (Muestra visibles)
	-------------------------------------------------
	*/

	for (n = 0; n < TORCH_NUM; n ++) {
		// Si estas en la misma pantalla
		if (TORCH[n].stage == stage) {
			// Calcula la posicion del sprite en la pantalla
			spr_x = (TORCH[n].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
			spr_y = (TORCH[n].pos_y - STAGE[stage].stg_top);
			// Calcula si esta en pantalla
			if (
				(spr_x >= -16)
				&&
				(spr_x <= 271)
				&&
				(spr_y >= -32)
				&&
				(spr_y <= 223)
				) {
				// Esta en pantalla
				TORCH[n].on_screen[screen] = true;
				// Si no esta creado, crealo
				if (!TORCH[n].created[screen]) {
					id = TorchGetSpriteId(screen);
					TORCH[n].spr_id[screen] = id;
					TORCH[n].created[screen] = true;
					if (TORCH[n].type == 0) {
						NF_CreateSprite(screen, TORCH[n].spr_id[screen], TORCH_SPR_ID, TORCH_SPR_PAL, spr_x, spr_y);
					} else {
						NF_CreateSprite(screen, TORCH[n].spr_id[screen], FLAME_SPR_ID, FLAME_SPR_PAL, spr_x, spr_y);
					}
					NF_SpriteLayer(screen, TORCH[n].spr_id[screen], TORCH_LAYER);
				}
				// Actualiza el sprite
				NF_MoveSprite(screen, TORCH[n].spr_id[screen], spr_x, spr_y);
				NF_SpriteFrame(screen, TORCH[n].spr_id[screen], TORCH[n].frame);
			}
		}
	}

}



// Funcion TochAnimation();
void TorchAnimation(void) {

	// Variables
	u16 n = 0;
	
	// Animacion de las antorchas
	for (n = 0; n < TORCH_NUM; n ++) {
		TORCH[n].frame_cnt ++;
		if (TORCH[n].frame_cnt > TORCH_SPEED) {
			TORCH[n].frame_cnt = 0;
			TORCH[n].frame ++;
			if (TORCH[n].frame > 3) TORCH[n].frame = 0;
		}
	}

}
