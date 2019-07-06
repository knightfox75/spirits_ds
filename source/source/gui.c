/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la GUI

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





// Funcion GuiMain();
void GuiMain(void) {

	// Actualiza la barra de vida
	GuiUpdateLiveBar();

	// Actualiza el contador de vidas
	GuiUpdateLivesCounter();

}



// Funcion GuiCreate();
void GuiCreate(void) {

	// Variables
	u8 n = 0;

	/*
	Crea los items de la GUI
	*/
	// Bola de cristal Gfx nº00
	NF_VramSpriteGfx(1, ID_GUI, GUI_SPRITE_CRISTALLBALL, true);
	NF_CreateSprite(1, GUI_SPRITE_CRISTALLBALL, GUI_SPRITE_CRISTALLBALL, GUI_SPR_PAL, 8, 56);
	
	// Libro de hechizos Gfx nº01
	NF_VramSpriteGfx(1, (ID_GUI + 1), GUI_SPRITE_SPELLBOOK, true);
	NF_CreateSprite(1, GUI_SPRITE_SPELLBOOK, GUI_SPRITE_SPELLBOOK, GUI_SPR_PAL, 8, 80);
	
	// Varita Magica Gfx nº02
	NF_VramSpriteGfx(1, (ID_GUI + 2), GUI_SPRITE_MAGICWAND, true);
	NF_CreateSprite(1, GUI_SPRITE_MAGICWAND, GUI_SPRITE_MAGICWAND, GUI_SPR_PAL, 8, 112);
	
	// Hechizo maestro Gfx nº03
	NF_VramSpriteGfx(1, (ID_GUI + 3), GUI_SPRITE_MASTERSPELL, true);
	NF_CreateSprite(1, GUI_SPRITE_MASTERSPELL, GUI_SPRITE_MASTERSPELL, GUI_SPR_PAL, 8, 144);

	// Contador de vidas restantes Gfx nº04
	NF_VramSpriteGfx(1, (ID_GUI + 4), GUI_SPRITE_LIVE1, true);
	NF_CreateSprite(1, GUI_SPRITE_LIVE1, GUI_SPRITE_LIVE1, GUI_SPR_PAL, 200, 8);
	NF_VramSpriteGfx(1, (ID_GUI + 4), GUI_SPRITE_LIVE2, true);
	NF_CreateSprite(1, GUI_SPRITE_LIVE2, GUI_SPRITE_LIVE2, GUI_SPR_PAL, 216, 8);
	NF_VramSpriteGfx(1, (ID_GUI + 4), GUI_SPRITE_LIVE3, true);
	NF_CreateSprite(1, GUI_SPRITE_LIVE3, GUI_SPRITE_LIVE3, GUI_SPR_PAL, 232, 8);
	
	// Barra de vida (rojo) Gfx nº05
	NF_VramSpriteGfx(1, (ID_GUI + 5), GUI_SPRITE_LB_RED, true);
	NF_CreateSprite(1, GUI_SPRITE_LB_RED, GUI_SPRITE_LB_RED, GUI_SPR_PAL, 8, 8);
	
	// Barra de vida (amarillo) Gfx nº06 y nº07
	if (GAMEOPTIONS[0].remake) {
		NF_VramSpriteGfx(1, (ID_GUI + 6), GUI_SPRITE_LB_YELLOW1, true);
		NF_CreateSprite(1, GUI_SPRITE_LB_YELLOW1, GUI_SPRITE_LB_YELLOW1, GUI_SPR_PAL, 40, 8);
		NF_VramSpriteGfx(1, (ID_GUI + 7), GUI_SPRITE_LB_YELLOW2, true);
		NF_CreateSprite(1, GUI_SPRITE_LB_YELLOW2, GUI_SPRITE_LB_YELLOW2, GUI_SPR_PAL, 72, 8);
	} else {	// Gfx nº06
		NF_VramSpriteGfx(1, (ID_GUI + 6), GUI_SPRITE_LB_YELLOW1, true);
		NF_CreateSprite(1, GUI_SPRITE_LB_YELLOW1, GUI_SPRITE_LB_YELLOW1, GUI_SPR_PAL, 40, 8);
		NF_VramSpriteGfx(1, (ID_GUI + 6), GUI_SPRITE_LB_YELLOW2, true);
		NF_CreateSprite(1, GUI_SPRITE_LB_YELLOW2, GUI_SPRITE_LB_YELLOW2, GUI_SPR_PAL, 72, 8);
	} 
	
	// Barra de vida (Verde) Gfx nº08 y nº09
	if (GAMEOPTIONS[0].remake) {
		NF_VramSpriteGfx(1, (ID_GUI + 8), GUI_SPRITE_LB_GREEN1, true);
		NF_CreateSprite(1, GUI_SPRITE_LB_GREEN1, GUI_SPRITE_LB_GREEN1, GUI_SPR_PAL, 104, 8);
		NF_VramSpriteGfx(1, (ID_GUI + 9), GUI_SPRITE_LB_GREEN2, true);
		NF_CreateSprite(1, GUI_SPRITE_LB_GREEN2, GUI_SPRITE_LB_GREEN2, GUI_SPR_PAL, 136, 8);
	} else {	// Gfx nº07
		NF_VramSpriteGfx(1, (ID_GUI + 7), GUI_SPRITE_LB_GREEN1, true);
		NF_CreateSprite(1, GUI_SPRITE_LB_GREEN1, GUI_SPRITE_LB_GREEN1, GUI_SPR_PAL, 104, 8);
		NF_VramSpriteGfx(1, (ID_GUI + 7), GUI_SPRITE_LB_GREEN2, true);
		NF_CreateSprite(1, GUI_SPRITE_LB_GREEN2, GUI_SPRITE_LB_GREEN2, GUI_SPR_PAL, 136, 8);
	}


	// Coloca todos los items en la capa correspondiente
	// y en el frame 0 por defecto
	for (n = 0; n < GUI_TOTAL_ITEMS; n ++) {
		NF_SpriteLayer(1, (GUI_SPR_ID + n), GUI_SPRITE_LAYER);
		NF_SpriteFrame(1, (GUI_SPR_ID + n), 0);
	}

	// Actualiza el estado de la GUI
	GUI.update_energy_bar = true;
	GUI.update_lives_counter = true;
	GuiMain();

}



