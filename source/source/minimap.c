/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del minimapa

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



// Funcion DestroySubscreen();
void DestroySubscreen(void) {

	// Variables
	u8 n = 0;


	/*
	-------------------------------------------------
		Destruye los sprites
	-------------------------------------------------
	*/

	// Personaje
	CHARACTER.on_screen[1] = false;
	CHARACTER.scr_x[1] = -64;
	CHARACTER.scr_y[1] = -64;
	if (CHARACTER.created[1]) {
		CHARACTER.created[1] = false;
		NF_DeleteSprite(1, CHARACTER_SPR_ID);
		NF_FreeSpriteGfx(1, CHARACTER_SPR_ID);
	}

	// Armadura
	ARMOR.on_screen[1] = false;
	ARMOR.scr_x[1] = -64;
	ARMOR.scr_y[1] = -64;
	if (ARMOR.created[1]) {
		ARMOR.created[1] = false;
		NF_DeleteSprite(1, ARMOR_SPR_ID);
		NF_FreeSpriteGfx(1, ARMOR_SPR_ID);
	}

	// Princesa
	PRINCESS.on_screen[1] = false;
	PRINCESS.scr_x[1] = -64;
	PRINCESS.scr_y[1] = -64;
	if (PRINCESS.created[1]) {
		PRINCESS.created[1] = false;
		NF_DeleteSprite(1, PRINCESS_SPR_ID);
		NF_FreeSpriteGfx(1, PRINCESS_SPR_ID);
	}

	// Aguila
	EAGLE.on_screen[1] = false;
	EAGLE.scr_x[1] = -64;
	EAGLE.scr_y[1] = -64;
	if (EAGLE.created[1]) {
		EAGLE.created[1] = false;
		NF_DeleteSprite(1, EAGLE_SPR_ID);
		NF_FreeSpriteGfx(1, EAGLE_SPR_ID);
	}

	// Bola de cristal
	CRISTALLBALL.on_screen[1] = false;
	if (CRISTALLBALL.created[1]) {
		CRISTALLBALL.created[1] = false;
		NF_DeleteSprite(1, CRISTALLBALL_SPR_ID);
		NF_FreeSpriteGfx(1, CRISTALLBALL_SPR_ID);
	}
	PEDESTAL[0].on_screen[1] = false;
	if (PEDESTAL[0].created[1]) {
		PEDESTAL[0].created[1] = false;
		NF_DeleteSprite(1, PEDESTAL_0_SPR_ID);
		NF_FreeSpriteGfx(1, PEDESTAL_0_SPR_ID);
	}

	// Libro de hechizos
	SPELLBOOK.on_screen[1] = false;
	if (SPELLBOOK.created[1]) {
		SPELLBOOK.created[1] = false;
		NF_DeleteSprite(1, SPELLBOOK_SPR_ID);
		NF_FreeSpriteGfx(1, SPELLBOOK_SPR_ID);
	}
	PEDESTAL[1].on_screen[1] = false;
	if (PEDESTAL[1].created[1]) {
		PEDESTAL[1].created[1] = false;
		NF_DeleteSprite(1, PEDESTAL_1_SPR_ID);
		NF_FreeSpriteGfx(1, PEDESTAL_1_SPR_ID);
	}

	// Varita magica
	MAGICWAND.on_screen[1] = false;
	if (MAGICWAND.created[1]) {
		MAGICWAND.created[1] = false;
		NF_DeleteSprite(1, MAGICWAND_SPR_ID);
		NF_FreeSpriteGfx(1, MAGICWAND_SPR_ID);
	}

	// Gouls
	for (n = 0; n < ENEMY_NUM_GOUL; n ++) {
		GOUL[n].on_screen[1] = false;
		GOUL[n].scr_x[1] = -64;
		GOUL[n].scr_y[1] = -64;
		if (GOUL[n].created[1]) {
			GOUL[n].created[1] = false;
			NF_DeleteSprite(1, GOUL[n].spr_id[1]);
			NF_FreeSpriteGfx(1, GOUL[n].vram_gfx[1]);
			EnemyFreeSpriteId(1, GOUL[n].spr_id[1]);
			GOUL[n].spr_id[1] = 255, GOUL[n].vram_gfx[1] = 255;
		}
	}

	// Phantoms
	for (n = 0; n < ENEMY_NUM_PHANTOM; n ++) {
		PHANTOM[n].on_screen[1] = false;
		PHANTOM[n].scr_x[1] = -64;
		PHANTOM[n].scr_y[1] = -64;
		// Destruye el sprite
		if (PHANTOM[n].created[1]) {
			PHANTOM[n].created[1] = false;
			NF_DeleteSprite(1, PHANTOM[n].spr_id[1]);
			NF_FreeSpriteGfx(1, PHANTOM[n].vram_gfx[1]);
			EnemyFreeSpriteId(1, PHANTOM[n].spr_id[1]);
			PHANTOM[n].spr_id[1] = 255, PHANTOM[n].vram_gfx[1] = 255;
		}
	}

	// Wolfs
	for (n = 0; n < ENEMY_NUM_WOLF; n ++) {
		WOLF[n].on_screen[1] = false;
		WOLF[n].scr_x[1] = -64;
		WOLF[n].scr_y[1] = -64;
		// Destruye el sprite
		if (WOLF[n].created[1]) {
			WOLF[n].created[1] = false;
			NF_DeleteSprite(1, WOLF[n].spr_id[1]);
			NF_FreeSpriteGfx(1, WOLF[n].vram_gfx[1]);
			EnemyFreeSpriteId(1, WOLF[n].spr_id[1]);
			WOLF[n].spr_id[1] = 255, WOLF[n].vram_gfx[1] = 255;
		}
	}

	// Gato
	CAT.on_screen[1] = false;
	CAT.scr_x[1] = -64;
	CAT.scr_y[1] = -64;
	if (CAT.created[1]) {
		CAT.created[1] = false;
		NF_DeleteSprite(1, CAT_SPR_ID);
		NF_FreeSpriteGfx(1, CAT_SPR_ID);
	}

	// Diablo arquero
	DEVIL.on_screen[1] = false;
	DEVIL.scr_x[1] = -64;
	DEVIL.scr_y[1] = -64;
	if (DEVIL.created[1]) {
		DEVIL.created[1] = false;
		NF_DeleteSprite(1, DEVIL_SPR_ID);
		NF_FreeSpriteGfx(1, DEVIL_SPR_ID);
	}
	ARROW.on_screen[1] = false;
	ARROW.scr_x[1] = -64;
	ARROW.scr_y[1] = -64;
	if (ARROW.created[1]) {
		ARROW.created[1] = false;
		NF_DeleteSprite(1, ARROW_SPR_ID);
		NF_FreeSpriteGfx(1, ARROW_SPR_ID);
	}

	// Interruptores
	for (n = 0; n < SWITCH_NUM; n ++) {
		SWITCH[n].on_screen[1] = false;
		if (SWITCH[n].created[1]) {
			SWITCH[n].created[1] = false;
			NF_DeleteSprite(1, SWITCH[n].spr_id[1]);
			NF_FreeSpriteGfx(1, SWITCH[n].vram_gfx[1]);
			SwitchFreeSpriteId(1, SWITCH[n].spr_id[1]);
			SWITCH[n].spr_id[1] = 255, SWITCH[n].vram_gfx[1] = 255;
		}
	}

	// Puertas
	CameraDoorHide(1, 0);

	// Semimuros
	CameraHwallHide(1, 0);

	// Trampas
	CameraTrapHide(1, 0);

	// Lamparas
	for (n = 0; n < LAMP_NUM; n ++) {
		LAMP[n].on_screen[1] = false;
		if (LAMP[n].created[1]) {
			LAMP[n].created[1] = false;
			NF_DeleteSprite(1, LAMP_SPR_ID);
			NF_FreeSpriteGfx(1, LAMP_SPR_ID);
		}
	}

	// Hogueras
	for (n = 0; n < FIRETRAP_NUM; n ++) {
		FIRETRAP[n].on_screen[1] = false;
		if (FIRETRAP[n].created[1]) {
			FIRETRAP[n].created[1] = false;
			NF_DeleteSprite(1, FIRETRAP_SPR_ID);
			NF_FreeSpriteGfx(1, FIRETRAP_SPR_ID);
		}
	}

	// Antorchas y velas
	for (n = 0; n < TORCH_NUM; n ++) {
		TORCH[n].on_screen[1] = false;
		if (TORCH[n].created[1]) {
			TORCH[n].created[1] = false;
			NF_DeleteSprite(1, TORCH[n].spr_id[1]);
			TorchFreeSpriteId(1, TORCH[n].spr_id[1]);
			TORCH[n].spr_id[1] = 255;
		}
	}

	// Hechizo
	SPELL.on_screen[1] = false;
	if (SPELL.created[1]) {
		SPELL.created[1] = false;
		NF_DeleteSprite(1, SPELL_SPR_ID);
		NF_FreeSpriteGfx(1, SPELL_SPR_ID);
	}

	// Ojos del Dragon
	DRAGONEYE.on_screen[1] = false;
	if (DRAGONEYE.created[1]) {
		DRAGONEYE.created[1] = false;
		// Ojo izquierdo
		NF_DeleteSprite(1, DRAGONEYE_SPR_ID);
		NF_FreeSpriteGfx(1, DRAGONEYE_SPR_ID);
		// Ojo derecho
		NF_DeleteSprite(1, (DRAGONEYE_SPR_ID + 1));
		NF_FreeSpriteGfx(1, (DRAGONEYE_SPR_ID + 1));
	}



	/*
	-------------------------------------------------
		Destruye los fondos
	-------------------------------------------------
	*/

	// Borra los fondos del sub-screen
	for (n = 1; n < 4; n ++) {
		if (NF_TILEDBG_LAYERS[1][n].created) NF_DeleteTiledBg(1, n);
	}
	// Marca el stage 0
	CAMERA[1].current_stage = 0;

}



