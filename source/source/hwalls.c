/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion de muros mobiles

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



// Funcion HwallGetSpriteId();
u16 HwallGetSpriteId(u8 screen) {

	// Variables
	u8 n = 0;
	u8 id = 255;

	// Busca una Id libre y asignala
	for (n = 0; n < HWALL_SPR_NUM; n ++) {
		if (!HWALL_SPR[screen].in_use[n]) {
			id = n;
			HWALL_SPR[screen].in_use[id] = true;
			n = HWALL_SPR_NUM;
		}
	}

	// Devuelve la ID
	return HWALL_SPR[screen].id[id];

}



// Funcion HwallFreeSpriteId();
void HwallFreeSpriteId(u8 screen, u16 id) {

	// Variables
	u8 n = 0;

	// Busca una Id libre y asignala
	for (n = 0; n < HWALL_SPR_NUM; n ++) {
		if (HWALL_SPR[screen].id[n] == id) {
			HWALL_SPR[screen].in_use[n] = false;
			n = HWALL_SPR_NUM;
		}
	}

}



// Funcion CameraHwallHide();
void CameraHwallHide(u8 screen, u8 stage) {

	// Muro nº00
	HwallCam00Hide(screen, stage);

	// Muro nº01
	HwallCam01Hide(screen, stage);

	// Muro nº02
	HwallCam02Hide(screen, stage);

	// Muro nº03
	HwallCam03Hide(screen, stage);

}



// Funcion CameraHwallShow();
void CameraHwallShow(u8 screen, u8 stage) {

	// Muro nº00
	HwallCam00Show(screen, stage);

	// Muro nº01
	HwallCam01Show(screen, stage);

	// Muro nº02
	HwallCam02Show(screen, stage);

	// Muro nº03
	HwallCam03Show(screen, stage);

}



