/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion de las trampas

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



// Funcion TrapGetSpriteId();
u16 TrapGetSpriteId(u8 screen) {

	// Variables
	u8 n = 0;
	u8 id = 255;

	// Busca una Id libre y asignala
	for (n = 0; n < TRAP_SPR_NUM; n ++) {
		if (!TRAP_SPR[screen].in_use[n]) {
			id = n;
			TRAP_SPR[screen].in_use[id] = true;
			n = TRAP_SPR_NUM;
		}
	}

	// Devuelve la ID
	return TRAP_SPR[screen].id[id];

}



// Funcion TrapFreeSpriteId();
void TrapFreeSpriteId(u8 screen, u16 id) {

	// Variables
	u8 n = 0;

	// Busca una Id libre y asignala
	for (n = 0; n < TRAP_SPR_NUM; n ++) {
		if (TRAP_SPR[screen].id[n] == id) {
			TRAP_SPR[screen].in_use[n] = false;
			n = TRAP_SPR_NUM;
		}
	}

}



// Funcion CameraTrapHide();
void CameraTrapHide(u8 screen, u8 stage) {

	// Trampa nº00
	TrapCam00Hide(screen, stage);

	// Trampa nº01
	TrapCam01Hide(screen, stage);

}



// Funcion TrapRearm();
void TrapRearm(bool force) {

	// Trampa nº00
	TrapRearm00(force);

	// Trampa nº01
	TrapRearm01(force);

	// Trampa nº02
	TrapRearm02(force);

}



// Funcion CameraTrapShow();
void CameraTrapShow(u8 screen, u8 stage) {

	// Trampa nº00
	TrapCam00Show(screen, stage);

	// Trampa nº01
	TrapCam01Show(screen, stage);

}



// Funcion TrapCam00Hide();
void TrapCam00Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes de la trampa
		(Stage 16)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((TRAP[0].pos_x  + (part * 48)) - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (TRAP[0].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -64)
			||
			(spr_x > 256)
			||
			(spr_y < -64)
			||
			(spr_y > 192)
			||
			(stage != 16)
			) {
			// No lo esta
			TRAP[0].on_screen[screen][part] = false;
			// Destruye el sprite
			if (TRAP[0].created[screen][part]) {
				TRAP[0].created[screen][part] = false;
				NF_DeleteSprite(screen, TRAP[0].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, TRAP[0].vram_gfx[screen][part]);
				TrapFreeSpriteId(screen, TRAP[0].spr_id[screen][part]);
				TRAP[0].spr_id[screen][part] = 255, TRAP[0].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion TrapCam00Show();
void TrapCam00Show(u8 screen, u8 stage) {

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
		Gestion de las partes de la trampa mobil
		(Stage 16)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((TRAP[0].pos_x  + (part * 48)) - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (TRAP[0].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -64)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -64)
			&&
			(spr_y <= 192)
			&&
			(stage == 16)
			) {
			// Esta en pantalla
			TRAP[0].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 6)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!TRAP[0].created[screen][part]) {
				id = TrapGetSpriteId(screen);
				TRAP[0].spr_id[screen][part] = id, TRAP[0].vram_gfx[screen][part] = id;
				TRAP[0].created[screen][part] = true;
				NF_VramSpriteGfx(screen, TRAP[0].ram_gfx[part], TRAP[0].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, TRAP[0].spr_id[screen][part], TRAP[0].vram_gfx[screen][part], TRAPGFX[0].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, TRAP[0].spr_id[screen][part], TRAPS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, TRAP[0].spr_id[screen][part], spr_x, spr_y);
		} 
	}

}



// Funcion TrapRearm00();
void TrapRearm00(bool force) {

	// Si la trampa esta armada
	if (TRAP[0].activated) {
		// Y no esta en el campo de vision en ninguna pantalla
		if (
			(!TRAP[0].on_screen[0][0]
			&&
			!TRAP[0].on_screen[0][1]
			&&
			!TRAP[0].on_screen[1][0]
			&&
			!TRAP[0].on_screen[1][1])
			||
			force
			) {
			// Rearma la trampa
			TRAP[0].activated = false;
			SWITCH[6].activated = false;
			// Reposiciona todos los elementos
			TRAP[0].pos_y = TRAP[0].trap_y;
			TRAP[0].pos_fy = (TRAP[0].pos_y << 8);
			SWITCH[5].pos_y = 1399;
			SWITCH[6].pos_y = 1399;
			SWITCH[7].pos_y = 1399;
		}
	}

}



