/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion de las hogueras

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





// Funcion FiretrapAnim();
void FiretrapAnim(void) {

	// Variables
	u8 id = 0;
		
	// Animacion
	for (id = 0; id < FIRETRAP_NUM; id ++) {
		FIRETRAP[id].frame_cnt ++;
		if (FIRETRAP[id].frame_cnt > 4) {
			FIRETRAP[id].frame_cnt = 0;
			FIRETRAP[id].frame ++;
			if (FIRETRAP[id].frame > 3) FIRETRAP[id].frame = 0;
		}
	}

}



// Funcion FiretrapCamHide();
void FiretrapCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 id = 0;


	/*
	-------------------------------------------------
		Gestion de las visivilidad de la lampara
	-------------------------------------------------
	*/

	for (id = 0; id < FIRETRAP_NUM; id ++) {

		// Calcula la posicion del sprite en la pantalla
		spr_x = (FIRETRAP[id].spr_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (FIRETRAP[id].spr_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -64)
			||
			(spr_x > 256)
			||
			(spr_y < -32)
			||
			(spr_y > 192)
			) {
			// No lo esta
			FIRETRAP[id].on_screen[screen] = false;
			// Destruye el sprite
			if (FIRETRAP[id].created[screen]) {
				FIRETRAP[id].created[screen] = false;
				NF_DeleteSprite(screen, FIRETRAP_SPR_ID);
				NF_FreeSpriteGfx(screen, FIRETRAP_SPR_ID);
			}
		}

	}

}



// Funcion FiretrapCamShow();
void FiretrapCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 id = 0;

	/*
	-------------------------------------------------
		Gestiona la visibilidad de las hogueras
	-------------------------------------------------
	*/

	for (id = 0; id < FIRETRAP_NUM; id ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (FIRETRAP[id].spr_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (FIRETRAP[id].spr_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -64)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -32)
			&&
			(spr_y <= 192)
			) {
			// Si no esta creado, crealo
			FIRETRAP[id].on_screen[screen] = true;
			if (!FIRETRAP[id].created[screen]) {
				FIRETRAP[id].created[screen] = true;
				NF_VramSpriteGfx(screen, ID_FIRETRAP, FIRETRAP_SPR_ID, true);
				NF_CreateSprite(screen, FIRETRAP_SPR_ID, FIRETRAP_SPR_ID, FIRETRAP_SPR_PAL, spr_x, spr_y);
				NF_SpriteLayer(screen, FIRETRAP_SPR_ID, TRAPS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, FIRETRAP_SPR_ID, spr_x, spr_y);
			NF_SpriteFrame(screen, FIRETRAP_SPR_ID, FIRETRAP[id].frame);
		} 
	}

}
