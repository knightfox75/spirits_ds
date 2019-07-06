/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos de las puertas

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





// Funcion LoadDefaultDoorData();
void LoadDefaultDoorData(void) {

	/*
	-------------------------------------------------
		Carga la info de las puertas (Graficos)
	-------------------------------------------------
	*/

	// Gfx n�00 - Puerta n�00
	DOORGFX[0].pal = DOOR_SPR_PAL;
	DOORGFX[0].width = 32, DOORGFX[0].height = 32;
	// Gfx n�01 - Puerta n�01
	DOORGFX[1].pal = DOOR_SPR_PAL;
	DOORGFX[1].width = 16, DOORGFX[1].height = 32;
	// Gfx n�02 - Puerta n�02
	DOORGFX[2].pal = DOOR_SPR_PAL;
	DOORGFX[2].width = 32, DOORGFX[2].height = 32;
	// Gfx n�03 - Puerta n�02/03
	DOORGFX[3].pal = DOOR_SPR_PAL;
	DOORGFX[3].width = 32, DOORGFX[3].height = 16;
	// Gfx n�04 - Puerta n�03
	DOORGFX[4].pal = DOOR_SPR_PAL;
	DOORGFX[4].width = 32, DOORGFX[4].height = 64;
	// Gfx n�05 - Puerta n�04/05
	DOORGFX[5].pal = DOOR_SPR_PAL;
	DOORGFX[5].width = 64, DOORGFX[5].height = 64;
	// Gfx n�06 - Puerta n�04/05
	DOORGFX[6].pal = DOOR_SPR_PAL;
	DOORGFX[6].width = 64, DOORGFX[6].height = 64;


	/*
	-------------------------------------------------
		Carga la info de las puertas
		(Gfx que usa cada puerta)
	-------------------------------------------------
	*/

	// Puerta n�00 (Stage 1) [2 partes] [GFX n�00]
	DOOR[0].ram_gfx[0] = ID_DOOR, DOOR[0].ram_gfx[1] = ID_DOOR;
	DOOR[0].door_x = 1616, DOOR[0].door_y = 96;
	DOOR[0].size_x = 32, DOOR[0].size_y = 64;
	// Puerta n�01 (Stage 4) [3 partes] [GFX n�01]
	DOOR[1].ram_gfx[0] = (ID_DOOR + 1), DOOR[1].ram_gfx[1] = (ID_DOOR + 1), DOOR[1].ram_gfx[2] = (ID_DOOR + 1);
	DOOR[1].door_x = 1600, DOOR[1].door_y = 640;
	DOOR[1].size_x = 16, DOOR[1].size_y = 96;
	// Puerta n�02 (Stage 5) [4 partes] [GFX n�02 y n�03]
	DOOR[2].ram_gfx[0] = (ID_DOOR + 2), DOOR[2].ram_gfx[1] = (ID_DOOR + 2),	DOOR[2].ram_gfx[2] = (ID_DOOR + 2), DOOR[2].ram_gfx[3] = (ID_DOOR + 3);
	DOOR[2].door_x = 1776, DOOR[2].door_y = 816;
	DOOR[2].size_x = 32, DOOR[2].size_y = 112;
	// Puerta n�03 (Stage 7) [3 partes] [GFX n�04 y n�03]
	DOOR[3].ram_gfx[0] = (ID_DOOR + 4), DOOR[3].ram_gfx[1] = (ID_DOOR + 4),	DOOR[3].ram_gfx[2] = (ID_DOOR + 3);
	DOOR[3].door_x = 256, DOOR[3].door_y = 1168;
	DOOR[3].size_x = 32, DOOR[3].size_y = 144;
	// Puerta n�04 (Stage 14) [2 partes] [GFX n�05 y n�06]
	DOOR[4].ram_gfx[0] = (ID_DOOR + 5), DOOR[4].ram_gfx[1] = (ID_DOOR + 6);
	DOOR[4].door_x = 4072, DOOR[4].door_y = 1008;
	DOOR[4].size_x = 48, DOOR[4].size_y = 112;
	// Puerta n�05 (Stage 14) [2 partes] [GFX n�05 y n�06]
	DOOR[5].ram_gfx[0] = (ID_DOOR + 5), DOOR[5].ram_gfx[1] = (ID_DOOR + 6);
	DOOR[5].door_x = 4456, DOOR[5].door_y = 1008;
	DOOR[5].size_x = 48, DOOR[5].size_y = 112;
	// Puerta n�06 (Stage 17) [2 partes] [GFX n�00]
	DOOR[6].ram_gfx[0] = ID_DOOR, DOOR[6].ram_gfx[1] = ID_DOOR;
	DOOR[6].door_x = 4864, DOOR[6].door_y = 1632;
	DOOR[6].size_x = 32, DOOR[6].size_y = 64;

}



// Funcion LoadStartDoorData();
void LoadStartDoorData(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s16 n = 0;
	u8 screen = 0;
	u8 id = 0;

	/*
	-------------------------------------------------
		Resetea el FIFO de sprites
		de las puertas
	-------------------------------------------------
	*/

	for (screen = 0; screen < 2; screen ++) {
		for (id = 0; id < DOOR_SPR_NUM; id ++) {
			DOOR_SPR[screen].id[id] = (id + DOOR_SPR_ID);
			DOOR_SPR[screen].in_use[id] = false;
		}
	}


	/*
	-------------------------------------------------
		Todas las puertas
		cerradas y ocultas
	-------------------------------------------------
	*/

	for (n = 0; n < DOOR_NUM; n ++) {
		// Por defecto, las puertas estan cerradas
		DOOR[n].activated = false;
		EventCloseDoor(n);
		// Resetea las posiciones de las puertas
		DOOR[n].pos_x = DOOR[n].door_x, DOOR[n].pos_y = DOOR[n].door_y;
		DOOR[n].pos_fx = (DOOR[n].pos_x << 8), DOOR[n].pos_fy = (DOOR[n].pos_y << 8);
		// Resetea los parametros de visualizacion de las puertas
		for (screen = 0; screen < 2; screen ++) {
			for (id = 0; id < DOOR_PARTS_NUM; id ++) {
				// Resetea la puesta en pantalla
				DOOR[n].on_screen[screen][id] = false;
				DOOR[n].created[screen][id] = false;
				// Resetea los datos del FIFO
				DOOR[n].spr_id[screen][id] = 255;
				DOOR[n].vram_gfx[screen][id] = 255;
			}
		}
	}

}
