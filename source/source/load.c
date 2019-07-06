/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de archivos

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



// Funcion LoadGameFiles();
void LoadGameFiles(void) {

	/*
	-------------------------------------------------
		Carga los fondos
	-------------------------------------------------
	*/

	// Carga los fondos dependiendo si se esta en modo 8 bits o remake
	if (GAMEOPTIONS[0].remake) {
		LoadBackgroundsHq();
	} else {
		LoadBackgrounds8bits();
	}



	/*
	-------------------------------------------------
		Carga los sprites
	-------------------------------------------------
	*/

	// Carga los sprites dependiendo si se esta en modo 8 bits o remake
	if (GAMEOPTIONS[0].remake) {
		LoadSpritesHq();
	} else {
		LoadSprites8bits();
	}



	/*
	-------------------------------------------------
		Carga los mapas de colisiones
	-------------------------------------------------
	*/

	// Carga los mapas
	NF_LoadColisionMap("maps/mainmap", MAINMAP_SLOT, MAINMAP_WIDTH, MAINMAP_HEIGHT);



	/*
	-------------------------------------------------
		Carga los efectos de sonido
	-------------------------------------------------
	*/
	if (GAMEOPTIONS[0].remake) {
		NF_LoadRawSound("snd/raw/hq_spell", SFX_ID_SPELL, 22050, 0);
		NF_LoadRawSound("snd/raw/hq_damage", SFX_ID_DAMAGE, 22050, 0);
		NF_LoadRawSound("snd/raw/hq_dead", SFX_ID_DEAD, 22050, 0);
	} else {
		// Efectos de sonidos
		NF_LoadRawSound("snd/raw/8bits_tack", SFX_ID_TACK, 22050, 0);
		NF_LoadRawSound("snd/raw/8bits_tick", SFX_ID_TICK, 22050, 0);
		NF_LoadRawSound("snd/raw/8bits_spell", SFX_ID_SPELL, 22050, 0);
		NF_LoadRawSound("snd/raw/8bits_fall", SFX_ID_FALL, 22050, 0);
		NF_LoadRawSound("snd/raw/8bits_damage", SFX_ID_DAMAGE, 22050, 0);
	}

}



// Funcion LoadBackgrounds8bits();
void LoadBackgrounds8bits(void) {

	// Variables locales
	char filename[128];			// Nombre de archivo
	char name[32];				// Nombre del fondo
	u8 n = 0;

	// Carga los fondos
	for (n = 1; n <= 19; n ++) {
		sprintf(filename, "8bits/game/bg/stg%02d", n);
		sprintf(name, "stg%02d", n);
		NF_LoadTiledBg(filename, name, STAGE[n].bg_width[1], STAGE[n].bg_height[1]);
	}
	// Carga el minimapa
	NF_LoadTiledBg("8bits/game/bg/minimap", "minimap", 768, 512);
	NF_LoadTiledBg("8bits/game/bg/fogmap", "fogmap", 768, 512);
	// Guarda la RAM ID del fondo de la niebla del minimapa
	MINIMAP.rambuffer = GetBgRamId("fogmap");

}



// Funcion LoadBackgroundsHq();
void LoadBackgroundsHq(void) {

	// Variables locales
	char filename[128];			// Nombre de archivo
	char name[32];				// Nombre del fondo
	u8 n = 0;
	u8 layer = 0;

	// Carga los fondos
	for (n = 1; n <= 19; n ++) {
		for (layer = 1; layer <= 2; layer ++) {
			sprintf(filename, "hq/game/bg/stg%02d_%d", n, layer);
			sprintf(name, "stg%02d_%d", n, layer);
			NF_LoadTiledBg(filename, name, STAGE[n].bg_width[1], STAGE[n].bg_height[1]);
		}
	}

	// Carga decodados comunes
	for (n = 1; n <= 2; n ++) {
		sprintf(filename, "hq/game/bg/forest%02d", n);
		sprintf(name, "forest%02d", n);
		NF_LoadTiledBg(filename, name, 1280, 256);		// Bosque
	}
	NF_LoadTiledBg("hq/game/bg/catacomb01", "catacomb01", 1280, 256);		// Catacumbas

	// Carga el minimapa
	NF_LoadTiledBg("hq/game/bg/minimap", "minimap", 768, 512);
	NF_LoadTiledBg("hq/game/bg/fogmap", "fogmap", 768, 512);
	// Guarda la RAM ID del fondo de la niebla del minimapa
	MINIMAP.rambuffer = GetBgRamId("fogmap");

}



