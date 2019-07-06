/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion del diablo

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





// Funcion DevilMain();
void DevilMain(void) {

	// Temporazador de actuacion
	DevilTimer();

	// Si se ha activado el evento
	if (DEVIL.activated) {
		// Animacion
		DevilAnimation();
	}

	// Si se ha disparado la flecha
	if (ARROW.activated) {
		// Gestiona el disparo
		if (ARROW.shot) { 
			ArrowShot();
		} else {
			// Si has tocado un muro, espera 60 frames y haz desaparecer la flecha
			ARROW.timer --;
			if (ARROW.timer <= 0) {
				ARROW.timer = 0;
				ARROW.cancel = true;
			}
		}
	}

}



// Funcion DevilTimer
void DevilTimer(void) {

	// Si estas inactivo y con tiempo en el contador...
	if (!DEVIL.activated && (DEVIL.timer > 0)) {
		// Actualiza el temporizador
		DEVIL.timer --;
		// Si has llegado a 0, activacion del evento
		if (DEVIL.timer == 0) {
			if (DevilGetPos()) {
				// Exito en colocar al diablo, activa el evento
				DEVIL.activated = true;
				DEVIL.frame = 0;
				DEVIL.frame_cnt = 0;
				DEVIL.animation = 0;
			} else {
				// Fallo, intentalo de nuevo en 5 segundos
				DEVIL.timer = 300;
			}
		}
	}

}



// Funcion DevilGetPos();
bool DevilGetPos(void) {

	// Variables
	bool result = false;				// Resultado
	u8 stage = 0;						// Stage del suceso

	s32 pos_xl, pos_xr;					// Posiciones iniciales
	s32 pos_yl, pos_yr;

	bool left = false, right = false;	// Disponibilidad de la ubicacion

	s32 x = 0, y = 0, width = 0, height = 0;			// Uso general

	// Stage del evento
	stage = GetStage(CHARACTER.pos_x, CHARACTER.pos_y);

	// Calcula las posiciones
	pos_xl = (CHARACTER.pos_x - 96), pos_yl = (CHARACTER.pos_y - 24);
	pos_xr = (CHARACTER.pos_x + 96), pos_yr = (CHARACTER.pos_y - 24);

	// Calcula si estan en rango
	if (pos_xl > (STAGE[stage].stg_left + 32)) left = true;
	if (pos_xr < (STAGE[stage].stg_right - 32)) right = true;

	// Calcula si las posiciones son validas
	width = (DEVIL.left + DEVIL.right);
	height = (DEVIL.up + DEVIL.down);
	// Izquierda
	if (left) {
		x = (pos_xl - DEVIL.left);
		y = (pos_yl - DEVIL.up);
		left = DevilCheckBox(x, y, width, height);
	}
	// Derecha
	if (right) {
		x = (pos_xr - DEVIL.left);
		y = (pos_yr - DEVIL.up);
		right = DevilCheckBox(x, y, width, height);
	}

	// Si las trayectorias son estan libres
	// Izquierda
	if (left) {
		x = pos_xl;
		y = (pos_yl - ARROW.up);
		width = (CHARACTER.pos_x - x);
		height = (ARROW.up + ARROW.down);
		left = DevilCheckBox(x, y, width, height);
	}
	// Derecha
	if (right) {
		x = CHARACTER.pos_x;
		y = (pos_yr - ARROW.up);
		width = (pos_xr - x);
		height = (ARROW.up + ARROW.down);
		right = DevilCheckBox(x, y, width, height);
	}

	// Escoge una de las posiciones
	if (left && right) {
		if ((rand() % 100) > 50) {
			left = false;
		} else {
			right = false;
		}
	}

	// Valida solo la izquierda
	if (left) {
		//*** Diablo
		DEVIL.pos_x = pos_xl, DEVIL.pos_fx = (pos_xl << 8);
		DEVIL.pos_y = pos_yl, DEVIL.pos_fy = (pos_yl << 8);
		DEVIL.flip = false;
		//** Flecha
		ARROW.pos_x = pos_xl, ARROW.pos_fx = (pos_xl << 8);
		ARROW.pos_y = pos_yl, ARROW.pos_fy = (pos_yl << 8);
		ARROW.flip = false;
		ARROW.speed = ARROW_MIN_SPEED;
		// Correcto
		result = true;
	}
	// Valida solo la derecha
	if (right) {
		//*** Diablo
		DEVIL.pos_x = pos_xr, DEVIL.pos_fx = (pos_xr << 8);
		DEVIL.pos_y = pos_yr, DEVIL.pos_fy = (pos_yr << 8);
		DEVIL.flip = true;
		// *** Flecha
		ARROW.pos_x = pos_xr, ARROW.pos_fx = (pos_xr << 8);
		ARROW.pos_y = pos_yr, ARROW.pos_fy = (pos_yr << 8);
		ARROW.flip = true;
		ARROW.speed = ARROW_MIN_SPEED;
		// Correcto
		result = true;
	}

	// Devuelve el resultado
	return result;

}



