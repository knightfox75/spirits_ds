/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los datos
	de los NPC

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





// Funcion LoadDefaultNpcData();
void LoadDefaultNpcData(void) {

	// Datos del grafico del sprite de la armadura
	SPRGFX[ID_ARMOR].width = 64, SPRGFX[ID_ARMOR].height = 64, SPRGFX[ID_ARMOR].pal = SPRITE_8BITS_PAL;
	// Datos del grafico del sprite de la princesa
	SPRGFX[ID_PRINCESS].width = 64, SPRGFX[ID_PRINCESS].height = 64, SPRGFX[ID_PRINCESS].pal = SPRITE_8BITS_PAL;
	// Datos del grafico del sprite de la aguila
	SPRGFX[ID_EAGLE].width = 64, SPRGFX[ID_EAGLE].height = 64, SPRGFX[ID_EAGLE].pal = SPRITE_8BITS_PAL;

	// Datos del tamaño del sprite de la Armadura.
	ARMOR.spr_up = 31, ARMOR.spr_left = 31;
	ARMOR.up = 31, ARMOR.down = 32, ARMOR.left = 12, ARMOR.right = 13;
	ARMOR.mov_y = 32;

	// Datos del tamaño del sprite de la Princesa.
	PRINCESS.spr_up = 31, PRINCESS.spr_left = 31;
	PRINCESS.up = 9, PRINCESS.down = 32, PRINCESS.left = 12, PRINCESS.right = 13;
	PRINCESS.mov_y = 32;

	// Datos del tamaño del sprite del Aguila.
	EAGLE.spr_up = 31, EAGLE.spr_left = 31;
	EAGLE.up = 23, EAGLE.down = 24, EAGLE.left = 23, EAGLE.right = 24;
	EAGLE.mov_y = 32;

}



// Funcion SetArmor();
void SetArmor(u8 pos) {

	// Reinicia los parametros de la Armadura
	ARMOR.show = false;
	ARMOR.done = false;
	ARMOR.created[0] = false, ARMOR.created[1] = false;
	ARMOR.on_screen[0] = false, ARMOR.on_screen[1] = false;

	// Flags de movimiento
	ARMOR.mov_left = false, ARMOR.mov_right = false;
	ARMOR.mov_up = false, ARMOR.mov_down = false;
	// Flags de salto
	ARMOR.can_jump = false, ARMOR.is_jump = false;
	// Control del salto
	ARMOR.jump_direction = 0, ARMOR.jump_height = 0, ARMOR.air_speed = 0;
	// Flags de caida
	ARMOR.fall = false;
	ARMOR.force_down = false;
	// Flags de escalera
	ARMOR.stair_up = false, ARMOR.stair_down = false, ARMOR.in_stair = false;
	// Datos de estado de la animacion
	ARMOR.frame = 0, ARMOR.frame_cnt = 0, ARMOR.anim = ARMOR_ANIM_STANDBY;

	// Datos de la posicion de la Armadura (Centro del Sprite)
	ARMOR.pos_x = RANDOM_POS[pos].x;
	ARMOR.pos_y = (RANDOM_POS[pos].y - ARMOR.mov_y);
	ARMOR.pos_fx = (ARMOR.pos_x << 8);
	ARMOR.pos_fy = (ARMOR.pos_y << 8);
	ARMOR.flip = false;

	// Datos de la IA
	if ((rand() % 100) > 50) {
		ARMOR.ai_command = AI_WALK_RIGHT;
		ARMOR.ai_right = true;
		ARMOR.ai_left = false;
	} else {
		ARMOR.ai_command = AI_WALK_LEFT;
		ARMOR.ai_right = false;
		ARMOR.ai_left = true;
	}
	ARMOR.ai_down = false;
	ARMOR.ai_jump = false;
	ARMOR.ai_shortjump = false;
	ARMOR.ai_up = false;
	ARMOR.ai_ready = true;
	ARMOR.ai_timer = 0;

}