// Funcion LoadSprites8bits();
void LoadSprites8bits(void) {

	// Variables locales
	char filename[128];			// Nombre de archivo
	u8 n = 0;

	// Carga los Sprites de personajes, enemigos, objetos...
	for (n = 0; n < TOTAL_SPRITE_GFX; n ++) {
		sprintf(filename, "8bits/game/sprite/spr%02d", n);
		NF_LoadSpriteGfx(filename, (ID_CHARACTER + n), SPRGFX[n].width, SPRGFX[n].height);
	}

	// Carga los Sprites de los enemigos aleatorios...
	for (n = 0; n < TOTAL_DEVIL_GFX; n ++) {
		sprintf(filename, "8bits/game/sprite/devil%02d", n);
		NF_LoadSpriteGfx(filename, (ID_CAT + n), DEVILGFX[n].width, DEVILGFX[n].height);
	}

	// Carga los Sprites de las puertas...
	for (n = 0; n < TOTAL_DOOR_GFX; n ++) {
		sprintf(filename, "8bits/game/sprite/door%02d", n);
		NF_LoadSpriteGfx(filename, (ID_DOOR + n), DOORGFX[n].width, DOORGFX[n].height);
	}

	// Carga los Sprites de los muros mobiles...
	for (n = 0; n < TOTAL_HWALL_GFX; n ++) {
		sprintf(filename, "8bits/game/sprite/hwall%02d", n);
		NF_LoadSpriteGfx(filename, (ID_HWALL + n), HWALLGFX[n].width, HWALLGFX[n].height);
	}

	// Carga los Sprites de las trampas...
	NF_LoadSpriteGfx("8bits/game/sprite/trap00", ID_TRAP, TRAPGFX[0].width, TRAPGFX[0].height);

	// Carga los Sprites de las lamparas...
	NF_LoadSpriteGfx("8bits/game/sprite/lamp00", ID_LAMP, 64, 64);

	// Carga los Sprites de las hogueras...
	NF_LoadSpriteGfx("8bits/game/sprite/firetrap00", ID_FIRETRAP, 64, 32);

	// Carga los Sprites de la GUI
	for (n = 0; n < TOTAL_GUI_GFX; n ++) {
		sprintf(filename, "8bits/game/sprite/gui%02d", n);
		NF_LoadSpriteGfx(filename, (ID_GUI + n), GUIGFX[n].width, GUIGFX[n].height);
	}

	// Carga los Sprites de la pausa
	NF_LoadSpriteGfx("8bits/game/sprite/pause", ID_PAUSE, 64, 64);

	// Carga los Sprites del Minimapa
	for (n = 0; n < TOTAL_MINIMAP_GFX; n ++) {
		sprintf(filename, "8bits/game/sprite/minimap%02d", n);
		NF_LoadSpriteGfx(filename, (ID_MINIMAP + n), 16, 16);
	}

	// Carga las paletas de los sprites
	NF_LoadSpritePal("8bits/game/sprite/spr8bits", SPRITE_8BITS_PAL);

}