// Funcion DevilCheckBox();
bool DevilCheckBox(s32 pos_x, s32 pos_y, s16 width, s16 height) {

	// Variables
	s32 start_x = pos_x, end_x = (pos_x + width);
	s32 start_y = pos_y, end_y = (pos_y + height);
	s32 x = 0, y = 0;
	bool result = true;

	// Analiza el cuadrante
	for (y = start_y; y < end_y; y += 8) {
		for (x = start_x; x < end_x; x += 8) {
			// Si algun tile es muro, marcalo y sal
			if (NF_GetTile(MAINMAP_SLOT, x, y) == T_WALL){
				result = false;
				x = end_x;
				y = end_y;
			}
		}
	}

	// Devuelve el resultado
	return result;

}



// Funcion DevilAnimation
void DevilAnimation(void) {

	// Control de la animacion
	switch (DEVIL.animation) {

		// Animacion de entrada
		case 0:
			DEVIL.frame_cnt ++;
			if (DEVIL.frame_cnt > 4) {
				DEVIL.frame_cnt = 0;
				DEVIL.frame ++;
				if (DEVIL.frame > 3) {
					DEVIL.frame = 3;
					DEVIL.animation = 1;
				}
			}
			break;

		// Espera 60 frames, pero dispara la flecha en el frame 30
		case 1:
			DEVIL.frame_cnt ++;
			// Activa el disparo de la flecha
			if (DEVIL.frame_cnt == 30) {
				ARROW.activated = true;
				ARROW.shot = true;
				ARROW.timer = 60;
			}
			// Fin de la espera, pasa a la animacion de salida
			if (DEVIL.frame_cnt > 60) {
				DEVIL.frame_cnt = 0;
				DEVIL.animation = 2;
			}
			break;

		// Animacion de salida
		case 2:
			DEVIL.frame_cnt ++;
			if (DEVIL.frame_cnt > 4) {
				DEVIL.frame_cnt = 0;
				DEVIL.frame --;
				if (DEVIL.frame < 0) {
					DEVIL.frame = 0;
					DEVIL.activated = false;
					DEVIL.timer = ((rand() % DEVIL_RAND_TIME) + DEVIL_MIN_TIME);;
				}
			}
			break;

		// Nada, error trap
		default:
			break;

	}

}



// Funcion ArrowShot();
void ArrowShot(void) {

	// Variables
	u16 tile_up = T_AIR, tile_down = T_AIR;
	s32 dist_x = 0, dist_y = 0;

	// Calcula la nueva velocidad
	ARROW.speed += (ARROW.speed >> 3);
	if (ARROW.speed > ARROW_MAX_SPEED) ARROW.speed = ARROW_MAX_SPEED;

	// Mueve a la flecha
	if (ARROW.flip) {
		// A la izquierda
		ARROW.pos_fx -= ARROW.speed;
		// Si hay colision con un muro, cancela la flecha
		ARROW.pos_x = (ARROW.pos_fx >> 8);
		tile_up = NF_GetTile(MAINMAP_SLOT, (ARROW.pos_x - ARROW.left), ARROW.pos_y);
		tile_down = NF_GetTile(MAINMAP_SLOT, (ARROW.pos_x - ARROW.left), (ARROW.pos_y + 1));
		if ((tile_up == T_WALL) || (tile_down == T_WALL)) {
			ARROW.shot = false;
			while ((tile_up == T_WALL) || (tile_down == T_WALL)) {
				// Ajusta la posicion
				ARROW.pos_fx += 64;
				// Si hay colision con un muro, cancela la flecha
				ARROW.pos_x = (ARROW.pos_fx >> 8);
				tile_up = NF_GetTile(MAINMAP_SLOT, (ARROW.pos_x - ARROW.left), ARROW.pos_y);
				tile_down = NF_GetTile(MAINMAP_SLOT, (ARROW.pos_x - ARROW.left), (ARROW.pos_y + 1));
			}
		}
	} else {
		// A la derecha
		ARROW.pos_fx += ARROW.speed;
		// Si hay colision con un muro, cancela la flecha
		ARROW.pos_x = (ARROW.pos_fx >> 8);
		tile_up = NF_GetTile(MAINMAP_SLOT, (ARROW.pos_x + ARROW.right), ARROW.pos_y);
		tile_down = NF_GetTile(MAINMAP_SLOT, (ARROW.pos_x + ARROW.right), (ARROW.pos_y + 1));
		if ((tile_up == T_WALL) || (tile_down == T_WALL)) {
			ARROW.shot = false;
			while ((tile_up == T_WALL) || (tile_down == T_WALL)) {
				// Ajusta la posicion
				ARROW.pos_fx -= 64;
				// Si hay colision con un muro, cancela la flecha
				ARROW.pos_x = (ARROW.pos_fx >> 8);
				tile_up = NF_GetTile(MAINMAP_SLOT, (ARROW.pos_x + ARROW.right), ARROW.pos_y);
				tile_down = NF_GetTile(MAINMAP_SLOT,(ARROW.pos_x + ARROW.right), (ARROW.pos_y + 1));
			}
		}
	}

	// Calcula si la flecha esta fuera del campo de accion y debe ser desactivada
	dist_x = (CHARACTER.pos_x - ARROW.pos_x);
	if (dist_x < 0) dist_x = -dist_x;
	dist_y = (CHARACTER.pos_y - ARROW.pos_y);
	if (dist_y < 0) dist_y = -dist_y;
	if (((dist_x > 192) || (dist_y > 128)) && !ARROW.on_screen[0] && !ARROW.on_screen[1]) {
		ARROW.cancel = true;
		ARROW.shot = false;
	}

}



