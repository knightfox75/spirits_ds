/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de presentacion

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



// Funcion Opening();
void Opening(void) {

	/*
	-------------------------------------------------
		Inicializaciones
	-------------------------------------------------
	*/

	// Resetealo todo
	ResetAll();

	// Variables locales
	char basepath[32];			// Path base
	char filename[128];			// Nombre de archivo
	char bgname[32];			// Nombre del fondo
	u8 thread = 0;				// Thread de ejecuccion
	bool loop = true;			// Control de loop
	bool next = false;			// Flag de cambio de thread
	s32 timer = 0;
	s16 n = 0;
	char temp[128];
	s32 fade = (16 << 8);
	bool fade_in = false;
	bool fade_out = false;

	// Prepara los cheats
	CHEATS.steep = 0;


	/*
	-------------------------------------------------
		Carga de archivos
	-------------------------------------------------
	*/

	// Carga los fondos
	if (GAMEOPTIONS[0].remake) {
		sprintf(basepath, "%s", "hq/opening/bg/");
	} else {
		sprintf(basepath, "%s", "8bits/opening/bg/");
	}
	for (n = 0; n < 4; n ++) {
		if (GAMEOPTIONS[0].remake) {
			sprintf(filename, "%sop%d_hq", basepath, n);
		} else {
			sprintf(filename, "%sop%d_8bits", basepath, n);
		}
		if (n == 3) {
			switch (GAMEOPTIONS[0].language) {
				case 0:		// Español
					sprintf(temp, "%s_es", filename);
					break;
				case 1:		// Ingles
					sprintf(temp, "%s_en", filename);
					break;
			}
			sprintf(filename, "%s", temp);
		}
		sprintf(bgname, "op%d", n);
		NF_LoadTiledBg(filename, bgname, 256, 256);
	}


	/*
	-------------------------------------------------
		Muestra la presentacion
	-------------------------------------------------
	*/
	
	// Brillo
	setBrightness(3, -16);

	// Crea las scanlines
	if (!GAMEOPTIONS[0].remake) CreateScanlines();

	// Bucle de ejecucion
	while (loop) {

		// Lee el teclado
		ReadKeypad();

		// Mira si se introduce el codigo de cheats
		CheatsEnable();

		// Arbol de threads
		switch (thread) {

			// Crea los fondos
			case 0:
				NF_CreateTiledBg(0, 3, "op0");
				NF_CreateTiledBg(1, 3, "op1");
				next = true;
				break;

			// Fade In
			case 1:
				fade_in = true;
				timer = 0;
				break;

			// Espera n Frames
			case 2:
				timer ++;
				if (timer >= 120) {
					next = true;
				}
				break;

			// Fade Out
			case 3:
				fade_out = true;
				break;

			// Cambia los fondos
			case 4:
				NF_DeleteTiledBg(0, 3);
				NF_DeleteTiledBg(1, 3);
				NF_CreateTiledBg(0, 3, "op2");
				NF_CreateTiledBg(1, 3, "op3");
				next = true;
				break;

			// Fade In
			case 5:
				fade_in = true;
				timer = 0;
				break;

			// Espera n Frames
			case 6:
				timer ++;
				if (timer >= 120) {
					next = true;
				}
				break;

			// Fade Out
			case 7:
				fade_out = true;
				break;

			// Salida
			case 8:
				loop = false;
				break;

			// Nada por defecto
			default:
				break;

		}

		// Fade IN
		if (fade_in) {
			fade -= 64;
			if (fade <= 0) {
				fade = 0;
				fade_in = false;
				next = true;
			}
			setBrightness(3, (0 - (fade >> 8)));
		}

		// Fade OUT
		if (fade_out) {
			fade += 64;
			if (fade >= (16 << 8)) {
				fade = (16 << 8);
				fade_out = false;
				next = true;
			}
			setBrightness(3, (0 - (fade >> 8)));
		}

		// Cambia de thread si es necesario
		if (next) {
			next = false;
			thread ++;
		}

		// Espera al sincronismo
		swiWaitForVBlank();

	}

}