// Funcion LoadSpritesHq();
void LoadSpritesHq(void) {

	// Variables locales
	char filename[128];			// Nombre de archivo
	u8 n = 0;

	// Carga los Sprites de personajes, enemigos, objetos...
	for (n = 0; n < TOTAL_SPRITE_GFX; n ++) {
		switch (n) {
			case 0: case 11:					// Paleta 00
				sprintf(filename, "hq/game/sprite/pal00/spr%02d", n);
				break;
			case 4: case 5: case 10:			// Paleta 01
				sprintf(filename, "hq/game/sprite/pal01/spr%02d", n);
				break;
			case 6: case 7: case 8: case 9:		// Paleta 02
				sprintf(filename, "hq/game/sprite/pal02/spr%02d", n);
				break;
			case 1: case 2: case 3:				// Paleta 03
				sprintf(filename, "hq/game/sprite/pal03/spr%02d", n);
				break;
			case 12:							// Paleta 10
				sprintf(filename, "hq/game/sprite/pal10/spr%02d", n);
				break;
		}
		NF_LoadSpriteGfx(filename, (ID_CHARACTER + n), SPRGFX[n].width, SPRGFX[n].height);
	}

	// Carga los Sprites de los enemigos aleatorios...
	for (n = 0; n < TOTAL_DEVIL_GFX; n ++) {
		sprintf(filename, "hq/game/sprite/pal05/devil%02d", n);
		NF_LoadSpriteGfx(filename, (ID_CAT + n), DEVILGFX[n].width, DEVILGFX[n].height);
	}

	// Carga los Sprites de las puertas...
	for (n = 0; n < TOTAL_DOOR_GFX; n ++) {
		sprintf(filename, "hq/game/sprite/pal11/door%02d", n);
		NF_LoadSpriteGfx(filename, (ID_DOOR + n), DOORGFX[n].width, DOORGFX[n].height);
	}

	// Carga los Sprites de los muros mobiles...
	for (n = 0; n < TOTAL_HWALL_GFX; n ++) {
		sprintf(filename, "hq/game/sprite/pal12/hwall%02d", n);
		NF_LoadSpriteGfx(filename, (ID_HWALL + n), HWALLGFX[n].width, HWALLGFX[n].height);
	}

	// Carga los Sprites de las trampas...
	NF_LoadSpriteGfx("hq/game/sprite/pal13/trap00", ID_TRAP, TRAPGFX[0].width, TRAPGFX[0].height);

	// Carga los Sprites de las lamparas...
	NF_LoadSpriteGfx("hq/game/sprite/pal14/lamp00", ID_LAMP, 64, 64);

	// Carga los Sprites de las hogueras...
	NF_LoadSpriteGfx("hq/game/sprite/pal15/firetrap00", ID_FIRETRAP, 64, 32);

	// Carga los Sprites de las antorchas y velas...
	NF_LoadSpriteGfx("hq/game/sprite/pal15/torch00", ID_TORCH, 16, 32);
	NF_LoadSpriteGfx("hq/game/sprite/pal15/flame00", ID_FLAME, 16, 16);

	// Carga los Sprites de la GUI
	for (n = 0; n < (TOTAL_GUI_GFX + 2); n ++) {
		sprintf(filename, "hq/game/sprite/pal04/gui%02d", n);
		NF_LoadSpriteGfx(filename, (ID_GUI + n), GUIGFX[n].width, GUIGFX[n].height);
	}

	// Carga el sprite de la pausa
	NF_LoadSpriteGfx("hq/game/sprite/pal09/pause", ID_PAUSE, 64, 64);

	// Carga los Sprites del Minimapa
	for (n = 0; n < TOTAL_MINIMAP_GFX; n ++) {
		sprintf(filename, "hq/game/sprite/pal06/minimap%02d", n);
		NF_LoadSpriteGfx(filename, (ID_MINIMAP + n), 16, 16);
	}

	// Carga las paletas de los sprites
	for (n = 0; n < 16; n ++) {
		switch (n) {
			// Grupo paletas Hq
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
				sprintf(filename, "hq/game/sprite/pal/pal%02d", n);
				NF_LoadSpritePal(filename, n);
				break;
			// Nada
			default:
				break;
		}
	}

}


