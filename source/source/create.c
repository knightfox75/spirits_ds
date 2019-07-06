/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de creacion del juego

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



// Funcion CreateGameStage();
void CreateGameStage(void) {


	// Dependiendo si es modo remake o original
	if (GAMEOPTIONS[0].remake) {
		CreateVramSprites();	// Manda los graficos de la RAM a la VRAM (Sprites siempre en VRAM)
	} else {
		CreateScanlines();		// Crea los fondos para el efecto scanlines
	}
	
	// Tareas comunes en ambos modos
	CreatePalettes();	// Manda la paletas de la RAM a la VRAM
	GuiCreate();		// Crea la GUI en la pantalla inferior
	CameraMain();		// Genera los fondos y sprites del juego en ambas pantallas

}



// Funcion CreateVramSprites();
void CreateVramSprites(void) {

	// Variables
	u8 n = 0;

	// Manda los sprites fijos a VRAM
	for (n = 0; n < 2; n ++) {
		NF_VramSpriteGfx(n, ID_TORCH, TORCH_SPR_ID, false);
		NF_VramSpriteGfx(n, ID_FLAME, FLAME_SPR_ID, false);
	}

}



// Funcion  CreatePalettes();
void CreatePalettes(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/
	
	u8 screen = 0;


	/*
	-------------------------------------------------
		Carga las paletas de Sprites
		en VRAM (comunes a ambas pantallas)
	-------------------------------------------------
	*/

	for (screen = 0; screen < 2; screen ++) {

		if (GAMEOPTIONS[0].remake) {	// Modo Remake

			// Paleta Character
			NF_VramSpritePal(screen, CHARACTER_SPR_PAL, CHARACTER_SPR_PAL);
			// Paleta Items
			NF_VramSpritePal(screen, ITEM_SPR_PAL, ITEM_SPR_PAL);
			// Paleta NPC
			NF_VramSpritePal(screen, NPC_SPR_PAL, NPC_SPR_PAL);
			// Paleta Enemigos
			NF_VramSpritePal(screen, ENEMY_SPR_PAL, ENEMY_SPR_PAL);
			// Paleta Enemigos especiales
			NF_VramSpritePal(screen, DEVIL_SPR_PAL, DEVIL_SPR_PAL);
			// Paleta Interruptores
			NF_VramSpritePal(screen, SWITCH_SPR_PAL, SWITCH_SPR_PAL);
			// Paleta Puertas
			NF_VramSpritePal(screen, DOOR_SPR_PAL, DOOR_SPR_PAL);
			// Paleta Muros mobiles
			NF_VramSpritePal(screen, HWALL_SPR_PAL, HWALL_SPR_PAL);
			// Paleta Trampas
			NF_VramSpritePal(screen, TRAP_SPR_PAL, TRAP_SPR_PAL);
			// Paleta Lamparas
			NF_VramSpritePal(screen, LAMP_SPR_PAL, LAMP_SPR_PAL);
			// Paleta Hogueras
			NF_VramSpritePal(screen, FIRETRAP_SPR_PAL, FIRETRAP_SPR_PAL);

		} else {	// Modo original

			// Paleta Character
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, CHARACTER_SPR_PAL);
			// Paleta Items
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, ITEM_SPR_PAL);
			// Paleta NPC
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, NPC_SPR_PAL);
			// Paleta Enemigos
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, ENEMY_SPR_PAL);
			// Paleta Enemigos especiales
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, DEVIL_SPR_PAL);
			// Paleta Interruptores
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, SWITCH_SPR_PAL);
			// Paleta Puertas
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, DOOR_SPR_PAL);
			// Paleta Muros mobiles
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, HWALL_SPR_PAL);
			// Paleta Trampas
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, TRAP_SPR_PAL);
			// Paleta Lamparas
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, LAMP_SPR_PAL);
			// Paleta Hogueras
			NF_VramSpritePal(screen, SPRITE_8BITS_PAL, FIRETRAP_SPR_PAL);

		}

	}


	/*
	-------------------------------------------------
		Carga las paletas de Sprites
		en VRAM (pantalla superior)
	-------------------------------------------------
	*/

	if (GAMEOPTIONS[0].remake) {	// Modo Remake
		// Paleta PAUSE
		NF_VramSpritePal(0, PAUSE_SPR_PAL, PAUSE_SPR_PAL);
	} else {
		// Paleta PAUSE
		NF_VramSpritePal(0, SPRITE_8BITS_PAL, PAUSE_SPR_PAL);
	}


	/*
	-------------------------------------------------
		Carga las paletas de Sprites
		en VRAM (pantalla inferior)
	-------------------------------------------------
	*/

	if (GAMEOPTIONS[0].remake) {	// Modo Remake
		// Paleta GUI
		NF_VramSpritePal(1, GUI_SPR_PAL, GUI_SPR_PAL);
		// Paleta Minimapa
		NF_VramSpritePal(1, MINIMAP_SPR_PAL, MINIMAP_SPR_PAL);
	} else {
		// Paleta GUI
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, GUI_SPR_PAL);
		// Paleta Minimapa
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, MINIMAP_SPR_PAL);
	}

}