// Funcion HwallCam00Hide();
void HwallCam00Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes del muro mobil
		(Stage 16)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((HWALL[0].pos_x  + (part << 5)) - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (HWALL[0].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -32)
			||
			(spr_x > 256)
			||
			(spr_y < -16)
			||
			(spr_y > 192)
			||
			(stage != 16)
			) {
			// No lo esta
			HWALL[0].on_screen[screen][part] = false;
			// Destruye el sprite
			if (HWALL[0].created[screen][part]) {
				HWALL[0].created[screen][part] = false;
				NF_DeleteSprite(screen, HWALL[0].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, HWALL[0].vram_gfx[screen][part]);
				HwallFreeSpriteId(screen, HWALL[0].spr_id[screen][part]);
				HWALL[0].spr_id[screen][part] = 255, HWALL[0].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion HwallCam00Show();
void HwallCam00Show(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;
	u16 id = 0;


	/*
	-------------------------------------------------
		Gestion de las partes del muro mobil
		(Stage 16)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((HWALL[0].pos_x  + (part << 5)) - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (HWALL[0].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -32)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -16)
			&&
			(spr_y <= 192)
			&&
			(stage == 16)
			) {
			// Esta en pantalla
			HWALL[0].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 5)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!HWALL[0].created[screen][part]) {
				id = HwallGetSpriteId(screen);
				HWALL[0].spr_id[screen][part] = id, HWALL[0].vram_gfx[screen][part] = id;
				HWALL[0].created[screen][part] = true;
				NF_VramSpriteGfx(screen, HWALL[0].ram_gfx[part], HWALL[0].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, HWALL[0].spr_id[screen][part], HWALL[0].vram_gfx[screen][part], HWALLGFX[0].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, HWALL[0].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, HWALL[0].spr_id[screen][part], spr_x, spr_y);
		} 
	}

}



// Funcion HwallCam01Hide();
void HwallCam01Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes del muro mobil
		(Stage 16)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (HWALL[1].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((HWALL[1].pos_y + (part << 5)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -16)
			||
			(spr_x > 256)
			||
			(spr_y < -32)
			||
			(spr_y > 192)
			||
			(stage != 16)
			) {
			// No lo esta
			HWALL[1].on_screen[screen][part] = false;
			// Destruye el sprite
			if (HWALL[1].created[screen][part]) {
				HWALL[1].created[screen][part] = false;
				NF_DeleteSprite(screen, HWALL[1].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, HWALL[1].vram_gfx[screen][part]);
				HwallFreeSpriteId(screen, HWALL[1].spr_id[screen][part]);
				HWALL[1].spr_id[screen][part] = 255, HWALL[1].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion HwallCam01Show();
void HwallCam01Show(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;
	u16 id = 0;


	/*
	-------------------------------------------------
		Gestion de las partes del muro mobil
		(Stage 16)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (HWALL[1].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((HWALL[1].pos_y + (part << 5)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -16)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -32)
			&&
			(spr_y <= 192)
			&&
			(stage == 16)
			) {
			// Esta en pantalla
			HWALL[1].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 7)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!HWALL[1].created[screen][part]) {
				id = HwallGetSpriteId(screen);
				HWALL[1].spr_id[screen][part] = id, HWALL[1].vram_gfx[screen][part] = id;
				HWALL[1].created[screen][part] = true;
				NF_VramSpriteGfx(screen, HWALL[1].ram_gfx[part], HWALL[1].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, HWALL[1].spr_id[screen][part], HWALL[1].vram_gfx[screen][part], HWALLGFX[0].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, HWALL[1].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, HWALL[1].spr_id[screen][part], spr_x, spr_y);
		} 
	}

}



// Funcion HwallCam02Hide();
void HwallCam02Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes del muro mobil
		(Stage 16)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((HWALL[2].pos_x  + (part << 5)) - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (HWALL[2].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -32)
			||
			(spr_x > 256)
			||
			(spr_y < -16)
			||
			(spr_y > 192)
			||
			(stage != 16)
			) {
			// No lo esta
			HWALL[2].on_screen[screen][part] = false;
			// Destruye el sprite
			if (HWALL[2].created[screen][part]) {
				HWALL[2].created[screen][part] = false;
				NF_DeleteSprite(screen, HWALL[2].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, HWALL[2].vram_gfx[screen][part]);
				HwallFreeSpriteId(screen, HWALL[2].spr_id[screen][part]);
				HWALL[2].spr_id[screen][part] = 255, HWALL[2].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion HwallCam02Show();
void HwallCam02Show(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;
	u16 id = 0;


	/*
	-------------------------------------------------
		Gestion de las partes del muro mobil
		(Stage 16)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((HWALL[2].pos_x  + (part << 5)) - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (HWALL[2].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -32)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -16)
			&&
			(spr_y <= 192)
			&&
			(stage == 16)
			) {
			// Esta en pantalla
			HWALL[2].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 5)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!HWALL[2].created[screen][part]) {
				id = HwallGetSpriteId(screen);
				HWALL[2].spr_id[screen][part] = id, HWALL[2].vram_gfx[screen][part] = id;
				HWALL[2].created[screen][part] = true;
				NF_VramSpriteGfx(screen, HWALL[2].ram_gfx[part], HWALL[2].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, HWALL[2].spr_id[screen][part], HWALL[2].vram_gfx[screen][part], HWALLGFX[0].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, HWALL[2].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, HWALL[2].spr_id[screen][part], spr_x, spr_y);
		} 
	}

}



// Funcion HwallCam03Hide();
void HwallCam03Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes del muro mobil
		(Stage 17)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((HWALL[3].pos_x  + (part << 5)) - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (HWALL[3].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -32)
			||
			(spr_x > 256)
			||
			(spr_y < -16)
			||
			(spr_y > 192)
			||
			(stage != 17)
			) {
			// No lo esta
			HWALL[3].on_screen[screen][part] = false;
			// Destruye el sprite
			if (HWALL[3].created[screen][part]) {
				HWALL[3].created[screen][part] = false;
				NF_DeleteSprite(screen, HWALL[3].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, HWALL[3].vram_gfx[screen][part]);
				HwallFreeSpriteId(screen, HWALL[3].spr_id[screen][part]);
				HWALL[3].spr_id[screen][part] = 255, HWALL[3].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion HwallCam03Show();
void HwallCam03Show(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;
	u16 id = 0;


	/*
	-------------------------------------------------
		Gestion de las partes del muro mobil
		(Stage 17)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((HWALL[3].pos_x  + (part << 5)) - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (HWALL[3].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -32)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -16)
			&&
			(spr_y <= 192)
			&&
			(stage == 17)
			) {
			// Esta en pantalla
			HWALL[3].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 9)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!HWALL[3].created[screen][part]) {
				id = HwallGetSpriteId(screen);
				HWALL[3].spr_id[screen][part] = id, HWALL[3].vram_gfx[screen][part] = id;
				HWALL[3].created[screen][part] = true;
				NF_VramSpriteGfx(screen, HWALL[3].ram_gfx[part], HWALL[3].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, HWALL[3].spr_id[screen][part], HWALL[3].vram_gfx[screen][part], HWALLGFX[0].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, HWALL[3].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, HWALL[3].spr_id[screen][part], spr_x, spr_y);
		} 
	}

}