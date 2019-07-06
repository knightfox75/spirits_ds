/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion de las lamparas

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





// Funcion LampCamHide();
void LampCamHide(u8 screen, u8 stage) {

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

	for (id = 0; id < LAMP_NUM; id ++) {

		// Calcula la posicion del sprite en la pantalla
		spr_x = (LAMP[id].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (LAMP[id].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -64)
			||
			(spr_x > 256)
			||
			(spr_y < -64)
			||
			(spr_y > 192)
			) {
			// No lo esta
			LAMP[id].on_screen[screen] = false;
			// Destruye el sprite
			if (LAMP[id].created[screen]) {
				LAMP[id].created[screen] = false;
				NF_DeleteSprite(screen, LAMP_SPR_ID);
				NF_FreeSpriteGfx(screen, LAMP_SPR_ID);
			}
		}

	}

}



// Funcion LampCamShow();
void LampCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 id = 0;

	/*
	-------------------------------------------------
		Gestiona la visibilidad de las lamparas
	-------------------------------------------------
	*/

	for (id = 0; id < LAMP_NUM; id ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (LAMP[id].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (LAMP[id].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -64)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -64)
			&&
			(spr_y <= 192)
			) {
			// Si no esta creado, crealo
			LAMP[id].on_screen[screen] = true;
			if (!LAMP[id].created[screen]) {
				LAMP[id].created[screen] = true;
				NF_VramSpriteGfx(screen, ID_LAMP, LAMP_SPR_ID, true);
				NF_CreateSprite(screen, LAMP_SPR_ID, LAMP_SPR_ID, LAMP_SPR_PAL, spr_x, spr_y);
				NF_SpriteLayer(screen, LAMP_SPR_ID, TRAPS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, LAMP_SPR_ID, spr_x, spr_y);
			if (GAMEOPTIONS[0].remake) NF_SpriteFrame(screen, LAMP_SPR_ID, LAMP[id].frame);
		} 
	}

}



// Funcion LampEvent();
void LampEvent(void) {

	// Activa o desactiva las lamparas
	LampActivation();

	// Temporizador de caida de las lamparas
	LampTimer();

	// Caida de las lamparas
	LampFall();

}



// Funcion LampActivation();
void LampActivation(void) {

	// Variables
	u8 id = 0;

	// Analiza todas las lamparas
	for (id = 0; id < LAMP_NUM; id ++) {

		// Si la lampara esta activada...
		if (LAMP[id].activated) {

			// Si la lampara esta fuera del campo de vision de ambas pantallas
			if (!LAMP[id].on_screen[0] && !LAMP[id].on_screen[1]) {
				// Resetea la lampara
				LAMP[id].pos_x = LAMP[id].lamp_x, LAMP[id].pos_y = LAMP[id].lamp_y;
				LAMP[id].pos_fx = (LAMP[id].pos_x << 8), LAMP[id].pos_fy = (LAMP[id].pos_y << 8);
				LAMP[id].activated = false;
				LAMP[id].fall = false;
				LAMP[id].timer = 0;
			}

		} else {	// Si la lampara no esta activada...

			// Si la lampara esta en el campo de vision de la pantalla principal
			if (LAMP[id].on_screen[0]) {
				// Prepara el contador e inicializa la lampara
				LAMP[id].timer = ((int)((rand() % 180) + 120));
				LAMP[id].activated = true;
			}

		}

	}

}



// Funcion LampTimer();
void LampTimer(void) {

	// Variables
	u8 id = 0;

	// Analiza todas las lamparas
	for (id = 0; id < LAMP_NUM; id ++) {
		if (LAMP[id].activated) {
			if (LAMP[id].timer > 0) {
				LAMP[id].timer --;
				if (LAMP[id].timer == 0) LAMP[id].fall = true;
			}
		}
	}

}



// Funcion LampFall();
void LampFall(void) {

	// Variables
	u8 id = 0;
	s32 speed = 0;
	u8 tile_a, tile_b;

	// Analiza todas las lamparas
	for (id = 0; id < LAMP_NUM; id ++) {
		// Si la lampara esta marcada para caerse...
		if (LAMP[id].fall) {

			// Calcula la velocidad de desplazamiento
			speed = ((LAMP[id].pos_fy - (LAMP[id].lamp_y << 8)) >> 3);
			if (speed < 128) speed = 128;

			// Calcula la nueva posicion
			LAMP[id].pos_fy += speed;
			LAMP[id].pos_y = (LAMP[id].pos_fy >> 8);

			// Obten los tiles de debajo la lampara
			tile_a = NF_GetTile(MAINMAP_SLOT, LAMP[id].pos_x, (LAMP[id].pos_y + 47));
			tile_b = NF_GetTile(MAINMAP_SLOT, (LAMP[id].pos_x + 56), (LAMP[id].pos_y + 47));

			// Deten la caida de la lampara
			if ((tile_a == T_WALL) || (tile_b == T_WALL)) {
				// Deten la caida
				LAMP[id].fall = false;
				// Ajusta la posicion de la lampara
				while ((tile_a == T_WALL) || (tile_b == T_WALL)) {
					// Calcula la nueva posicion
					LAMP[id].pos_fy -= 64;
					LAMP[id].pos_y = (LAMP[id].pos_fy >> 8);
					// Obten los tiles de debajo la lampara
					tile_a = NF_GetTile(MAINMAP_SLOT, LAMP[id].pos_x, (LAMP[id].pos_y + 47));
					tile_b = NF_GetTile(MAINMAP_SLOT, (LAMP[id].pos_x + 56), (LAMP[id].pos_y + 47));
				}
			}

		}
	}

}



// Funcion LampAnimation();
void LampAnimation(void) {

	// Variables
	u16 n = 0;
	
	// Animacion de las antorchas
	for (n = 0; n < LAMP_NUM; n ++) {
		LAMP[n].frame_cnt ++;
		if (LAMP[n].frame_cnt > LAMP_ANIM_SPEED) {
			LAMP[n].frame_cnt = 0;
			LAMP[n].frame ++;
			if (LAMP[n].frame > 3) LAMP[n].frame = 0;
		}
	}

}