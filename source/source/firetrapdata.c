/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de carga de datos
	de las hogueras

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





// Funcion LoadDefaultFiretrapData();
void LoadDefaultFiretrapData(void) {

	/*
	-------------------------------------------------
		Carga la info de las trampas de fuego
	-------------------------------------------------
	*/

	// Firetrap nº00 (Stage 08)
	FIRETRAP[0].pos_x = 1832, FIRETRAP[0].pos_y = 1488;
	FIRETRAP[0].size_x = 64, FIRETRAP[0].size_y = 32;
	FIRETRAP[0].spr_x = 1832, FIRETRAP[0].spr_y = 1488;
	FIRETRAP[0].stage = 8;

	// Firetrap nº01 (Stage 18)
	FIRETRAP[1].pos_x = 3120, FIRETRAP[1].pos_y = 1872;
	FIRETRAP[1].size_x = 64, FIRETRAP[1].size_y = 32;
	FIRETRAP[1].spr_x = 3120, FIRETRAP[1].spr_y = 1872;
	FIRETRAP[1].stage = 18;

	// Firetrap nº02 (Stage 18)
	FIRETRAP[2].pos_x = 4000, FIRETRAP[2].pos_y = 1823;
	FIRETRAP[2].size_x = 64, FIRETRAP[2].size_y = 81;
	FIRETRAP[2].spr_x = 4000, FIRETRAP[2].spr_y = 1872;
	FIRETRAP[2].stage = 18;

}



// Funcion LoadStartFiretrapData();
void LoadStartFiretrapData(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s16 n = 0;
	u8 screen = 0;

	/*
	-------------------------------------------------
		Todos las hogueras en posicion inicial
	-------------------------------------------------
	*/

	for (n = 0; n < FIRETRAP_NUM; n ++) {
		// Inicializa la animacion
		FIRETRAP[n].frame = (int)(rand() % 3);
		FIRETRAP[n].frame_cnt = 0;
		// Resetea los parametros de visualizacion de las trampas
		for (screen = 0; screen < 2; screen ++) {
            // Resetea la puesta en pantalla
			FIRETRAP[n].on_screen[screen] = false;
			FIRETRAP[n].created[screen] = false;
		}
	}

}
