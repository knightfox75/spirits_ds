/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los items

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





// Funcion GetCristallball();
void GetCristallball(void) {

	// Variables
	u8 n = 0;

	// Modifica los slots de subcam disponibles
	SUBCAM.available[0] = false;
	SUBCAM.slot = 1;
	for (n = 1; n < 6; n ++) {		// Vuelve a poner esto a 6
		SUBCAM.available[n] = true;
	}

	// Oculta la bola
	CRISTALLBALL.show = false;
	// Marcala como conseguida
	CRISTALLBALL.done = true;

	// Muestra el Libro de hechizos y su pedestal
	SPELLBOOK.show = true;
	PEDESTAL[1].show = true;

	// Muestra la Varita magica
	MAGICWAND.show = true;

	// Muestra la Armadura
	ARMOR.show = true;
	// Muestra la Princesa
	PRINCESS.show = true;
	// Muestra al Aguila
	EAGLE.show = true;

	// Actualiza la GUI
	NF_SpriteFrame(1, GUI_SPRITE_CRISTALLBALL, 1);

	// Y recupera algo de vida (8 puntos)
	CHARACTER.energy += (8 << 3);
	if (CHARACTER.energy > (40 << 3)) CHARACTER.energy = (40 << 3);
	GUI.update_energy_bar = true;

	// Voz
	if (VOICE.can_play) {
		VOICE.id = VOICE_CRISTALLBALL;
		VOICE.play = true;
	}

	// Cambio de musica
	BGM.next = MOD_KINGDOM_SKY;

}



// Funcion GetSpellbook();
void GetSpellbook(void) {

	// Marca su slot en la subcam como no disponible
	SUBCAM.available[1] = false;

	// Oculta el Libro de hechizos
	SPELLBOOK.show = false;
	// Y marcalo como conseguido
	SPELLBOOK.done = true;
	// Si ya tenias la varita, cambia de BGM
	if (MAGICWAND.done) BGM.next = MOD_SWORD_STONE;

	// Cambia la subcamara al siguiente slot disponible
	while (!SUBCAM.available[SUBCAM.slot]) {
		SUBCAM.slot ++;
		if (SUBCAM.slot > 5) SUBCAM.slot = 1;
	}

	// Actualiza la GUI
	NF_SpriteFrame(1, GUI_SPRITE_SPELLBOOK, 1);

	// Y recupera algo de vida (8 puntos)
	CHARACTER.energy += (8 << 3);
	if (CHARACTER.energy > (40 << 3)) CHARACTER.energy = (40 << 3);
	GUI.update_energy_bar = true;

	// Voz
	if (VOICE.can_play) {
		VOICE.id = VOICE_SPELLBOOK;
		VOICE.play = true;
	}

}



// Funcion GetMagicwand();
void GetMagicwand(void) {

	// Marca su slot en la subcam como no disponible
	SUBCAM.available[2] = false;

	// Oculta el Libro de hechizos y su pedestal
	MAGICWAND.show = false;
	// Y marcalo como conseguido
	MAGICWAND.done = true;
	// Si ya tenias la varita, cambia de BGM
	if (SPELLBOOK.done) BGM.next = MOD_SWORD_STONE;

	// Cambia la subcamara al siguiente slot disponible
	while (!SUBCAM.available[SUBCAM.slot]) {
		SUBCAM.slot ++;
		if (SUBCAM.slot > 5) SUBCAM.slot = 1;
	}

	// Actualiza la GUI
	NF_SpriteFrame(1, GUI_SPRITE_MAGICWAND, 1);

	// Y recupera algo de vida (8 puntos)
	CHARACTER.energy += (8 << 3);
	if (CHARACTER.energy > (40 << 3)) CHARACTER.energy = (40 << 3);
	GUI.update_energy_bar = true;

	// Voz
	if (VOICE.can_play) {
		VOICE.id = VOICE_MAGICWAND;
		VOICE.play = true;
	}

}



