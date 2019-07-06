/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos
	del gato y diablo

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





// Funcion LoadDefaultDevilcatData();
void LoadDefaultDevilcatData(void) {

	// Datos de los graficos de los Sprites
	DEVILGFX[0].width = 64, DEVILGFX[0].height = 32, DEVILGFX[0].pal = CAT_SPR_PAL;			// Gato
	DEVILGFX[1].width = 64, DEVILGFX[1].height = 64, DEVILGFX[1].pal = DEVIL_SPR_PAL;		// Diablo
	DEVILGFX[2].width = 32, DEVILGFX[2].height = 16, DEVILGFX[2].pal = ARROW_SPR_PAL;		// Flecha del diablo
	DEVILGFX[3].width = 32, DEVILGFX[3].height = 32, DEVILGFX[2].pal = DRAGONEYE_SPR_PAL;	// Ojos del Dragon

	// Datos del Sprite del gato
	CAT.spr_up = 15, CAT.spr_left = 31;
	CAT.up = 15, CAT.down = 16, CAT.left = 22, CAT.right = 23;

	// Datos del Sprite del Diablo
	DEVIL.spr_up = 31, DEVIL.spr_left = 31;
	DEVIL.up = 28, DEVIL.down = 29, DEVIL.left = 28, DEVIL.right = 29;

	// Datos del Sprite de la felcha del diablo
	ARROW.spr_up = 7, ARROW.spr_left = 15;
	ARROW.up = 7, ARROW.down = 8, ARROW.left = 15, ARROW.right = 16;

}



// Funcion LoadStartDevilcatData();
void LoadStartDevilcatData(void) {

	// Reinicia el gato
	CAT.activated = false, CAT.timer = ((rand() % CAT_RAND_TIME) + CAT_MIN_TIME);
	CAT.cancel = false;
	CAT.created[0] = false, CAT.created[1] = false;
	CAT.on_screen[0] = false, CAT.on_screen[1] = false;
	CAT.frame = 0, CAT.frame_cnt = 0;
	CAT.fall = false; CAT.air_speed = 0;
	CAT.counter = 0;

	// Reinicia al diablo
	DEVIL.activated = false, DEVIL.timer = ((rand() % DEVIL_RAND_TIME) + DEVIL_MIN_TIME);
	DEVIL.created[0] = false, DEVIL.created[1] = false;
	DEVIL.on_screen[0] = false, DEVIL.on_screen[1] = false;
	DEVIL.frame = 0, DEVIL.frame_cnt = 0;

	// Y la flecha que dispara el demonio
	ARROW.activated = false; ARROW.shot = false;
	ARROW.cancel = false;
	ARROW.created[0] = false, ARROW.created[1] = false;
	ARROW.on_screen[0] = false, ARROW.on_screen[1] = false;

	// Inicializa los ojos del dragon
	DRAGONEYE.on_screen[0] = false, DRAGONEYE.on_screen[1] = false;
	DRAGONEYE.created[0] = false, DRAGONEYE.created[1] = false;
	DRAGONEYE.frame = 0, DRAGONEYE.frame_cnt = 0, DRAGONEYE.animation = 0;
	DRAGONEYE.active = false;

}
