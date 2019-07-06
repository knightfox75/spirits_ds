/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos de la GUI

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





// Funcion LoadDefaultGuiData();
void LoadDefaultGuiData(void){

	// Variables
	u8 n = 0;

	/*
	-------------------------------------------------
		Carga la info de la GUI (Graficos)
	-------------------------------------------------
	*/

	// Gfx nº00 - Bola de cristal
	GUIGFX[0].pal = GUI_SPR_PAL;
	GUIGFX[0].width = 16, GUIGFX[0].height = 16;

	// Gfx nº01 - Libro de Hechizos
	GUIGFX[1].pal = GUI_SPR_PAL;
	GUIGFX[1].width = 32, GUIGFX[1].height = 32;

	// Gfx nº02 - Varita magica
	GUIGFX[2].pal = GUI_SPR_PAL;
	GUIGFX[2].width = 16, GUIGFX[2].height = 32;

	// Gfx nº03 - Hechizo maestro
	GUIGFX[3].pal = GUI_SPR_PAL;
	GUIGFX[3].width = 32, GUIGFX[3].height = 64;

	// Gfx nº04 - Contador de vidas
	GUIGFX[4].pal = GUI_SPR_PAL;
	GUIGFX[4].width = 16, GUIGFX[4].height = 32;

	// Gfx nº05/nº09 - Barras de vida
	for (n = 5; n <= 9; n ++) {
		GUIGFX[n].pal = GUI_SPR_PAL;
		GUIGFX[n].width = 32, GUIGFX[n].height = 16;
	}

}



// Funcion LoadStartGuiData();
void LoadStartGuiData(void){

	/*
	-------------------------------------------------
		Info inicial de la GUI
	-------------------------------------------------
	*/

	// Flags de actualizacion
	GUI.update_energy_bar = false;
	GUI.update_lives_counter = false;


	/*
	-------------------------------------------------
		Info inicial del minimapa
	-------------------------------------------------
	*/

	// Control del minimapa
	MINIMAP.active = false;
	MINIMAP.bg_x = 0, MINIMAP.bg_y = 0;
	MINIMAP.frame = 0, MINIMAP.frame_cnt = 0;

}