// Funcion CameraItemHide();
void CameraItemHide(u8 screen, u8 stage) {

	CristallballCamHide(screen, stage);		// Bola de cristal y pedestal
	SpellbookCamHide(screen, stage);		// Libro de hechizos y pedestal
	MagicwandCamHide(screen, stage);		// Varita magica

}



// Funcion CameraItemShow();
void CameraItemShow(u8 screen, u8 stage) {

	CristallballCamShow(screen, stage);		// Bola de cristal y pedestal
	SpellbookCamShow(screen, stage);		// Libro de hechizos y pedestal
	MagicwandCamShow(screen, stage);		// Varita magica

}



// Funcion CristallballCamHide();
void CristallballCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visivilidad de
		la bola de cristal
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (CRISTALLBALL.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (CRISTALLBALL.pos_y - STAGE[stage].stg_top);
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
		!CRISTALLBALL.show
		) {
		// No lo esta
		CRISTALLBALL.on_screen[screen] = false;
		// Destruye el sprite
		if (CRISTALLBALL.created[screen]) {
			CRISTALLBALL.created[screen] = false;
			NF_DeleteSprite(screen, CRISTALLBALL_SPR_ID);
			NF_FreeSpriteGfx(screen, CRISTALLBALL_SPR_ID);
		}
	}


	/*
	-------------------------------------------------
		Gestion de las visibilidad del pedestal
		de la bola de cristal
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (PEDESTAL[0].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (PEDESTAL[0].pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x < -32)
		||
		(spr_x > 256)
		||
		(spr_y < -64)
		||
		(spr_y > 192)
		) {
		// No lo esta
		PEDESTAL[0].on_screen[screen] = false;
		// Destruye el sprite
		if (PEDESTAL[0].created[screen]) {
			PEDESTAL[0].created[screen] = false;
			NF_DeleteSprite(screen, PEDESTAL_0_SPR_ID);
			NF_FreeSpriteGfx(screen, PEDESTAL_0_SPR_ID);
		}
	}

}



// Funcion CristallballCamShow();
void CristallballCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la bola de cristal
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (CRISTALLBALL.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (CRISTALLBALL.pos_y - STAGE[stage].stg_top);
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
		CRISTALLBALL.show
		) {
		// Si no esta creado, crealo
		CRISTALLBALL.on_screen[screen] = true;
		if (!CRISTALLBALL.created[screen]) {
			CRISTALLBALL.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_BALL, CRISTALLBALL_SPR_ID, true);
			NF_CreateSprite(screen, CRISTALLBALL_SPR_ID, CRISTALLBALL_SPR_ID, ITEM_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, CRISTALLBALL_SPR_ID, SPRITES_LAYER);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, CRISTALLBALL_SPR_ID, spr_x, spr_y);
	}


	/*
	-------------------------------------------------
		Gestion de las visibilidad del pedestal
		de la bola de cristal
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (PEDESTAL[0].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (PEDESTAL[0].pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x >= -32)
		&&
		(spr_x <= 256)
		&&
		(spr_y >= -64)
		&&
		(spr_y <= 192)
		) {
		// Si no esta creado, crealo
		PEDESTAL[0].on_screen[screen] = true;
		if (!PEDESTAL[0].created[screen]) {
			PEDESTAL[0].created[screen] = true;
			NF_VramSpriteGfx(screen, ID_BASE, PEDESTAL_0_SPR_ID, true);
			NF_CreateSprite(screen, PEDESTAL_0_SPR_ID, PEDESTAL_0_SPR_ID, ITEM_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, PEDESTAL_0_SPR_ID, SPRITES_LAYER);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, PEDESTAL_0_SPR_ID, spr_x, spr_y);
	}

}



// Funcion SpellbookCamHide();
void SpellbookCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visivilidad del
		libro de hechizos
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (SPELLBOOK.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (SPELLBOOK.pos_y - STAGE[stage].stg_top);
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
		!SPELLBOOK.show
		) {
		// No lo esta
		SPELLBOOK.on_screen[screen] = false;
		// Destruye el sprite
		if (SPELLBOOK.created[screen]) {
			SPELLBOOK.created[screen] = false;
			NF_DeleteSprite(screen, SPELLBOOK_SPR_ID);
			NF_FreeSpriteGfx(screen, SPELLBOOK_SPR_ID);
		}
	}


	/*
	-------------------------------------------------
		Gestion de las visibilidad del pedestal
		del libro de hechizos
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (PEDESTAL[1].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (PEDESTAL[1].pos_y - STAGE[stage].stg_top);
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
		!PEDESTAL[1].show
		) {
		// No lo esta
		PEDESTAL[1].on_screen[screen] = false;
		// Destruye el sprite
		if (PEDESTAL[1].created[screen]) {
			PEDESTAL[1].created[screen] = false;
			NF_DeleteSprite(screen, PEDESTAL_1_SPR_ID);
			NF_FreeSpriteGfx(screen, PEDESTAL_1_SPR_ID);
		}
	}

}



// Funcion SpellbookCamShow();
void SpellbookCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad del
		libro de hechizos
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (SPELLBOOK.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (SPELLBOOK.pos_y - STAGE[stage].stg_top);
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
		SPELLBOOK.show
		) {
		// Si no esta creado, crealo
		SPELLBOOK.on_screen[screen] = true;
		if (!SPELLBOOK.created[screen]) {
			SPELLBOOK.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_BOOK, SPELLBOOK_SPR_ID, true);
			NF_CreateSprite(screen, SPELLBOOK_SPR_ID, SPELLBOOK_SPR_ID, ITEM_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, SPELLBOOK_SPR_ID, SPRITES_LAYER);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, SPELLBOOK_SPR_ID, spr_x, spr_y);
	}


	/*
	-------------------------------------------------
		Gestion de las visibilidad del pedestal
		del libro de hechizos
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (PEDESTAL[1].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (PEDESTAL[1].pos_y - STAGE[stage].stg_top);
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
		PEDESTAL[1].show
		) {
		// Si no esta creado, crealo
		PEDESTAL[0].on_screen[screen] = true;
		if (!PEDESTAL[1].created[screen]) {
			PEDESTAL[1].created[screen] = true;
			NF_VramSpriteGfx(screen, ID_BASE, PEDESTAL_1_SPR_ID, true);
			NF_CreateSprite(screen, PEDESTAL_1_SPR_ID, PEDESTAL_1_SPR_ID, ITEM_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, PEDESTAL_1_SPR_ID, SPRITES_LAYER);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, PEDESTAL_1_SPR_ID, spr_x, spr_y);
	}

}



// Funcion MagicwandCamHide();
void MagicwandCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la varita magica
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (MAGICWAND.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (MAGICWAND.pos_y - STAGE[stage].stg_top);
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
		!MAGICWAND.show
		) {
		// No lo esta
		MAGICWAND.on_screen[screen] = false;
		// Destruye el sprite
		if (MAGICWAND.created[screen]) {
			MAGICWAND.created[screen] = false;
			NF_DeleteSprite(screen, MAGICWAND_SPR_ID);
			NF_FreeSpriteGfx(screen, MAGICWAND_SPR_ID);
		}
	}

}



// Funcion MagicwandCamShow();
void MagicwandCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la varita magica
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (MAGICWAND.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (MAGICWAND.pos_y - STAGE[stage].stg_top);
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
		MAGICWAND.show
		) {
		// Si no esta creado, crealo
		MAGICWAND.on_screen[screen] = true;
		if (!MAGICWAND.created[screen]) {
			MAGICWAND.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_WAND, MAGICWAND_SPR_ID, true);
			NF_CreateSprite(screen, MAGICWAND_SPR_ID, MAGICWAND_SPR_ID, ITEM_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, MAGICWAND_SPR_ID, SPRITES_LAYER);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, MAGICWAND_SPR_ID, spr_x, spr_y);
	}

}
