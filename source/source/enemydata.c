/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos de los enemigos

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



// Funcion LoadDefaultEnemyData();
void LoadDefaultEnemyData(void) {

	// Variables
	u8 n = 0;

	// Informacion de los graficos de los sprites
	SPRGFX[ID_GOUL].width = 64, SPRGFX[ID_GOUL].height = 64, SPRGFX[ID_GOUL].pal = ENEMY_SPR_PAL;
	SPRGFX[ID_PHANTOM].width = 64, SPRGFX[ID_PHANTOM].height = 64, SPRGFX[ID_PHANTOM].pal = ENEMY_SPR_PAL;
	SPRGFX[ID_WOLF].width = 64, SPRGFX[ID_WOLF].height = 64, SPRGFX[ID_WOLF].pal = ENEMY_SPR_PAL;

	// Carga los parametros estaticos del Goul
	for (n = 0; n < ENEMY_NUM_GOUL; n ++) {
		GOUL[n].ram_gfx = ID_GOUL;
		GOUL[n].spr_up = 31, GOUL[n].spr_left = 31;
		GOUL[n].up = 27, GOUL[n].down = 32, GOUL[n].left = 23, GOUL[n].right = 24;
	}

	// Carga los parametros estaticos del Phantom
	for (n = 0; n < ENEMY_NUM_PHANTOM; n ++) {
		PHANTOM[n].ram_gfx = ID_PHANTOM;
		PHANTOM[n].spr_up = 31, PHANTOM[n].spr_left = 31;
		PHANTOM[n].up = 29, PHANTOM[n].down = 32, PHANTOM[n].left = 23, PHANTOM[n].right = 24;
	}

	// Carga los parametros estaticos del Wolf
	for (n = 0; n < ENEMY_NUM_WOLF; n ++) {
		WOLF[n].ram_gfx = ID_WOLF;
		WOLF[n].spr_up = 31, WOLF[n].spr_left = 31;
		WOLF[n].up = 27, WOLF[n].down = 32, WOLF[n].left = 21, WOLF[n].right = 22;
	}

}



// Funcion LoadStartEnemyData();
void LoadStartEnemyData(void) {

	/*
	-------------------------------------------------
		Parametros iniciales de los enemigos
	-------------------------------------------------
	*/

	// Gestion de Sprites
	u8 screen = 0;
	u8 id = 0;
	for (screen = 0; screen < 2; screen ++) {
		for (id = 0; id < ENEMY_SPR_NUM; id ++) {
			ENEMY_SPR[screen].id[id] = (id + ENEMY_SPR_ID);
			ENEMY_SPR[screen].in_use[id] = false;
		}
	}

	LoadStartGoulData();			// Gouls
	LoadStartPhantomData();			// Fantasmas
	LoadStartWolfData();			// Lobos

}