// Funcion TrapCam01Hide();
void TrapCam01Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes de la trampa
		(Stage 17)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((TRAP[1].pos_x  + (part * 48)) - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (TRAP[1].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -64)
			||
			(spr_x > 256)
			||
			(spr_y < -64)
			||
			(spr_y > 192)
			||
			(stage != 17)
			) {
			// No lo esta
			TRAP[1].on_screen[screen][part] = false;
			// Destruye el sprite
			if (TRAP[1].created[screen][part]) {
				TRAP[1].created[screen][part] = false;
				NF_DeleteSprite(screen, TRAP[1].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, TRAP[1].vram_gfx[screen][part]);
				TrapFreeSpriteId(screen, TRAP[1].spr_id[screen][part]);
				TRAP[1].spr_id[screen][part] = 255, TRAP[1].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion TrapCam01Show();
void TrapCam01Show(u8 screen, u8 stage) {

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
		Gestion de las partes de la trampa
		(Stage 17)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((TRAP[1].pos_x  + (part * 48)) - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (TRAP[1].pos_y - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -64)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -64)
			&&
			(spr_y <= 192)
			&&
			(stage == 17)
			) {
			// Esta en pantalla
			TRAP[1].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 10)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!TRAP[1].created[screen][part]) {
				id = TrapGetSpriteId(screen);
				TRAP[1].spr_id[screen][part] = id, TRAP[1].vram_gfx[screen][part] = id;
				TRAP[1].created[screen][part] = true;
				NF_VramSpriteGfx(screen, TRAP[1].ram_gfx[part], TRAP[1].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, TRAP[1].spr_id[screen][part], TRAP[1].vram_gfx[screen][part], TRAPGFX[0].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, TRAP[1].spr_id[screen][part], TRAPS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, TRAP[1].spr_id[screen][part], spr_x, spr_y);
		} 
	}

}


// Funcion TrapRearm01();
void TrapRearm01(bool force) {

	// Si la trampa esta armada
	if (TRAP[1].activated) {
		// Y no esta en el campo de vision en ninguna pantalla
		if (
			(!TRAP[1].on_screen[0][0]
			&&
			!TRAP[1].on_screen[0][1]
			&&
			!TRAP[1].on_screen[1][0]
			&&
			!TRAP[1].on_screen[1][1])
			||
			force
			) {
			// Rearma la trampa
			TRAP[1].activated = false;
			SWITCH[10].activated = false;
			// Reposiciona todos los elementos
			TRAP[1].pos_y = TRAP[1].trap_y;
			TRAP[1].pos_fy = (TRAP[1].pos_y << 8);
			SWITCH[9].pos_y = 1607;
			SWITCH[10].pos_y = 1607;
		}
	}

}



// Funcion TrapRearm02();
void TrapRearm02(bool force) {

	// Variables
	u8 stage = 0;

	// Si la trampa esta armada
	if (HWALL[3].activated) {
		// Stage donde esta el personaje
		stage = GetStage(CHARACTER.pos_x, CHARACTER.pos_y);
		// Y no esta en el campo de vision en ninguna pantalla
		if (
			(!HWALL[3].on_screen[0][0]
			&&
			!HWALL[3].on_screen[0][1]
			&&
			!HWALL[3].on_screen[1][0]
			&&
			!HWALL[3].on_screen[1][1]
			&&
			stage != 18)
			||
			force
			) {
			// Rearma la trampa
			HWALL[3].activated = false;
			SWITCH[9].activated = false;
			// Reposiciona todos los elementos
			HWALL[3].pos_x = HWALL[3].hwall_x;
			HWALL[3].pos_fx = (HWALL[3].pos_x << 8);
			// Cierra la trampilla
			EventCloseHwall(3);
		}
	}

}




