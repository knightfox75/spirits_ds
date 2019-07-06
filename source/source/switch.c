/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del sistema de interruptores

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




// Funcion SwitchGetSpriteId();
u16 SwitchGetSpriteId(u8 screen) {

	// Variables
	u8 n = 0;
	u8 id = 255;

	// Busca una Id libre y asignala
	for (n = 0; n < SWITCH_SPR_NUM; n ++) {
		if (!SWITCH_SPR[screen].in_use[n]) {
			id = n;
			SWITCH_SPR[screen].in_use[id] = true;
			n = SWITCH_SPR_NUM;
		}
	}

	// Devuelve la ID
	return SWITCH_SPR[screen].id[id];

}



// Funcion SwitchFreeSpriteId();
void SwitchFreeSpriteId(u8 screen, u16 id) {

	// Variables
	u8 n = 0;

	// Busca una Id libre y asignala
	for (n = 0; n < SWITCH_SPR_NUM; n ++) {
		if (SWITCH_SPR[screen].id[n] == id) {
			SWITCH_SPR[screen].in_use[n] = false;
			n = SWITCH_SPR_NUM;
		}
	}

}



// Funcion CameraSwitchHide();
void CameraSwitchHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 n = 0;


	/*
	-------------------------------------------------
		Gestion de los switchs (Elimina ocultos)
	-------------------------------------------------
	*/

	for (n = 0; n < SWITCH_NUM; n ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (SWITCH[n].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (SWITCH[n].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -16)
			||
			(spr_x > 271)
			||
			(spr_y < -16)
			||
			(spr_y > 207)
			) {
			// No esta en pantalla
			SWITCH[n].on_screen[screen] = false;
			// Destruye el sprite
			if (SWITCH[n].created[screen]) {
				SWITCH[n].created[screen] = false;
				NF_DeleteSprite(screen, SWITCH[n].spr_id[screen]);
				NF_FreeSpriteGfx(screen, SWITCH[n].vram_gfx[screen]);
				SwitchFreeSpriteId(screen, SWITCH[n].spr_id[screen]);
				SWITCH[n].spr_id[screen] = 255, SWITCH[n].vram_gfx[screen] = 255;
			}
		}
	}

}



// Funcion CameraSwitchShow();
void CameraSwitchShow(u8 screen, u8 stage) {

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
		Gestion de los switchs (Muestra visibles)
	-------------------------------------------------
	*/

	for (n = 0; n < SWITCH_NUM; n ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (SWITCH[n].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (SWITCH[n].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -16)
			&&
			(spr_x <= 271)
			&&
			(spr_y >= -16)
			&&
			(spr_y <= 207)
			) {
			// Esta en pantalla
			SWITCH[n].on_screen[screen] = true;
			// Si no esta creado, crealo
			if (!SWITCH[n].created[screen]) {
				id = SwitchGetSpriteId(screen);
				SWITCH[n].spr_id[screen] = id, SWITCH[n].vram_gfx[screen] = id;
				SWITCH[n].created[screen] = true;
				NF_VramSpriteGfx(screen, SWITCH[n].ram_gfx, SWITCH[n].vram_gfx[screen], true);
				NF_CreateSprite(screen, SWITCH[n].spr_id[screen], SWITCH[n].vram_gfx[screen], SPRGFX[ID_SWITCH].pal, (spr_x - SWITCH[n].spr_left), (spr_y - SWITCH[n].spr_up));
				NF_SpriteLayer(screen, SWITCH[n].spr_id[screen], SPRITES_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, SWITCH[n].spr_id[screen], (spr_x - SWITCH[n].spr_left), (spr_y - SWITCH[n].spr_up));
			if (GAMEOPTIONS[0].remake) {
				if (SWITCH[n].activated) {
					NF_SpriteFrame(screen, SWITCH[n].spr_id[screen], 1);
				} else {
					NF_SpriteFrame(screen, SWITCH[n].spr_id[screen], 0);
				}
			} else {
				NF_HflipSprite(screen, SWITCH[n].spr_id[screen], SWITCH[n].activated);
			}
		}
	}

}