// Funcion CreateMinimap();
void CreateMinimap(void) {

	// Variables
	s16 n = 0;

	// Crea el fondo
	NF_CreateTiledBg(1, MINIMAP_LAYER, "minimap");
	NF_CreateTiledBg(1, MINIMAP_FOG_LAYER, "fogmap");

	// Crea el sprite Personaje
	NF_VramSpriteGfx(1, ID_MINIMAP, MINIMAP_SPRITE_CHARACTER, true);
	NF_CreateSprite(1, MINIMAP_SPRITE_CHARACTER, MINIMAP_SPRITE_CHARACTER, MINIMAP_SPR_PAL, -16, -16);
	// Crea el sprite de la "Bola de cristal", "Libro de hechizos" y "Varita magica"
	NF_VramSpriteGfx(1, (ID_MINIMAP + 1), MINIMAP_SPRITE_CRISTALLBALL, true);
	NF_CreateSprite(1, MINIMAP_SPRITE_CRISTALLBALL, MINIMAP_SPRITE_CRISTALLBALL, MINIMAP_SPR_PAL, -16, -16);
	NF_VramSpriteGfx(1, (ID_MINIMAP + 1), MINIMAP_SPRITE_SPELLBOOK, true);
	NF_CreateSprite(1, MINIMAP_SPRITE_SPELLBOOK, MINIMAP_SPRITE_SPELLBOOK, MINIMAP_SPR_PAL, -16, -16);
	NF_VramSpriteGfx(1, (ID_MINIMAP + 1), MINIMAP_SPRITE_MAGICWAND, true);
	NF_CreateSprite(1, MINIMAP_SPRITE_MAGICWAND, MINIMAP_SPRITE_MAGICWAND, MINIMAP_SPR_PAL, -16, -16);
	// Crea el sprite de la "Armadura" y "Princesa"
	NF_VramSpriteGfx(1, (ID_MINIMAP + 2), MINIMAP_SPRITE_ARMOR, true);
	NF_CreateSprite(1, MINIMAP_SPRITE_ARMOR, MINIMAP_SPRITE_ARMOR, MINIMAP_SPR_PAL, -16, -16);
	NF_VramSpriteGfx(1, (ID_MINIMAP + 2), MINIMAP_SPRITE_PRINCESS, true);
	NF_CreateSprite(1, MINIMAP_SPRITE_PRINCESS, MINIMAP_SPRITE_PRINCESS, MINIMAP_SPR_PAL, -16, -16);
	// Crea el sprite del "Aguila"
	NF_VramSpriteGfx(1, (ID_MINIMAP + 3), MINIMAP_SPRITE_EAGLE, true);
	NF_CreateSprite(1, MINIMAP_SPRITE_EAGLE, MINIMAP_SPRITE_EAGLE, MINIMAP_SPR_PAL, -16, -16);

	// Ajusta los parametros iniciales
	for (n = 0; n < MINIMAP_TOTAL_ITEMS; n ++) {
		NF_SpriteFrame(1, (MINIMAP_SPR_ID + n), 0);
		NF_SpriteLayer(1, (MINIMAP_SPR_ID + n), MINIMAP_FOG_LAYER);
	}

	// Control de animacion
	MINIMAP.frame = 0;
	MINIMAP.frame_cnt = 0;

}



