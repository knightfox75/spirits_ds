/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Compo

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



// Funcion Compo();
void Compo(void) {

	/*
	-------------------------------------------------
		Inicializaciones
	-------------------------------------------------
	*/

	// Resetealo todo
	ResetAll();

	// Variables locales
	u8 thread = 0;				// Thread de ejecuccion
	bool loop = true;			// Control de loop
	bool next = false;			// Flag de cambio de thread
	s32 timer = 0;


	/*
	-------------------------------------------------
		Carga de archivos
	-------------------------------------------------
	*/

	NF_LoadTiledBg("compo/bg/neo2012_up", "neo_up", 256, 256);
	NF_LoadTiledBg("compo/bg/neo2012_down", "neo_down", 256, 256);




	/*
	-------------------------------------------------
		Muestra la pantallas
	-------------------------------------------------
	*/
	
	// Brillo
	setBrightness(3, -16);

	// Bucle de ejecucion
	while (loop) {

		// Arbol de threads
		switch (thread) {

			// Crea los fondos
			case 0:
				NF_CreateTiledBg(0, 3, "neo_up");
				NF_CreateTiledBg(1, 3, "neo_down");
				next = true;
				break;

			// Fade In
			case 1:
				FadeIn(3, 64);
				next = true;
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
				FadeOut(3, 64);
				next = true;
				loop = false;
				break;

			// Nada por defecto
			default:
				break;

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