/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion de las puertas

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



// Funcion DoorGetSpriteId();
u16 DoorGetSpriteId(u8 screen) {

	// Variables
	u8 n = 0;
	u8 id = 255;

	// Busca una Id libre y asignala
	for (n = 0; n < DOOR_SPR_NUM; n ++) {
		if (!DOOR_SPR[screen].in_use[n]) {
			id = n;
			DOOR_SPR[screen].in_use[id] = true;
			n = DOOR_SPR_NUM;
		}
	}

	// Devuelve la ID
	return DOOR_SPR[screen].id[id];

}



// Funcion DoorFreeSpriteId();
void DoorFreeSpriteId(u8 screen, u16 id) {

	// Variables
	u8 n = 0;

	// Busca una Id libre y asignala
	for (n = 0; n < DOOR_SPR_NUM; n ++) {
		if (DOOR_SPR[screen].id[n] == id) {
			DOOR_SPR[screen].in_use[n] = false;
			n = DOOR_SPR_NUM;
		}
	}

}



// Funcion CameraDoorHide();
void CameraDoorHide(u8 screen, u8 stage) {

	// Puerta nº00
	DoorCam00Hide(screen, stage);
	// Puerta nº01
	DoorCam01Hide(screen, stage);
	// Puerta nº02
	DoorCam02Hide(screen, stage);
	// Puerta nº03
	DoorCam03Hide(screen, stage);
	// Puerta nº04
	DoorCam04Hide(screen, stage);
	// Puerta nº05
	DoorCam05Hide(screen, stage);
	// Puerta nº06
	DoorCam06Hide(screen, stage);

}


// Funcion CameraDoorShow();
void CameraDoorShow(u8 screen, u8 stage) {

	// Puerta nº00
	DoorCam00Show(screen, stage);
	// Puerta nº01
	DoorCam01Show(screen, stage);
	// Puerta nº02
	DoorCam02Show(screen, stage);
	// Puerta nº03
	DoorCam03Show(screen, stage);
	// Puerta nº04
	DoorCam04Show(screen, stage);
	// Puerta nº05
	DoorCam05Show(screen, stage);
	// Puerta nº06
	DoorCam06Show(screen, stage);

}