// Funcion MinimapCamera();
void MinimapCamera(void) {

	// Variables
	s32 x = 0, y  = 0;

	// Calcula las coordenadas del fondo
	MINIMAP.bg_x = ((CHARACTER.pos_x >> 3) - 16);
	if (MINIMAP.bg_x < 0) MINIMAP.bg_x = 0;
	if (MINIMAP.bg_x > 447) MINIMAP.bg_x = 447;
	MINIMAP.bg_y = ((CHARACTER.pos_y >> 3) - 12);
	if (MINIMAP.bg_y < 0) MINIMAP.bg_y = 0;
	if (MINIMAP.bg_y > 159) MINIMAP.bg_y = 159;

	// Control de animacion
	MINIMAP.frame_cnt ++;
	if (MINIMAP.frame_cnt > 5) {
		MINIMAP.frame_cnt = 0;
		MINIMAP.frame ++;
		if (MINIMAP.frame > 6) MINIMAP.frame = 0;
	}

	// Marca "Bola de cristal"
	if (CRISTALLBALL.show) {
		x = ((CRISTALLBALL.pos_x >> 3) - MINIMAP.bg_x) + 32;
		if (x < -16) x = -16;
		if (x > 271) x = 271;
		y = ((CRISTALLBALL.pos_y >> 3) - MINIMAP.bg_y) + 32;
		if (y < - 16) y = -16;
		if (y > 207) y = 207;
		NF_ShowSprite(1, MINIMAP_SPRITE_CRISTALLBALL, true);
		NF_SpriteFrame(1, MINIMAP_SPRITE_CRISTALLBALL, MINIMAP.frame);
		NF_MoveSprite(1, MINIMAP_SPRITE_CRISTALLBALL, x, y);
	} else {
		NF_ShowSprite(1, MINIMAP_SPRITE_CRISTALLBALL, false);
	}

	// Marca "Libro de hechizos"
	if (SPELLBOOK.show) {
		x = ((SPELLBOOK.pos_x >> 3) - MINIMAP.bg_x) + 32;
		if (x < -16) x = -16;
		if (x > 271) x = 271;
		y = ((SPELLBOOK.pos_y >> 3) - MINIMAP.bg_y) + 32;
		if (y < - 16) y = -16;
		if (y > 207) y = 207;
		NF_ShowSprite(1, MINIMAP_SPRITE_SPELLBOOK, true);
		NF_SpriteFrame(1, MINIMAP_SPRITE_SPELLBOOK, MINIMAP.frame);
		NF_MoveSprite(1, MINIMAP_SPRITE_SPELLBOOK, x, y);
	} else {
		NF_ShowSprite(1, MINIMAP_SPRITE_SPELLBOOK, false);
	}

	// Marca "Varita magica"
	if (MAGICWAND.show) {
		x = ((MAGICWAND.pos_x >> 3) - MINIMAP.bg_x) + 32;
		if (x < -16) x = -16;
		if (x > 271) x = 271;
		y = ((MAGICWAND.pos_y >> 3) - MINIMAP.bg_y) + 32;
		if (y < - 16) y = -16;
		if (y > 207) y = 207;
		NF_ShowSprite(1, MINIMAP_SPRITE_MAGICWAND, true);
		NF_SpriteFrame(1, MINIMAP_SPRITE_MAGICWAND, MINIMAP.frame);
		NF_MoveSprite(1, MINIMAP_SPRITE_MAGICWAND, x, y);
	} else {
		NF_ShowSprite(1, MINIMAP_SPRITE_MAGICWAND, false);
	}

	// Marca "Armadura"
	if (ARMOR.show && !ARMOR.done) {
		x = ((ARMOR.pos_x >> 3) - MINIMAP.bg_x) + 32;
		if (x < -16) x = -16;
		if (x > 271) x = 271;
		y = ((ARMOR.pos_y >> 3) - MINIMAP.bg_y) + 32;
		if (y < - 16) y = -16;
		if (y > 207) y = 207;
		NF_ShowSprite(1, MINIMAP_SPRITE_ARMOR, true);
		NF_SpriteFrame(1, MINIMAP_SPRITE_ARMOR, MINIMAP.frame);
		NF_MoveSprite(1, MINIMAP_SPRITE_ARMOR, x, y);
	} else {
		NF_ShowSprite(1, MINIMAP_SPRITE_ARMOR, false);
	}

	// Marca "Princesa"
	if (PRINCESS.show && !PRINCESS.done) {
		x = ((PRINCESS.pos_x >> 3) - MINIMAP.bg_x) + 32;
		if (x < -16) x = -16;
		if (x > 271) x = 271;
		y = ((PRINCESS.pos_y >> 3) - MINIMAP.bg_y) + 32;
		if (y < - 16) y = -16;
		if (y > 207) y = 207;
		NF_ShowSprite(1, MINIMAP_SPRITE_PRINCESS, true);
		NF_SpriteFrame(1, MINIMAP_SPRITE_PRINCESS, MINIMAP.frame);
		NF_MoveSprite(1, MINIMAP_SPRITE_PRINCESS, x, y);
	} else {
		NF_ShowSprite(1, MINIMAP_SPRITE_PRINCESS, false);
	}

	// Marca "Aguila"
	if (EAGLE.show && !EAGLE.done) {
		x = ((EAGLE.pos_x >> 3) - MINIMAP.bg_x) + 32;
		if (x < -16) x = -16;
		if (x > 271) x = 271;
		y = ((EAGLE.pos_y >> 3) - MINIMAP.bg_y) + 32;
		if (y < - 16) y = -16;
		if (y > 207) y = 207;
		NF_ShowSprite(1, MINIMAP_SPRITE_EAGLE, true);
		NF_SpriteFrame(1, MINIMAP_SPRITE_EAGLE, MINIMAP.frame);
		NF_MoveSprite(1, MINIMAP_SPRITE_EAGLE, x, y);
	} else {
		NF_ShowSprite(1, MINIMAP_SPRITE_EAGLE, false);
	}

	// Marca personaje
	x = ((CHARACTER.pos_x >> 3) - MINIMAP.bg_x) + 32;
	y = ((CHARACTER.pos_y >> 3) - MINIMAP.bg_y) + 32;
	NF_MoveSprite(1, MINIMAP_SPRITE_CHARACTER, x, y);
	NF_SpriteFrame(1, MINIMAP_SPRITE_CHARACTER, MINIMAP.frame);

	// Actualiza el mapa en VRAM de la niebla si es necesario
	if (MINIMAP.vram_update) NF_UpdateVramMap(1, MINIMAP_FOG_LAYER);

}



