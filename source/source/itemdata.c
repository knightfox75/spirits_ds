/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los datos
	iniciales de los items

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





// Funcion LoadDefaultItemData();
void LoadDefaultItemData(void) {

	// Datos del grafico del sprite del pedestal
	SPRGFX[ID_BASE].width = 32, SPRGFX[ID_BASE].height = 64, SPRGFX[ID_BASE].pal = SPRITE_8BITS_PAL;
	// Datos del grafico del sprite de la bola
	SPRGFX[ID_BALL].width = 32, SPRGFX[ID_BALL].height = 32, SPRGFX[ID_BALL].pal = SPRITE_8BITS_PAL;
	// Datos del grafico del sprite del libro de hechizos
	SPRGFX[ID_BOOK].width = 64, SPRGFX[ID_BOOK].height = 64, SPRGFX[ID_BOOK].pal = SPRITE_8BITS_PAL;
	// Datos del grafico del sprite de la varita magica
	SPRGFX[ID_WAND].width = 32, SPRGFX[ID_WAND].height = 64, SPRGFX[ID_WAND].pal = SPRITE_8BITS_PAL;

	// Datos del tamaño del sprite del pedestal
	PEDESTAL[0].width = 32, PEDESTAL[0].height = 48, PEDESTAL[0].mov_x = 15, PEDESTAL[0].mov_y = 47;
	PEDESTAL[1].width = 32, PEDESTAL[1].height = 48, PEDESTAL[1].mov_x = 15, PEDESTAL[1].mov_y = 47;
	// Datos del tamaño del sprite de la bola
	CRISTALLBALL.width = 27, CRISTALLBALL.height = 27, CRISTALLBALL.mov_x = 13, CRISTALLBALL.mov_y = 75;
	// Datos del tamaño del sprite del libro de hechizos
	SPELLBOOK.width = 48, SPELLBOOK.height = 42, SPELLBOOK.mov_x = 23, SPELLBOOK.mov_y = 89;
	// Datos del grafico del sprite de la varita magica
	MAGICWAND.width = 16, MAGICWAND.height = 46, MAGICWAND.mov_x = 7, MAGICWAND.mov_y = 45;

}



// Funcion SetCristallBall();
void SetCristallBall(u8 pos) {

	// Reinicia los parametros de la bola
	CRISTALLBALL.show = true;
	CRISTALLBALL.done = false;
	CRISTALLBALL.created[0] = false, CRISTALLBALL.created[1] = false;
	CRISTALLBALL.on_screen[0] = false, CRISTALLBALL.on_screen[1] = false;

	// Datos de la posicion de la bola
	CRISTALLBALL.cam_x = RANDOM_POS[pos].x;
	CRISTALLBALL.cam_y = RANDOM_POS[pos].y;
	CRISTALLBALL.pos_x = (RANDOM_POS[pos].x - CRISTALLBALL.mov_x);
	CRISTALLBALL.pos_y = (RANDOM_POS[pos].y - CRISTALLBALL.mov_y);
	CRISTALLBALL.stage = RANDOM_POS[pos].stage;

	// Reinicia los parametros del pedestal
	PEDESTAL[0].show = true;
	PEDESTAL[0].created[0] = false, PEDESTAL[0].created[1] = false;
	PEDESTAL[0].on_screen[0] = false, PEDESTAL[0].on_screen[1] = false;

	// Datos de la posicion del pedestal
	PEDESTAL[0].cam_x = RANDOM_POS[pos].x;
	PEDESTAL[0].cam_y = RANDOM_POS[pos].y;
	PEDESTAL[0].pos_x = (RANDOM_POS[pos].x - PEDESTAL[0].mov_x);
	PEDESTAL[0].pos_y = (RANDOM_POS[pos].y - PEDESTAL[0].mov_y);
	PEDESTAL[0].stage = RANDOM_POS[pos].stage;

}



// Funcion SetSpellbook();
void SetSpellbook(u8 pos) {

	// Reinicia los parametros del libro de hechizos
	SPELLBOOK.show = false;
	SPELLBOOK.done = false;
	SPELLBOOK.created[0] = false, SPELLBOOK.created[1] = false;
	SPELLBOOK.on_screen[0] = false, SPELLBOOK.on_screen[1] = false;

	// Datos de la posicion del libro de hechizos
	SPELLBOOK.cam_x = RANDOM_POS[pos].x;
	SPELLBOOK.cam_y = RANDOM_POS[pos].y;
	SPELLBOOK.pos_x = (RANDOM_POS[pos].x - SPELLBOOK.mov_x);
	SPELLBOOK.pos_y = (RANDOM_POS[pos].y - SPELLBOOK.mov_y);
	SPELLBOOK.stage = RANDOM_POS[pos].stage;

	// Reinicia los parametros del pedestal
	PEDESTAL[1].show = false;
	PEDESTAL[1].created[0] = false, PEDESTAL[1].created[1] = false;
	PEDESTAL[1].on_screen[0] = false, PEDESTAL[1].on_screen[1] = false;

	// Datos de la posicion del pedestal
	PEDESTAL[1].cam_x = RANDOM_POS[pos].x;
	PEDESTAL[1].cam_y = RANDOM_POS[pos].y;
	PEDESTAL[1].pos_x = (RANDOM_POS[pos].x - PEDESTAL[1].mov_x);
	PEDESTAL[1].pos_y = (RANDOM_POS[pos].y - PEDESTAL[1].mov_y);
	PEDESTAL[1].stage = RANDOM_POS[pos].stage;

}



// Funcion SetMagicwand();
void SetMagicwand(u8 pos) {

	// Reinicia los parametros de la bola
	MAGICWAND.show = false;
	MAGICWAND.done = false;
	MAGICWAND.created[0] = false, MAGICWAND.created[1] = false;
	MAGICWAND.on_screen[0] = false, MAGICWAND.on_screen[1] = false;

	// Datos de la posicion de la bola
	MAGICWAND.cam_x = RANDOM_POS[pos].x;
	MAGICWAND.cam_y = RANDOM_POS[pos].y;
	MAGICWAND.pos_x = (RANDOM_POS[pos].x - MAGICWAND.mov_x);
	MAGICWAND.pos_y = (RANDOM_POS[pos].y - MAGICWAND.mov_y);
	MAGICWAND.stage = RANDOM_POS[pos].stage;

}
