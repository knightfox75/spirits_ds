/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos de las lamparas

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





// Funcion LoadDefaultLampData();
void LoadDefaultLampData(void) {

	/*
	-------------------------------------------------
		Carga la info de las lamparas
		(posicion arriba/izquierda de cada lampara)
	-------------------------------------------------
	*/

	// Lampara nº00 (Stage 3)
	LAMP[0].lamp_x = 895, LAMP[0].lamp_y = 415; LAMP[0].stage = 3;

	// Lampara nº01 (Stage 5)
	LAMP[1].lamp_x = 1264, LAMP[1].lamp_y = 800; LAMP[1].stage = 5;

	// Lampara nº02 (Stage 6)
	LAMP[2].lamp_x = 192, LAMP[2].lamp_y = 976; LAMP[2].stage = 6;

	// Lampara nº03 (Stage 10)
	LAMP[3].lamp_x = 2848, LAMP[3].lamp_y = 976; LAMP[3].stage = 10;

	// Lampara nº04 (Stage 11)
	LAMP[4].lamp_x = 3968, LAMP[4].lamp_y = 416; LAMP[4].stage = 11;

	// Lampara nº05 (Stage 14)
	LAMP[5].lamp_x = 3952, LAMP[5].lamp_y = 976; LAMP[5].stage = 14;

}



// Funcion LoadStartLampData();
void LoadStartLampData(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s16 n = 0;
	u8 screen = 0;

	/*
	-------------------------------------------------
		Todos las lamparas listas
		y en posicion inicial
	-------------------------------------------------
	*/

	for (n = 0; n < LAMP_NUM; n ++) {
		// Por defecto, las trampas estan listas
		LAMP[n].activated = false;
		LAMP[n].fall = false;
		LAMP[n].timer = 0;
		// Resetea las posiciones de las trampas
		LAMP[n].pos_x = LAMP[n].lamp_x, LAMP[n].pos_y = LAMP[n].lamp_y;
		LAMP[n].pos_fx = (LAMP[n].pos_x << 8), LAMP[n].pos_fy = (LAMP[n].pos_y << 8);
		// Resetea los parametros de la animacion
		LAMP[n].frame = (int)(rand() % 4);
		LAMP[n].frame_cnt = 0;
		// Resetea los parametros de visualizacion de las trampas
		for (screen = 0; screen < 2; screen ++) {
            // Resetea la puesta en pantalla
			LAMP[n].on_screen[screen] = false;
			LAMP[n].created[screen] = false;
		}
	}

}
