/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los NPC
	(Aguila)

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





// Funcion EagleCamHide();
void EagleCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la Aguila
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (EAGLE.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (EAGLE.pos_y - STAGE[stage].stg_top);
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
		!EAGLE.show
		) {
		// No lo esta
		EAGLE.on_screen[screen] = false;
		EAGLE.scr_x[screen] = -64;
		EAGLE.scr_y[screen] = -64;
		// Destruye el sprite
		if (EAGLE.created[screen]) {
			EAGLE.created[screen] = false;
			NF_DeleteSprite(screen, EAGLE_SPR_ID);
			NF_FreeSpriteGfx(screen, EAGLE_SPR_ID);
		}
	}

}



// Funcion EagleCamShow();
void EagleCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la Aguila
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (EAGLE.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (EAGLE.pos_y - STAGE[stage].stg_top);
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
		EAGLE.show
		) {
		// Esta en pantalla
		EAGLE.on_screen[screen] = true;
		EAGLE.scr_x[screen] = spr_x;
		EAGLE.scr_y[screen] = spr_y;
		// Si no esta creado, crealo
		if (!EAGLE.created[screen]) {
			EAGLE.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_EAGLE, EAGLE_SPR_ID, true);
			NF_CreateSprite(screen, EAGLE_SPR_ID, EAGLE_SPR_ID, NPC_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, EAGLE_SPR_ID, SPRITES_LAYER);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, EAGLE_SPR_ID, (spr_x - EAGLE.spr_left), (spr_y - EAGLE.spr_up));
		NF_SpriteFrame(screen, EAGLE_SPR_ID, EAGLE.frame);
		NF_HflipSprite(screen, EAGLE_SPR_ID, EAGLE.flip);
	}

}