// Funcion DoorCam00Hide();
void DoorCam00Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes de la puerta
		(Stage 1)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (DOOR[0].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((DOOR[0].pos_y + (part << 5)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -32)
			||
			(spr_x > 256)
			||
			(spr_y < -32)
			||
			(spr_y > 192)
			||
			(stage != 1)
			) {
			// No lo esta
			DOOR[0].on_screen[screen][part] = false;
			// Destruye el sprite
			if (DOOR[0].created[screen][part]) {
				DOOR[0].created[screen][part] = false;
				NF_DeleteSprite(screen, DOOR[0].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, DOOR[0].vram_gfx[screen][part]);
				DoorFreeSpriteId(screen, DOOR[0].spr_id[screen][part]);
				DOOR[0].spr_id[screen][part] = 255, DOOR[0].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion DoorCam00Show();
void DoorCam00Show(u8 screen, u8 stage) {

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
		Gestion de las partes de la puerta
		(Stage 1)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (DOOR[0].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((DOOR[0].pos_y + (part << 5)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -32)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -32)
			&&
			(spr_y <= 192)
			&&
			(stage == 1)
			) {
			// Esta en pantalla
			DOOR[0].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 0)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!DOOR[0].created[screen][part]) {
				id = DoorGetSpriteId(screen);
				DOOR[0].spr_id[screen][part] = id, DOOR[0].vram_gfx[screen][part] = id;
				DOOR[0].created[screen][part] = true;
				NF_VramSpriteGfx(screen, DOOR[0].ram_gfx[part], DOOR[0].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, DOOR[0].spr_id[screen][part], DOOR[0].vram_gfx[screen][part], DOORGFX[0].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, DOOR[0].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, DOOR[0].spr_id[screen][part], spr_x, spr_y);
		}
	}

}



// Funcion DoorCam01Hide();
void DoorCam01Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes de la puerta
		(Stage 4)
	-------------------------------------------------
	*/

	for (part = 0; part < 3; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (DOOR[1].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((DOOR[1].pos_y + (part << 5)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -32)
			||
			(spr_x > 256)
			||
			(spr_y < -32)
			||
			(spr_y > 192)
			||
			(stage != 4)
			) {
			// No lo esta
			DOOR[1].on_screen[screen][part] = false;
			// Destruye el sprite
			if (DOOR[1].created[screen][part]) {
				DOOR[1].created[screen][part] = false;
				NF_DeleteSprite(screen, DOOR[1].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, DOOR[1].vram_gfx[screen][part]);
				DoorFreeSpriteId(screen, DOOR[1].spr_id[screen][part]);
				DOOR[1].spr_id[screen][part] = 255, DOOR[1].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion DoorCam01Show();
void DoorCam01Show(u8 screen, u8 stage) {

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
		Gestion de las partes de la puerta
		(Stage 4)
	-------------------------------------------------
	*/

	for (part = 0; part < 3; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (DOOR[1].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((DOOR[1].pos_y + (part << 5)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -32)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -32)
			&&
			(spr_y <= 192)
			&&
			(stage == 4)
			) {
			// Esta en pantalla
			DOOR[1].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 1)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!DOOR[1].created[screen][part]) {
				id = DoorGetSpriteId(screen);
				DOOR[1].spr_id[screen][part] = id, DOOR[1].vram_gfx[screen][part] = id;
				DOOR[1].created[screen][part] = true;
				NF_VramSpriteGfx(screen, DOOR[1].ram_gfx[part], DOOR[1].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, DOOR[1].spr_id[screen][part], DOOR[1].vram_gfx[screen][part], DOORGFX[1].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, DOOR[1].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, DOOR[1].spr_id[screen][part], spr_x, spr_y);
		}
	}

}



// Funcion DoorCam02Hide();
void DoorCam02Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes de la puerta
		(Stage 5)
	-------------------------------------------------
	*/

	for (part = 0; part < 4; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (DOOR[2].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((DOOR[2].pos_y + (part << 5)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -32)
			||
			(spr_x > 256)
			||
			(spr_y < -32)
			||
			(spr_y > 192)
			||
			(stage != 5)
			) {
			// No lo esta
			DOOR[2].on_screen[screen][part] = false;
			// Destruye el sprite
			if (DOOR[2].created[screen][part]) {
				DOOR[2].created[screen][part] = false;
				NF_DeleteSprite(screen, DOOR[2].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, DOOR[2].vram_gfx[screen][part]);
				DoorFreeSpriteId(screen, DOOR[2].spr_id[screen][part]);
				DOOR[2].spr_id[screen][part] = 255, DOOR[2].vram_gfx[screen][part] = 255;
			}
		} 
	}

}



// Funcion DoorCam02Show();
void DoorCam02Show(u8 screen, u8 stage) {

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
		Gestion de las partes de la puerta
		(Stage 5)
	-------------------------------------------------
	*/

	for (part = 0; part < 4; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (DOOR[2].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((DOOR[2].pos_y + (part << 5)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -32)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -32)
			&&
			(spr_y <= 192)
			&&
			(stage == 5)
			) {
			// Esta en pantalla
			DOOR[2].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 2)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!DOOR[2].created[screen][part]) {
				id = DoorGetSpriteId(screen);
				DOOR[2].spr_id[screen][part] = id, DOOR[2].vram_gfx[screen][part] = id;
				DOOR[2].created[screen][part] = true;
				NF_VramSpriteGfx(screen, DOOR[2].ram_gfx[part], DOOR[2].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, DOOR[2].spr_id[screen][part], DOOR[2].vram_gfx[screen][part], DOORGFX[2].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, DOOR[2].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, DOOR[2].spr_id[screen][part], spr_x, spr_y);
		}
	}

}



// Funcion DoorCam03Hide();
void DoorCam03Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes de la puerta
		(Stage 7)
	-------------------------------------------------
	*/

	for (part = 0; part < 3; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (DOOR[3].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((DOOR[3].pos_y + (part << 6)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -32)
			||
			(spr_x > 256)
			||
			(spr_y < -64)
			||
			(spr_y > 192)
			||
			(stage != 7)
			) {
			// No lo esta
			DOOR[3].on_screen[screen][part] = false;
			// Destruye el sprite
			if (DOOR[3].created[screen][part]) {
				DOOR[3].created[screen][part] = false;
				NF_DeleteSprite(screen, DOOR[3].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, DOOR[3].vram_gfx[screen][part]);
				DoorFreeSpriteId(screen, DOOR[3].spr_id[screen][part]);
				DOOR[3].spr_id[screen][part] = 255, DOOR[3].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion DoorCam03Show();
void DoorCam03Show(u8 screen, u8 stage) {

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
		Gestion de las partes de la puerta
		(Stage 7)
	-------------------------------------------------
	*/

	for (part = 0; part < 3; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (DOOR[3].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((DOOR[3].pos_y + (part << 6)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -32)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -64)
			&&
			(spr_y <= 192)
			&&
			(stage == 7)
			) {
			// Esta en pantalla
			DOOR[3].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 3)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!DOOR[3].created[screen][part]) {
				id = DoorGetSpriteId(screen);
				DOOR[3].spr_id[screen][part] = id, DOOR[3].vram_gfx[screen][part] = id;
				DOOR[3].created[screen][part] = true;
				NF_VramSpriteGfx(screen, DOOR[3].ram_gfx[part], DOOR[3].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, DOOR[3].spr_id[screen][part], DOOR[3].vram_gfx[screen][part], DOORGFX[3].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, DOOR[3].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, DOOR[3].spr_id[screen][part], spr_x, spr_y);
		}
	}

}



// Funcion DoorCam04Hide();
void DoorCam04Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes de la puerta
		(Stage 14)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((DOOR[4].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x) - 8);
		spr_y = ((DOOR[4].pos_y + (part << 6)) - STAGE[stage].stg_top);
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
			(stage != 14)
			) {
			// No lo esta
			DOOR[4].on_screen[screen][part] = false;
			// Destruye el sprite
			if (DOOR[4].created[screen][part]) {
				DOOR[4].created[screen][part] = false;
				NF_DeleteSprite(screen, DOOR[4].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, DOOR[4].vram_gfx[screen][part]);
				DoorFreeSpriteId(screen, DOOR[4].spr_id[screen][part]);
				DOOR[4].spr_id[screen][part] = 255, DOOR[4].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion DoorCam04Show();
void DoorCam04Show(u8 screen, u8 stage) {

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
		Gestion de las partes de la puerta
		(Stage 14)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((DOOR[4].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x) - 8);
		spr_y = ((DOOR[4].pos_y + (part << 6)) - STAGE[stage].stg_top);
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
			(stage == 14)
			) {
			// Esta en pantalla
			DOOR[4].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 4)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!DOOR[4].created[screen][part]) {
				id = DoorGetSpriteId(screen);
				DOOR[4].spr_id[screen][part] = id, DOOR[4].vram_gfx[screen][part] = id;
				DOOR[4].created[screen][part] = true;
				NF_VramSpriteGfx(screen, DOOR[4].ram_gfx[part], DOOR[4].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, DOOR[4].spr_id[screen][part], DOOR[4].vram_gfx[screen][part], DOORGFX[4].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, DOOR[4].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, DOOR[4].spr_id[screen][part], spr_x, spr_y);
		}
	}

}



// Funcion DoorCam05Hide();
void DoorCam05Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes de la puerta
		(Stage 14)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((DOOR[5].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x) - 8);
		spr_y = ((DOOR[5].pos_y + (part << 6)) - STAGE[stage].stg_top);
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
			(stage != 14)
			) {
			// No lo esta
			DOOR[5].on_screen[screen][part] = false;
			// Destruye el sprite
			if (DOOR[5].created[screen][part]) {
				DOOR[5].created[screen][part] = false;
				NF_DeleteSprite(screen, DOOR[5].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, DOOR[5].vram_gfx[screen][part]);
				DoorFreeSpriteId(screen, DOOR[5].spr_id[screen][part]);
				DOOR[5].spr_id[screen][part] = 255, DOOR[5].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion DoorCam05Show();
void DoorCam05Show(u8 screen, u8 stage) {

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
		Gestion de las partes de la puerta
		(Stage 14)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = ((DOOR[5].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x) - 8);
		spr_y = ((DOOR[5].pos_y + (part << 6)) - STAGE[stage].stg_top);
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
			(stage == 14)
			) {
			// Esta en pantalla
			DOOR[5].on_screen[screen][part] = true;
			// Si no esta creado, crealo
			if (!DOOR[5].created[screen][part]) {
				id = DoorGetSpriteId(screen);
				DOOR[5].spr_id[screen][part] = id, DOOR[5].vram_gfx[screen][part] = id;
				DOOR[5].created[screen][part] = true;
				NF_VramSpriteGfx(screen, DOOR[5].ram_gfx[part], DOOR[5].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, DOOR[5].spr_id[screen][part], DOOR[5].vram_gfx[screen][part], DOORGFX[5].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, DOOR[5].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, DOOR[5].spr_id[screen][part], spr_x, spr_y);
		}
	}

}



// Funcion DoorCam06Hide();
void DoorCam06Hide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 part = 0;


	/*
	-------------------------------------------------
		Gestion de las partes de la puerta
		(Stage 17)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (DOOR[6].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((DOOR[6].pos_y + (part << 5)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x < -32)
			||
			(spr_x > 256)
			||
			(spr_y < -32)
			||
			(spr_y > 192)
			||
			(stage != 17)
			) {
			// No lo esta
			DOOR[6].on_screen[screen][part] = false;
			// Destruye el sprite
			if (DOOR[6].created[screen][part]) {
				DOOR[6].created[screen][part] = false;
				NF_DeleteSprite(screen, DOOR[6].spr_id[screen][part]);
				NF_FreeSpriteGfx(screen, DOOR[6].vram_gfx[screen][part]);
				DoorFreeSpriteId(screen, DOOR[6].spr_id[screen][part]);
				DOOR[6].spr_id[screen][part] = 255, DOOR[6].vram_gfx[screen][part] = 255;
			}
		}
	}

}



// Funcion DoorCam06Show();
void DoorCam06Show(u8 screen, u8 stage) {

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
		Gestion de las partes de la puerta
		(Stage 17)
	-------------------------------------------------
	*/

	for (part = 0; part < 2; part ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (DOOR[6].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = ((DOOR[6].pos_y + (part << 5)) - STAGE[stage].stg_top);
		// Calcula si esta en pantalla
		if (
			(spr_x >= -32)
			&&
			(spr_x <= 256)
			&&
			(spr_y >= -32)
			&&
			(spr_y <= 192)
			&&
			(stage == 17)
			) {
			// Esta en pantalla
			DOOR[6].on_screen[screen][part] = true;
			if ((screen == 0) && (EVENT.id == 8)) EVENT.on_main_screen = true;
			// Si no esta creado, crealo
			if (!DOOR[6].created[screen][part]) {
				id = DoorGetSpriteId(screen);
				DOOR[6].spr_id[screen][part] = id, DOOR[6].vram_gfx[screen][part] = id;
				DOOR[6].created[screen][part] = true;
				NF_VramSpriteGfx(screen, DOOR[6].ram_gfx[part], DOOR[6].vram_gfx[screen][part], true);
				NF_CreateSprite(screen, DOOR[6].spr_id[screen][part], DOOR[6].vram_gfx[screen][part], DOORGFX[0].pal, spr_x, spr_y);
				NF_SpriteLayer(screen, DOOR[6].spr_id[screen][part], DOORS_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, DOOR[6].spr_id[screen][part], spr_x, spr_y);
		}
	}

}


