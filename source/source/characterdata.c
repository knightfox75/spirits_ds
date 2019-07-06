/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos del personaje

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




// Funcion LoadDefaultCharacterData();
void LoadDefaultCharacterData(void) {

	// Datos del grafico del sprite del personaje
	SPRGFX[ID_CHARACTER].width = 64, SPRGFX[ID_CHARACTER].height = 64;

	// Carga los parametros estaticos del personaje
	CHARACTER.spr_up = 32, CHARACTER.spr_left = 31;
	CHARACTER.up[0] = 30, CHARACTER.up[1] = 14, CHARACTER.down = 31, CHARACTER.left = 11, CHARACTER.right = 12;

}



// Funcion LoadStartCharacterData();
void LoadStartCharacterData(void) {

	/*
	-------------------------------------------------
		Parametros iniciales del personaje
	-------------------------------------------------
	*/

	// Posicion inicial del personaje
	CHARACTER.pos_x = CHARACTER_START_X, CHARACTER.pos_y = CHARACTER_START_Y;
	CHARACTER.pos_fx = (CHARACTER.pos_x << 8), CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
	CHARACTER.flip = false;
	CHARACTER.stage = GetStage(CHARACTER.pos_x, CHARACTER.pos_y);
	// Control de pantalla
	CHARACTER.on_screen[0] = false, CHARACTER.on_screen[1] = false;
	CHARACTER.created[0] = false, CHARACTER.created[1] = false;
	// Flags de movimiento
	CHARACTER.mov_left = false, CHARACTER.mov_right = false;
	// Flags de salto
	CHARACTER.can_jump = false, CHARACTER.is_jump = false;
	// Control del salto
	CHARACTER.jump_direction = 0, CHARACTER.jump_height = 0, CHARACTER.air_speed = 0;
	// Flags de caida
	CHARACTER.fall = false;
	CHARACTER.force_down = false;
	// Flags de escalera
	CHARACTER.stair_up = false, CHARACTER.stair_down = false, CHARACTER.in_stair = false;
	// Datos de estado de la animacion
	CHARACTER.duck = 0;
	CHARACTER.frame = 0, CHARACTER.frame_cnt = 0, CHARACTER.anim = CHARACTER_ANIM_STANDBY;
	CHARACTER.spell = false;

	// Vida inicial del personaje
	CHARACTER.energy = (40 << 3);
	CHARACTER.damage = CHARACTER.energy;
	CHARACTER.lives = 3;

	// Control de inmunidad
	CHARACTER.immunity = 0, CHARACTER.show = true;

	// Backup del estado actual
	CharacterBackupPos();

}
