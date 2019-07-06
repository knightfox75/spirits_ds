/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos
	del hechizo

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





// Funcion LoadDefaultSpellData();
void LoadDefaultSpellData(void) {

	// Datos del grafico del sprite del disparo de hechizo
	SPRGFX[ID_SPELL].width = 32, SPRGFX[ID_SPELL].height = 32, SPRGFX[ID_SPELL].pal = SPRITE_8BITS_PAL;

	// Carga los parametros estaticos del hechizo
	SPELL.spr_up = 15, SPELL.spr_left = 15;
	SPELL.up = 9, SPELL.down = 10, SPELL.left = 7, SPELL.right = 8;

}



// Funcion LoadStartSpellData();
void LoadStartSpellData(void) {

	/*
	-------------------------------------------------
		Parametros iniciales del hechizo
	-------------------------------------------------
	*/

	// Posicion inicial del hechizo
	SPELL.pos_x = 0, SPELL.pos_y = 0;
	SPELL.pos_fx = 0, SPELL.pos_fy = 0;
	SPELL.flip = 0;
	// Control de pantalla
	SPELL.on_screen[0] = false, SPELL.on_screen[1] = false;
	SPELL.created[0] = false, SPELL.created[1] = false;
	// Animacion del hechizo
	SPELL.frame = 0, SPELL.frame_cnt = 0;
	// Contol del hechizo
	SPELL.active = false, SPELL.shot = false;
	SPELL.cancel = false;
	SPELL.speed = 0;

}