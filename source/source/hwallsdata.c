/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos de los muros mobiles

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





// Funcion LoadDefaultHwallData();
void LoadDefaultHwallData(void) {

	/*
	-------------------------------------------------
	  Carga la info de los muros ocultos (Graficos)
	-------------------------------------------------
	*/

	// Gfx nº00 - Muro nº00
	HWALLGFX[0].pal = HWALL_SPR_PAL;
	HWALLGFX[0].width = 32, HWALLGFX[0].height = 16;
	// Gfx nº01 - Muro nº00
	HWALLGFX[1].pal = HWALL_SPR_PAL;
	HWALLGFX[1].width = 32, HWALLGFX[1].height = 16;
	// Gfx nº02 - Muro nº01
	HWALLGFX[2].pal = HWALL_SPR_PAL;
	HWALLGFX[2].width = 16, HWALLGFX[2].height = 32;
	// Gfx nº03 - Muro nº02
	HWALLGFX[3].pal = HWALL_SPR_PAL;
	HWALLGFX[3].width = 32, HWALLGFX[3].height = 16;
	// Gfx nº04 - Muro nº03
	HWALLGFX[4].pal = HWALL_SPR_PAL;
	HWALLGFX[4].width = 32, HWALLGFX[4].height = 16;
	// Gfx nº05 - Muro nº03
	HWALLGFX[5].pal = HWALL_SPR_PAL;
	HWALLGFX[5].width = 32, HWALLGFX[5].height = 16;


	/*
	-------------------------------------------------
		Carga la info de las puertas
		(Gfx que usa cada puerta)
	-------------------------------------------------
	*/

	// Muro nº00 (Stage 16) [2 partes] [GFX nº00 y nº01]
	HWALL[0].ram_gfx[0] = ID_HWALL, HWALL[0].ram_gfx[1] = (ID_HWALL + 1);
	HWALL[0].hwall_x = 4384, HWALL[0].hwall_y = 1488;
	HWALL[0].size_x = 64, HWALL[0].size_y = 16;

	// Muro nº01 (Stage 16) [2 partes] [GFX nº02] [Vertical]
	HWALL[1].ram_gfx[0] = (ID_HWALL + 2), HWALL[1].ram_gfx[1] = (ID_HWALL + 2);
	HWALL[1].hwall_x = 4128, HWALL[1].hwall_y = 1440;
	HWALL[1].size_x = 16, HWALL[1].size_y = 64;

	// Muro nº02 (Stage 16) [2 partes] [GFX nº03] [Horizontal]
	HWALL[2].ram_gfx[0] = (ID_HWALL + 3), HWALL[2].ram_gfx[1] = (ID_HWALL + 3);
	HWALL[2].hwall_x = 4128, HWALL[2].hwall_y = 1504;
	HWALL[2].size_x = 64, HWALL[2].size_y = 16;

	// Muro nº03 (Stage 17) [2 partes] [GFX nº04 y nº05]
	HWALL[3].ram_gfx[0] = (ID_HWALL + 4), HWALL[3].ram_gfx[1] = (ID_HWALL + 5);
	HWALL[3].hwall_x = 3120, HWALL[3].hwall_y = 1696;
	HWALL[3].size_x = 64, HWALL[3].size_y = 16;

}



// Funcion LoadStartHwallData();
void LoadStartHwallData(void) {

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
		de los muros mobiles
	-------------------------------------------------
	*/

	for (screen = 0; screen < 2; screen ++) {
		for (id = 0; id < HWALL_SPR_NUM; id ++) {
			HWALL_SPR[screen].id[id] = (id + HWALL_SPR_ID);
			HWALL_SPR[screen].in_use[id] = false;
		}
	}


	/*
	-------------------------------------------------
		Todos los muros mobiles
		cerrados y en posicion inicial
	-------------------------------------------------
	*/

	for (n = 0; n < HWALL_NUM; n ++) {
		// Por defecto, las puertas estan cerradas
		HWALL[n].activated = false;
		EventCloseHwall(n);
		// Resetea las posiciones de las puertas
		HWALL[n].pos_x = HWALL[n].hwall_x, HWALL[n].pos_y = HWALL[n].hwall_y;
		HWALL[n].pos_fx = (HWALL[n].pos_x << 8), HWALL[n].pos_fy = (HWALL[n].pos_y << 8);
		// Resetea los parametros de visualizacion de las puertas
		for (screen = 0; screen < 2; screen ++) {
			for (id = 0; id < HWALL_PARTS_NUM; id ++) {
				// Resetea la puesta en pantalla
				HWALL[n].on_screen[screen][id] = false;
				HWALL[n].created[screen][id] = false;
				// Resetea los datos del FIFO
				HWALL[n].spr_id[screen][id] = 255;
				HWALL[n].vram_gfx[screen][id] = 255;
			}
		}
	}

}