// Funcion SetPrincess();
void SetPrincess(u8 pos) {

	// Reinicia los parametros de la Princesa
	PRINCESS.show = false;
	PRINCESS.done = false;
	PRINCESS.created[0] = false, PRINCESS.created[1] = false;
	PRINCESS.on_screen[0] = false, PRINCESS.on_screen[1] = false;

	// Flags de movimiento
	PRINCESS.mov_left = false, PRINCESS.mov_right = false;
	PRINCESS.mov_up = false, PRINCESS.mov_down = false;
	// Flags de salto
	PRINCESS.can_jump = false, PRINCESS.is_jump = false;
	// Control del salto
	PRINCESS.jump_direction = 0, PRINCESS.jump_height = 0, PRINCESS.air_speed = 0;
	// Flags de caida
	PRINCESS.fall = false;
	PRINCESS.force_down = false;
	// Flags de escalera
	PRINCESS.stair_up = false, PRINCESS.stair_down = false, PRINCESS.in_stair = false;
	// Datos de estado de la animacion
	PRINCESS.frame = 0, PRINCESS.frame_cnt = 0, PRINCESS.anim = PRINCESS_ANIM_STANDBY;

	// Datos de la posicion de la Princesa (Centro del Sprite)
	PRINCESS.pos_x = RANDOM_POS[pos].x;
	PRINCESS.pos_y = (RANDOM_POS[pos].y - PRINCESS.mov_y);
	PRINCESS.pos_fx = (PRINCESS.pos_x << 8);
	PRINCESS.pos_fy = (PRINCESS.pos_y << 8);
	PRINCESS.flip = false;

	// Datos de la IA
	if ((rand() % 100) > 50) {
		PRINCESS.ai_command = AI_WALK_RIGHT;
		PRINCESS.ai_right = true;
		PRINCESS.ai_left = false;
	} else {
		PRINCESS.ai_command = AI_WALK_LEFT;
		PRINCESS.ai_right = false;
		PRINCESS.ai_left = true;
	}
	PRINCESS.ai_down = false;
	PRINCESS.ai_jump = false;
	PRINCESS.ai_shortjump = false;
	PRINCESS.ai_up = false;
	PRINCESS.ai_ready = true;
	PRINCESS.ai_timer = 0;

}



// Funcion SetEagle();
void SetEagle(u8 pos) {

	// Reinicia los parametros del Aguila
	EAGLE.show = false;
	EAGLE.done = false;
	EAGLE.created[0] = false, EAGLE.created[1] = false;
	EAGLE.on_screen[0] = false, EAGLE.on_screen[1] = false;

	// Flags de movimiento
	EAGLE.mov_left = false, EAGLE.mov_right = false;
	EAGLE.mov_up = false, EAGLE.mov_down = false;

	// Datos de estado de la animacion
	EAGLE.frame = 0, EAGLE.frame_cnt = 0, EAGLE.anim = EAGLE_ANIM_FLY;

	// Datos de la posicion de la Aguila (Centro del Sprite)
	EAGLE.pos_x = RANDOM_POS[pos].x;
	EAGLE.pos_y = (RANDOM_POS[pos].y - EAGLE.mov_y);
	EAGLE.pos_fx = (EAGLE.pos_x << 8);
	EAGLE.pos_fy = (EAGLE.pos_y << 8);

	// Datos de la IA
	if ((rand() % 100) > 50) {
		EAGLE.ai_command = AI_MOVE_RIGHT;
		EAGLE.ai_right = true;
		EAGLE.ai_left = false;
	} else {
		EAGLE.ai_command = AI_MOVE_LEFT;
		EAGLE.ai_right = false;
		EAGLE.ai_left = true;
	}
	EAGLE.ai_down = false;
	EAGLE.ai_up = false;
	EAGLE.ai_ready = true;
	EAGLE.ai_timer = 0;
	EAGLE.ai_error = false;

}