// Funcion CameraDevilHide();
void CameraDevilHide(u8 screen, u8 stage) {

	DevilCamHide(screen, stage);	// Diablo
	ArrowCamHide(screen, stage);	// Flecha del diablo

}



// Funcion CameraDevilShow();
void CameraDevilShow(u8 screen, u8 stage) {

	DevilCamShow(screen, stage);	// Diablo
	ArrowCamShow(screen, stage);	// Flecha del diablo

}



// Funcion DevilCamHide();
void DevilCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		el Diablo
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (DEVIL.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (DEVIL.pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x < -32)
		||
		(spr_x > 287)
		||
		(spr_y < -32)
		||
		(spr_y > 223)
		||
		!DEVIL.activated
		) {
		// No lo esta
		DEVIL.on_screen[screen] = false;
		DEVIL.scr_x[screen] = -64;
		DEVIL.scr_y[screen] = -64;
		// Destruye el sprite
		if (DEVIL.created[screen]) {
			DEVIL.created[screen] = false;
			NF_DeleteSprite(screen, DEVIL_SPR_ID);
			NF_FreeSpriteGfx(screen, DEVIL_SPR_ID);
		}
	}

}



// Funcion DevilCamShow();
void DevilCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		el Diablo
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (DEVIL.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (DEVIL.pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x >= -32)
		&&
		(spr_x <= 287)
		&&
		(spr_y >= -32)
		&&
		(spr_y <= 223)
		&&
		DEVIL.activated
		) {
		// Esta en pantalla
		DEVIL.on_screen[screen] = true;
		DEVIL.scr_x[screen] = spr_x;
		DEVIL.scr_y[screen] = spr_y;
		// Si no esta creado, crealo
		if (!DEVIL.created[screen]) {
			DEVIL.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_DEVIL, DEVIL_SPR_ID, true);
			NF_CreateSprite(screen, DEVIL_SPR_ID, DEVIL_SPR_ID, DEVIL_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, DEVIL_SPR_ID, SPRITES_LAYER);
			NF_HflipSprite(screen, DEVIL_SPR_ID, DEVIL.flip);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, DEVIL_SPR_ID, (spr_x - DEVIL.spr_left), (spr_y - DEVIL.spr_up));
		NF_SpriteFrame(screen, DEVIL_SPR_ID, DEVIL.frame);
	}

}



// Funcion ArrowCamHide();
void ArrowCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la Flecha
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (ARROW.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (ARROW.pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x < -16)
		||
		(spr_x > 271)
		||
		(spr_y < -8)
		||
		(spr_y > 199)
		||
		!ARROW.activated
		) {
		// No lo esta
		ARROW.on_screen[screen] = false;
		ARROW.scr_x[screen] = -64;
		ARROW.scr_y[screen] = -64;
		// Destruye el sprite
		if (ARROW.created[screen]) {
			ARROW.created[screen] = false;
			NF_DeleteSprite(screen, ARROW_SPR_ID);
			NF_FreeSpriteGfx(screen, ARROW_SPR_ID);
		}
	}

}



// Funcion ArrowCamShow();
void ArrowCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la Flecha
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (ARROW.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (ARROW.pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x >= -16)
		&&
		(spr_x <= 271)
		&&
		(spr_y >= -8)
		&&
		(spr_y <= 199)
		&&
		ARROW.activated
		) {
		// Esta en pantalla
		ARROW.on_screen[screen] = true;
		ARROW.scr_x[screen] = spr_x;
		ARROW.scr_y[screen] = spr_y;
		// Si no esta creado, crealo
		if (!ARROW.created[screen]) {
			ARROW.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_ARROW, ARROW_SPR_ID, true);
			NF_CreateSprite(screen, ARROW_SPR_ID, ARROW_SPR_ID, ARROW_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, ARROW_SPR_ID, SPRITES_LAYER);
			NF_HflipSprite(screen, ARROW_SPR_ID, ARROW.flip);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, ARROW_SPR_ID, (spr_x - ARROW.spr_left), (spr_y - ARROW.spr_up));
	}

}