// Funcion DestroyMinimap();
void DestroyMinimap(void) {

	// Variables
	s16 n = 0;

	// Destruye el fondo
	if (NF_TILEDBG_LAYERS[1][MINIMAP_LAYER].created) NF_DeleteTiledBg(1, MINIMAP_LAYER);
	if (NF_TILEDBG_LAYERS[1][MINIMAP_FOG_LAYER].created) NF_DeleteTiledBg(1, MINIMAP_FOG_LAYER);

	// Destruye los sprites
	for (n = 0; n < MINIMAP_TOTAL_ITEMS; n ++) {
		NF_DeleteSprite(1, (MINIMAP_SPR_ID + n));
		NF_FreeSpriteGfx(1, (MINIMAP_SPR_ID + n));
	}

}



// Funcion UpdateMinimapFog();
void UpdateMinimapFog(void) {

	// Variables
	s32 x = 0, y  = 0;
	s8 ix = 0, iy = 0;

	// Resetea el flag
	MINIMAP.vram_update = false;

	// Actualizacion Niebla de guerra del minimapa
	x = (((CHARACTER.pos_x >> 3) + 40) >> 3);
	y = (((CHARACTER.pos_y >> 3) + 40) >> 3);
	for (iy = -2; iy < 2; iy ++) {
		for (ix = -2; ix < 2; ix ++) {
			// Si el tile es negro, eliminalo
			if (GetBgTile((x + ix), (y + iy), MINIMAP.rambuffer) != 0) {
				SetBgTile((x + ix), (y + iy), 0, MINIMAP.rambuffer);
				MINIMAP.vram_update = true;
			}
		}
	}

}