// Funcion GuiUpdateLiveBar();
void GuiUpdateLiveBar(void) {

	// Variables
	s8 points;									// Puntos totales a mostrar
	s8 red, yellow1, yellow2, green1, green2;	// Puntos de cada sub-barra	

	// Si necesitas actualizarte...
	if (GUI.update_energy_bar) {

		// Calcula los puntos de la barra
		points = (CHARACTER.energy >> 3);

		// Calcula los frames de la barra de vida
		green2 = (8 - (40 - points));
		if (green2 < 0) green2 = 0;
		green1 = (8 - (32 - points));
		if (green1 < 0) green1 = 0;
		if (green1 > 8) green1 = 8;
		yellow2 = (8 - (24 - points));
		if (yellow2 < 0) yellow2 = 0;
		if (yellow2 > 8) yellow2 = 8;
		yellow1 = (8 - (16 - points));
		if (yellow1 < 0) yellow1 = 0;
		if (yellow1 > 8) yellow1 = 8;
		red = (8 - (8 - points));
		if (red < 0) red = 0;
		if (red > 8) red = 8;

		// Actualiza la barra
		NF_SpriteFrame(1, GUI_SPRITE_LB_GREEN2, green2);
		NF_SpriteFrame(1, GUI_SPRITE_LB_GREEN1, green1);
		NF_SpriteFrame(1, GUI_SPRITE_LB_YELLOW2, yellow2);
		NF_SpriteFrame(1, GUI_SPRITE_LB_YELLOW1, yellow1);
		NF_SpriteFrame(1, GUI_SPRITE_LB_RED, red);

		// Marca la actualizacion como realizada
		GUI.update_energy_bar = false;

	}

}



// Funcion GuiUpdateLivesCounter();
void GuiUpdateLivesCounter(void) {

	// Variables
	s8 live1 = 0, live2 = 0, live3 = 0;

	// Si debe ser actualizado el contador de vidas...
	if (GUI.update_lives_counter) {

		// Segun las vidas restantes
		switch (CHARACTER.lives) {
			case 0:
				live1 = 1;
				live2 = 1;
				live3 = 1;
				break;
			case 1:
				live1 = 1;
				live2 = 1;
				live3 = 0;
				break;
			case 2:
				live1 = 1;
				live2 = 0;
				live3 = 0;
				break;
			case 3:
				live1 = 0;
				live2 = 0;
				live3 = 0;
				break;
		}

		// Actualiza los iconos
		NF_SpriteFrame(1, GUI_SPRITE_LIVE1, live1);
		NF_SpriteFrame(1, GUI_SPRITE_LIVE2, live2);
		NF_SpriteFrame(1, GUI_SPRITE_LIVE3, live3);

		// Marcalo como actualizado
		GUI.update_lives_counter = false;

	}

}



// Funcion GuiPause();
void GuiPause(void) {

	/*
	Crea los items del menu de pausa
	*/
	NF_VramSpriteGfx(0, ID_PAUSE, PAUSE_SPRITE, true);
	NF_VramSpriteGfx(0, ID_PAUSE, (PAUSE_SPRITE + 1), true);
	NF_CreateSprite(0, PAUSE_SPRITE, PAUSE_SPRITE, PAUSE_SPR_PAL, 64, 32);
	NF_CreateSprite(0, (PAUSE_SPRITE + 1), (PAUSE_SPRITE + 1), PAUSE_SPR_PAL, 128, 32);
	NF_SpriteLayer(0, PAUSE_SPRITE, GUI_SPRITE_LAYER);
	NF_SpriteLayer(0, (PAUSE_SPRITE + 1), GUI_SPRITE_LAYER);
	if (GAMEOPTIONS[0].language == 0) {
		NF_SpriteFrame(0, PAUSE_SPRITE, 0);
		NF_SpriteFrame(0, (PAUSE_SPRITE + 1), 2);
	} else {
		NF_SpriteFrame(0, PAUSE_SPRITE, 1);
		NF_SpriteFrame(0, (PAUSE_SPRITE + 1), 3);
	}
	NF_ShowSprite(0, PAUSE_SPRITE, false);
	NF_ShowSprite(0, (PAUSE_SPRITE + 1), false);

}