/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la pantalla de carga

	Requiere DevkitARM
	Requiere NightFox's Lib

	Codigo por NightFox
	http://www.nightfoxandco.com
	Inicio 02 de Septiembre del 2011

	(c)2008 - 2012 NightFox & Co.

-------------------------------------------------
*/



// Includes C
#include <stdio.h>
#include <time.h>

// Includes propietarios NDS
#include <nds.h>

// Includes NightFox's Lib
#include <nf_lib.h>

//Incluye las librerias del juego
#include "includes.h"





// Funcion LoadingIn();
void LoadingIn(void) {

	// Variables
	u8 n = 0;
	char filename[64];
	s32 y = 111;

	// Carga y crea los fondos
	if (GAMEOPTIONS[0].remake) {
		if (GAMEOPTIONS[0].language == 0) {
			NF_LoadTiledBg("hq/load/bg/load_hq_es", "load", 256, 256);
		} else {
			NF_LoadTiledBg("hq/load/bg/load_hq_en", "load", 256, 256);
		}
		NF_LoadTiledBg("hq/load/bg/loadbg_hq", "loadbg", 512, 256);
	} else {
		if (GAMEOPTIONS[0].language == 0) {
			NF_LoadTiledBg("8bits/load/bg/load_8b_es", "load", 256, 256);
		} else {
			NF_LoadTiledBg("8bits/load/bg/load_8b_en", "load", 256, 256);
		}
		NF_LoadTiledBg("8bits/load/bg/loadbg_8b", "loadbg", 512, 256);
	}
	NF_CreateTiledBg(0, 3, "load");
	NF_CreateTiledBg(1, 3, "loadbg");

	// Carga el sprite y crea el sprite
	srand(time(NULL));
	n = (((int)(rand() % 3)) + 1);
	if (n == 2) y = 63;
	if (GAMEOPTIONS[0].remake) {
		sprintf(filename, "hq/game/sprite/pal03/spr%02d", n);
		NF_LoadSpriteGfx(filename, 127, 64, 64);
		NF_LoadSpritePal("hq/game/sprite/pal/pal03", 8);
	} else {
		sprintf(filename, "8bits/game/sprite/spr%02d", n);
		NF_LoadSpriteGfx(filename, 127, 64, 64);
		NF_LoadSpritePal("8bits/game/sprite/spr8bits", 8);
	}
	NF_VramSpriteGfx(1, 127, 127, false);
	NF_VramSpritePal(1, 8, 8);
	NF_CreateSprite(1, 127, 127, 8, 96, y);
	NF_SpriteLayer(1, 127, 3);

	// Crea las scanlines si es necesario
	if (!GAMEOPTIONS[0].remake) CreateScanlines();

	// Actualiza la pantalla
	UpdateBothScreens2D();

	// Inicializa la animacion
	LOADING.frame = 0;
	LOADING.timer = 0;
	LOADING.bg_x = 0;

	// Prepara la interrupcion
	irqSet(IRQ_VBLANK, LoadingAnimation);
	irqEnable(IRQ_VBLANK);

	// FadeIn
	FadeIn(3, 64);

}



// Funcion LoadingOut();
void LoadingOut(void) {

	// FadeOut
	FadeOut(3, 64);

	// Deshabilita la interrupcion
	irqClear(IRQ_VBLANK);
	irqEnable(IRQ_VBLANK);

	// Destruye el fondo
	NF_ScrollBg(1, 3, 0, 0);
	NF_DeleteTiledBg(0, 3);
	NF_DeleteTiledBg(1, 3);
	NF_UnloadTiledBg("load");
	NF_UnloadTiledBg("loadbg");

	// Destruye el Sprite
	NF_DeleteSprite(1, 127);
	NF_FreeSpriteGfx(1, 127);
	NF_UnloadSpriteGfx(127);

	if (!GAMEOPTIONS[0].remake) DeleteScanlines();

}



// Funcion LoadingAnimation();
void LoadingAnimation(void) {

	// Deshabilita la interrupcion
	irqDisable(IRQ_VBLANK);

	// Calculo de la animacion
	LOADING.timer ++;
	if (LOADING.timer > 7) {
		LOADING.timer = 0;
		LOADING.frame ++;
		if (LOADING.frame > 3) LOADING.frame = 0;
		// Anima el sprite
		NF_SpriteFrame(1, 127, LOADING.frame);
		NF_SpriteOamSet(1);
		oamUpdate(&oamSub);
	}

	// Mueve el fondo
	LOADING.bg_x ++;
	if (LOADING.bg_x > 192) LOADING.bg_x -= 192;
	NF_ScrollBg(1, 3, LOADING.bg_x, 0);

	// Vuelve a habilitar el VBLANK
	irqEnable(IRQ_VBLANK);

}