// Funcion LoadStartGoulData();
void LoadStartGoulData(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u8 n = 0;


	/*
	-------------------------------------------------
		Parametros iniciales de los Gouls (Unicos)
	-------------------------------------------------
	*/

	// Y base = 127

	// Goul 0 - Stage 1
	GOUL[0].pos_x = 664, GOUL[0].pos_y = 127;
	GOUL[0].pos_fx = (GOUL[0].pos_x << 8), GOUL[0].pos_fy = (GOUL[0].pos_y << 8);

	// Goul 1 - Stage 5
	GOUL[1].pos_x = 700, GOUL[1].pos_y = 895;
	GOUL[1].pos_fx = (GOUL[1].pos_x << 8), GOUL[1].pos_fy = (GOUL[1].pos_y << 8);

	// Goul 2 - Stage 8
	GOUL[2].pos_x = 700, GOUL[2].pos_y = 1487;
	GOUL[2].pos_fx = (GOUL[2].pos_x << 8), GOUL[2].pos_fy = (GOUL[2].pos_y << 8);

	// Goul 3 - Stage 13
	GOUL[3].pos_x = 4272, GOUL[3].pos_y = 895;
	GOUL[3].pos_fx = (GOUL[3].pos_x << 8), GOUL[3].pos_fy = (GOUL[3].pos_y << 8);

	// Goul 4 - Stage 16
	GOUL[4].pos_x = 3372, GOUL[4].pos_y = 1471;
	GOUL[4].pos_fx = (GOUL[4].pos_x << 8), GOUL[4].pos_fy = (GOUL[4].pos_y << 8);

	// Goul 5 - Stage 18
	GOUL[5].pos_x = 4572, GOUL[5].pos_y = 1855;
	GOUL[5].pos_fx = (GOUL[5].pos_x << 8), GOUL[5].pos_fy = (GOUL[5].pos_y << 8);


	/*
	-------------------------------------------------
		Parametros iniciales de los Gouls (Comunes)
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_GOUL; n ++) {
		// Control de pantalla
		GOUL[n].on_screen[0] = false, GOUL[n].on_screen[1] = false;
		GOUL[n].created[0] = false, GOUL[n].created[1] = false;
		// Datos de estado de la animacion
		GOUL[n].frame = 0, GOUL[n].frame_cnt = 0;
		// Datos del movimiento
		GOUL[n].speed = 256;
		if ((rand() % 100) < 50) GOUL[n].speed = -GOUL[n].speed;
		if (GOUL[n].speed > 0) {
			GOUL[n].flip = false;
		} else {
			GOUL[n].flip = true;
		}
		GOUL[n].stage = GetStage(GOUL[n].pos_x, GOUL[n].pos_y);
		// Datos adicionales
		GOUL[n].sleep = 0;
		GOUL[n].ignore = ENEMY_AI_IGNORE;
		GOUL[n].delay = 0;
		// Resetea los datos del FIFO
		GOUL[n].spr_id[0] = 255, GOUL[n].vram_gfx[0] = 255;
		GOUL[n].spr_id[1] = 255, GOUL[n].vram_gfx[1] = 255;
	}

}



// Funcion LoadStartPhantomData();
void LoadStartPhantomData(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u8 n = 0;


	/*
	-------------------------------------------------
		Parametros iniciales de los Phantoms (Unicos)
	-------------------------------------------------
	*/
	
	// Y base = 80

	// Phantom 0 - Stage 2
	PHANTOM[0].pos_x = 200, PHANTOM[0].pos_y = 288;
	PHANTOM[0].pos_fx = (PHANTOM[0].pos_x << 8), PHANTOM[0].pos_fy = (PHANTOM[0].pos_y << 8);

	// Phantom 1 - Stage 3
	PHANTOM[1].pos_x = 700, PHANTOM[1].pos_y = 480;
	PHANTOM[1].pos_fx = (PHANTOM[1].pos_x << 8), PHANTOM[1].pos_fy = (PHANTOM[1].pos_y << 8);

	// Phantom 2 - Stage 4
	PHANTOM[2].pos_x = 1100, PHANTOM[2].pos_y = 672;
	PHANTOM[2].pos_fx = (PHANTOM[2].pos_x << 8), PHANTOM[2].pos_fy = (PHANTOM[2].pos_y << 8);

	// Phantom 3 - Stage 6
	PHANTOM[3].pos_x = 800, PHANTOM[3].pos_y = 1056;
	PHANTOM[3].pos_fx = (PHANTOM[3].pos_x << 8), PHANTOM[3].pos_fy = (PHANTOM[3].pos_y << 8);

	// Phantom 4 - Stage 12
	PHANTOM[4].pos_x = 3532, PHANTOM[4].pos_y = 672;
	PHANTOM[4].pos_fx = (PHANTOM[4].pos_x << 8), PHANTOM[4].pos_fy = (PHANTOM[4].pos_y << 8);

	// Phantom 5 - Stage 12
	PHANTOM[5].pos_x = 4452, PHANTOM[5].pos_y = 672;
	PHANTOM[5].pos_fx = (PHANTOM[5].pos_x << 8), PHANTOM[5].pos_fy = (PHANTOM[5].pos_y << 8);

	// Phantom 6 - Stage 13
	PHANTOM[6].pos_x = 3472, PHANTOM[6].pos_y = 864;
	PHANTOM[6].pos_fx = (PHANTOM[6].pos_x << 8), PHANTOM[6].pos_fy = (PHANTOM[6].pos_y << 8);

	// Phantom 7 - Stage 14
	PHANTOM[7].pos_x = 3572, PHANTOM[7].pos_y = 1056;
	PHANTOM[7].pos_fx = (PHANTOM[7].pos_x << 8), PHANTOM[7].pos_fy = (PHANTOM[7].pos_y << 8);

	// Phantom 8 - Stage 17
	PHANTOM[8].pos_x = 3972, PHANTOM[8].pos_y = 1632;
	PHANTOM[8].pos_fx = (PHANTOM[8].pos_x << 8), PHANTOM[8].pos_fy = (PHANTOM[8].pos_y << 8);

	// Phantom 9 - Stage 18
	PHANTOM[9].pos_x = 3872, PHANTOM[9].pos_y = 1824;
	PHANTOM[9].pos_fx = (PHANTOM[9].pos_x << 8), PHANTOM[9].pos_fy = (PHANTOM[9].pos_y << 8);


	/*
	-------------------------------------------------
		Parametros iniciales de los Phantoms (Comunes)
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_PHANTOM; n ++) {
		// Control de pantalla
		PHANTOM[n].on_screen[0] = false, PHANTOM[n].on_screen[1] = false;
		PHANTOM[n].created[0] = false, PHANTOM[n].created[1] = false;
		// Datos de estado de la animacion
		PHANTOM[n].frame = 0, PHANTOM[n].frame_cnt = 0;
		// Datos del movimiento
		PHANTOM[n].speed = 224;
		if ((rand() % 100) < 50) PHANTOM[n].speed = -PHANTOM[n].speed;
		if (PHANTOM[n].speed > 0) {
			PHANTOM[n].flip = false;
		} else {
			PHANTOM[n].flip = true;
		}
		PHANTOM[n].stage = GetStage(PHANTOM[n].pos_x, PHANTOM[n].pos_y);
		// Datos adicionales
		PHANTOM[n].sleep = 0;
		PHANTOM[n].ignore = ENEMY_AI_IGNORE;
		PHANTOM[n].delay = 0;
		// Resetea los datos del FIFO
		PHANTOM[n].spr_id[0] = 255, PHANTOM[n].vram_gfx[0] = 255;
		PHANTOM[n].spr_id[1] = 255, PHANTOM[n].vram_gfx[1] = 255;
	}

}



// Funcion LoadStartWolfData();
void LoadStartWolfData(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u8 n = 0;


	/*
	-------------------------------------------------
		Parametros iniciales de los Wolfs (Unicos)
	-------------------------------------------------
	*/

	// Y base = 127

	// Wolf 0 - Stage 7
	WOLF[0].pos_x = 1000, WOLF[0].pos_y = 1279;
	WOLF[0].pos_fx = (WOLF[0].pos_x << 8), WOLF[0].pos_fy = (WOLF[0].pos_y << 8);

	// Wolf 1 - Stage 8
	WOLF[1].pos_x = 1400, WOLF[1].pos_y = 1471;
	WOLF[1].pos_fx = (WOLF[1].pos_x << 8), WOLF[1].pos_fy = (WOLF[1].pos_y << 8);

	// Wolf 2 - Stage 9
	WOLF[2].pos_x = 2420, WOLF[2].pos_y = 911;
	WOLF[2].pos_fx = (WOLF[2].pos_x << 8), WOLF[2].pos_fy = (WOLF[2].pos_y << 8);

	// Wolf 3 - Stage 11
	WOLF[3].pos_x = 4172, WOLF[3].pos_y = 511;
	WOLF[3].pos_fx = (WOLF[3].pos_x << 8), WOLF[3].pos_fy = (WOLF[3].pos_y << 8);


	/*
	-------------------------------------------------
		Parametros iniciales de los Wolfs (Comunes)
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_WOLF; n ++) {
		// Control de pantalla
		WOLF[n].on_screen[0] = false, WOLF[n].on_screen[1] = false;
		WOLF[n].created[0] = false, WOLF[n].created[1] = false;
		// Datos de estado de la animacion
		WOLF[n].frame = 0, WOLF[n].frame_cnt = 0;
		// Datos del movimiento
		WOLF[n].speed = 288;
		if ((rand() % 100) < 50) WOLF[n].speed = -WOLF[n].speed;
		if (WOLF[n].speed > 0) {
			WOLF[n].flip = false;
		} else {
			WOLF[n].flip = true;
		}
		WOLF[n].stage = GetStage(WOLF[n].pos_x, WOLF[n].pos_y);
		// Datos adicionales
		WOLF[n].sleep = 0;
		WOLF[n].ignore = ENEMY_AI_IGNORE;
		WOLF[n].delay = 0;
		// Resetea los datos del FIFO
		WOLF[n].spr_id[0] = 255, WOLF[n].vram_gfx[0] = 255;
		WOLF[n].spr_id[1] = 255, WOLF[n].vram_gfx[1] = 255;
	}

}