// Funcion EagleCheckRight();
u16 EagleCheckRight(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (EAGLE.pos_fx >> 8);
	fy = (EAGLE.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	x = (fx + EAGLE.right + add);
	start = (fy - EAGLE.up);
	end = (fy + EAGLE.down);

	// Analiza los tiles del lateral (steps de 1/2 tile)
	for (y = start; y <= end; y += 4) {
		tile = NF_GetTile(MAINMAP_SLOT, x, y);
		// Si el tile es pared...
		if (tile == T_WALL) {
			result = T_WALL;
			y = end;
		}
	}

	// Devuelve el resultado
	return result;

}



// Funcion EagleCheckLeft();
u16 EagleCheckLeft(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (EAGLE.pos_fx >> 8);
	fy = (EAGLE.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	x = (fx - EAGLE.left - add);
	start = (fy - EAGLE.up);
	end = (fy + EAGLE.down);

	// Analiza los tiles del lateral (steps de 1/2 tile)
	for (y = start; y <= end; y += 4) {
		tile = NF_GetTile(MAINMAP_SLOT, x, y);
		// Si el tile es pared...
		if (tile == T_WALL) {
			result = T_WALL;
			y = end;
		}
	}

	// Devuelve el resultado
	return result;

}



// Funcion EagleCheckUp();
u16 EagleCheckUp(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (EAGLE.pos_fx >> 8);
	fy = (EAGLE.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	y = (fy - EAGLE.up - add);
	start = (fx - EAGLE.left);
	end = (fx + EAGLE.right);

	// Analiza los tiles de la parte superior (steps de 4 pixeles)
	for (x = start; x <= end; x += 4) {
		tile = NF_GetTile(MAINMAP_SLOT, x, y);
		// Si el tile es pared...
		if (tile == T_WALL) {
			result = T_WALL;
			x = end;
		}
	}

	// Devuelve el resultado
	return result;

}



// Funcion EagleCheckDown();
u16 EagleCheckDown(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (EAGLE.pos_fx >> 8);
	fy = (EAGLE.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	y = (fy + EAGLE.down + add);
	start = (fx - EAGLE.left);
	end = (fx + EAGLE.right);

	// Analiza los tiles de la parte inferior (steps de 4 pixels)
	for (x = start; x <= end; x += 4) {
		tile = NF_GetTile(MAINMAP_SLOT, x, y);
		// Si el tile es pared...
		if (tile == T_WALL) {
			result = T_WALL;
			x = end;
		}
	}

	// Devuelve el resultado
	return result;

}



// Funcion EagleFly();
void EagleFly(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u16 t_left = T_AIR, t_right = T_AIR, t_up = T_AIR, t_down = T_AIR;	// Almacena los tiles


	/*
	-------------------------------------------------
		Analiza las posibilidades
	-------------------------------------------------
	*/

	// Analiza los tiles de alrededor
	t_left = EagleCheckLeft(1);
	t_right = EagleCheckRight(1);
	t_up = EagleCheckUp(1);
	t_down = EagleCheckDown(1);

	// Calcula si puedes ir a la derecha
	if (t_right != T_WALL) { 
		EAGLE.mov_right = true;
	} else {
		EAGLE.mov_right = false;
	}

	// Calcula si puedes ir a la izquierda
	if (t_left != T_WALL) {
		EAGLE.mov_left = true;
	} else {
		EAGLE.mov_left = false;
	}

	// Calcula si puedes ir arriba
	if (t_up != T_WALL) { 
		EAGLE.mov_up = true;
	} else {
		EAGLE.mov_up = false;
	}

	// Calcula si puedes ir abajo
	if (t_down != T_WALL) { 
		EAGLE.mov_down = true;
	} else {
		EAGLE.mov_down = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// Volar a la derecha
	if (EAGLE.ai_right && EAGLE.mov_right) {
		// Nueva posicion
		EAGLE.pos_fx += EAGLE_FLY_SPEED;
	}

	// Volar a la izquierda
	if (EAGLE.ai_left && EAGLE.mov_left) {
		// Nueva posicion
		EAGLE.pos_fx -= EAGLE_FLY_SPEED;
	}

	// Volar arriba
	if (EAGLE.ai_up && EAGLE.mov_up) {
		// Nueva posicion
		EAGLE.pos_fy -= EAGLE_FLY_SPEED;
	}

	// Volar abajo
	if (EAGLE.ai_down && EAGLE.mov_down) {
		// Nueva posicion
		EAGLE.pos_fy += EAGLE_FLY_SPEED;
	}

}



// Funcion EagleAdjustPosition();
void EagleAdjustPosition(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u16 t_left = T_AIR, t_right = T_AIR, t_up = T_AIR, t_down = T_AIR;	// Almacena los tiles


	/*
	-------------------------------------------------
		Ajusta la aguila a derecha e izquierda
	-------------------------------------------------
	*/

	// Ajusta el limite derecho
	t_right = EagleCheckRight(0);
	while (t_right == T_WALL) {
		EAGLE.pos_fx -= 64;
		t_right = EagleCheckRight(0);
	}

	// Ajusta el limite izquierdo
	t_left = EagleCheckLeft(0);
	// Ajusta la posicion de la izquierda
	while (t_left == T_WALL) {
		EAGLE.pos_fx += 64;
		t_left = EagleCheckLeft(0);
	}


	/*
	-----------------------------------------
		Ajusta el nivel del techo y suelo
	-----------------------------------------
	*/
	
	// Ajusta al nivel del techo
	t_up = EagleCheckUp(0);
	while (t_up == T_WALL) {
		EAGLE.pos_fy += 64;
		t_up = EagleCheckUp(0);
	}

	// Ajusta al nivel del suelo
	t_down = EagleCheckDown(0);
	while (t_down == T_WALL) {
		EAGLE.pos_fy -= 64;
		t_down = EagleCheckDown(0);
	}

}



// Funcion EagleAnimation();
void EagleAnimation(void) {

	// Animacion andando (Frames 0 a 3)
	EAGLE.frame_cnt ++;
	if (EAGLE.frame_cnt > 9) {
		EAGLE.frame_cnt = 0;
		EAGLE.frame ++;
		if (EAGLE.frame > 3) EAGLE.frame = 0;
	}

	// Calcula y marca la direccion a la que miras
	if (EAGLE.ai_right && EAGLE.flip) EAGLE.flip = false;
	if (EAGLE.ai_left && !EAGLE.flip) EAGLE.flip = true;
	
}



// Funcion EagleMove();
void EagleMove(void) {

	/*
	-------------------------------------------------
		Movimiento de la aguila
	-------------------------------------------------
	*/

	// Procesa el andar
	EagleFly();

	// Ajusta la posicion de la aguila, para que no atraviese ningun limite
	EagleAdjustPosition();

	// Animacion de la aguila
	EagleAnimation();


	/*
	-------------------------------------------------
		Ajustes de posicion
	-------------------------------------------------
	*/

	EAGLE.old_x = EAGLE.pos_x;
	EAGLE.old_y = EAGLE.pos_y;
	EAGLE.pos_x = (EAGLE.pos_fx >> 8);
	EAGLE.pos_y = (EAGLE.pos_fy >> 8);
	EAGLE.stage = GetStage(EAGLE.pos_x, EAGLE.pos_y);

}
