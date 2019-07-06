/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos de las trampas

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





// Funcion LoadDefaultTrapData();
void LoadDefaultTrapData(void) {

	/*
	-------------------------------------------------
	  Carga la info de las trampas (Graficos)
	-------------------------------------------------
	*/

	// Gfx nº00 - Trampas nº00 y nº01
	TRAPGFX[0].pal = TRAP_SPR_PAL;
	TRAPGFX[0].width = 64, TRAPGFX[0].height = 64;


	/*
	-------------------------------------------------
		Carga la info de las trampas
		(Gfx que usa cada trampa)
	-------------------------------------------------
	*/

	// Trampa nº00 (Stage 16) [2 partes] [GFX nº00]
	TRAP[0].ram_gfx[0] = ID_TRAP, TRAP[0].ram_gfx[1] = ID_TRAP;
	TRAP[0].trap_x = 4288, TRAP[0].trap_y = 1344;
	TRAP[0].size_x = 128, TRAP[0].size_y = 64;

	// Trampa nº01 (Stage 17) [2 partes] [GFX nº00]
	TRAP[1].ram_gfx[0] = ID_TRAP, TRAP[1].ram_gfx[1] = ID_TRAP;
	TRAP[1].trap_x = 3104, TRAP[1].trap_y = 1551;
	TRAP[1].size_x = 128, TRAP[1].size_y = 64;

}



// Funcion LoadStartTrapData();
void LoadStartTrapData(void) {

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
		de las trampas
	-------------------------------------------------
	*/

	for (screen = 0; screen < 2; screen ++) {
		for (id = 0; id < TRAP_SPR_NUM; id ++) {
			TRAP_SPR[screen].id[id] = (id + TRAP_SPR_ID);
			TRAP_SPR[screen].in_use[id] = false;
		}
	}


	/*
	-------------------------------------------------
		Todos las trampas cerradas
		y en posicion inicial
	-------------------------------------------------
	*/

	for (n = 0; n < TRAP_NUM; n ++) {
		// Por defecto, las trampas estan listas
		TRAP[n].activated = false;
		// Resetea las posiciones de las trampas
		TRAP[n].pos_x = TRAP[n].trap_x, TRAP[n].pos_y = TRAP[n].trap_y;
		TRAP[n].pos_fx = (TRAP[n].pos_x << 8), TRAP[n].pos_fy = (TRAP[n].pos_y << 8);
		// Resetea los parametros de visualizacion de las trampas
		for (screen = 0; screen < 2; screen ++) {
			for (id = 0; id < TRAP_PARTS_NUM; id ++) {
				// Resetea la puesta en pantalla
				TRAP[n].on_screen[screen][id] = false;
				TRAP[n].created[screen][id] = false;
				// Resetea los datos del FIFO
				TRAP[n].spr_id[screen][id] = 255;
				TRAP[n].vram_gfx[screen][id] = 255;
			}
		}
	}

}
