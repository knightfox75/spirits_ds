/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos de los interruptores

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





// Funcion LoadDefaultSwitchData();
void LoadDefaultSwtichData(void) {

	// Variables
	u8 n = 0;

	// Parametros de los graficos usados por los interruptores
	SPRGFX[ID_SWITCH].width = 32, SPRGFX[ID_SWITCH].height = 16, SPRGFX[ID_SWITCH].pal = SWITCH_SPR_PAL;

	// Carga los parametros estaticos del Switch (comunes)
	for (n = 0; n < SWITCH_NUM; n ++) {
		SWITCH[n].ram_gfx = ID_SWITCH;
		SWITCH[n].spr_up = 7, SWITCH[n].spr_left = 15;
	}

	// Carga los parametros estaticos del Switch (unicos)
	SWITCH[0].pos_x = 1599, SWITCH[0].pos_y = 71;
	SWITCH[1].pos_x = 1311, SWITCH[1].pos_y = 455;
	SWITCH[2].pos_x = 1679, SWITCH[2].pos_y = 791;
	SWITCH[3].pos_x = 527, SWITCH[3].pos_y = 1223;
	SWITCH[4].pos_x = 3375, SWITCH[4].pos_y = 999;
	SWITCH[5].pos_x = 4303, SWITCH[5].pos_y = 1399;
	SWITCH[6].pos_x = 4335, SWITCH[6].pos_y = 1399;
	SWITCH[7].pos_x = 4367, SWITCH[7].pos_y = 1399;
	SWITCH[8].pos_x = 4815, SWITCH[8].pos_y = 1575;
	SWITCH[9].pos_x = 3135, SWITCH[9].pos_y = 1607;
	SWITCH[10].pos_x = 3167, SWITCH[10].pos_y = 1607;

}



// Funcion LoadStartSwitchData();
void LoadStartSwitchData(void) {

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
		de los interruptores
	-------------------------------------------------
	*/

	for (screen = 0; screen < 2; screen ++) {
		for (id = 0; id < SWITCH_SPR_NUM; id ++) {
			SWITCH_SPR[screen].id[id] = (id + SWITCH_SPR_ID);
			SWITCH_SPR[screen].in_use[id] = false;
		}
	}


	/*
	-------------------------------------------------
		Todos los interruptores
		desconectados y ocultos
	-------------------------------------------------
	*/

	for (n = 0; n < SWITCH_NUM; n ++) {
		// Parametros iniciales de los interruptores
		SWITCH[n].activated = false;
		SWITCH[n].on_screen[0] = false, SWITCH[n].on_screen[1] = false;
		SWITCH[n].created[0] = false, SWITCH[n].created[1] = false;
		// Resetea los datos del FIFO
		SWITCH[n].spr_id[0] = 255, SWITCH[n].vram_gfx[0] = 255;
		SWITCH[n].spr_id[1] = 255, SWITCH[n].vram_gfx[1] = 255;
	}

	// Y los especiales (se desplazan con las trampas), en su posicion inicial
	SWITCH[5].pos_y = 1399;		// Trampa 00
	SWITCH[6].pos_y = 1399;
	SWITCH[7].pos_y = 1399;
	SWITCH[9].pos_y = 1607;		// Trampa 01
	SWITCH[10].pos_y = 1607;

}
