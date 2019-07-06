/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del hechizo

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





// Funcion SpellCamHide();
void SpellCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visivilidad del hechizo
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (SPELL.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (SPELL.pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x < -16)
		||
		(spr_x > 272)
		||
		(spr_y < -16)
		||
		(spr_y > 208)
		||
		!SPELL.active
		) {
		// No lo esta
		SPELL.on_screen[screen] = false;
		// Destruye el sprite
		if (SPELL.created[screen]) {
			SPELL.created[screen] = false;
			NF_DeleteSprite(screen, SPELL_SPR_ID);
			NF_FreeSpriteGfx(screen, SPELL_SPR_ID);
		}
	}

}



// Funcion SpellCamShow();
void SpellCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;

	/*
	-------------------------------------------------
		Gestiona la visibilidad de las lamparas
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (SPELL.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (SPELL.pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x >= -16)
		&&
		(spr_x <= 272)
		&&
		(spr_y >= -16)
		&&
		(spr_y <= 208)
		&&
		SPELL.active
		) {
		// Esta en pantalla
		SPELL.on_screen[screen] = true;
		SPELL.scr_x[screen] = spr_x;
		SPELL.scr_y[screen] = spr_y;
		// Si no esta creado, crealo
		if (!SPELL.created[screen]) {
			SPELL.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_SPELL, SPELL_SPR_ID, true);
			NF_CreateSprite(screen, SPELL_SPR_ID, SPELL_SPR_ID, SPELL_SPR_PAL, (SPELL.scr_x[screen] - SPELL.spr_left), (SPELL.scr_y[screen] - SPELL.spr_up));
			NF_SpriteLayer(screen, SPELL_SPR_ID, SPRITES_LAYER);
			NF_HflipSprite(screen, SPELL_SPR_ID, SPELL.flip);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, SPELL_SPR_ID, (SPELL.scr_x[screen] - SPELL.spr_left), (SPELL.scr_y[screen] - SPELL.spr_up));
		NF_SpriteFrame(screen, SPELL_SPR_ID, SPELL.frame);
	} 

}



// Funcion SpellMain();
void SpellMain(void) {

	// Al pulsar Y, si es posible, lanza el hechizo
	SpellShot();

	// Si has lanzado el hechizo y has llegado al frame correcto, crealo
	SpellCreate();

	// Mueve el hechizo si esta activo
	SpellMove();

}





// Funcion SpellShot();
void SpellShot(void) {

	// Si se pulsa Y, verifica si se puede disparar el hechizo
	if (KEYPRESS.y) {
		if (
			!CHARACTER.is_jump
			&&
			!CHARACTER.fall
			&&
			!CHARACTER.stair_down
			&&
			(CHARACTER.duck == 0)
			&&
			!SPELL.active
			&&
			!SPELL.shot
			&&
			!CHARACTER.spell
			) {
			// Lanzalo
			SPELL.shot = true;
			CHARACTER.spell = true;
		}
	}

}



// Funcion SpellCreate();
void SpellCreate(void) {

	// Si has lanzado el hechizo y has llegado al frame correcto, crealo
	if (
		!SPELL.active
		&&
		SPELL.shot
		&&
		(CHARACTER.frame == 15)
		) {

			// Lanza el hechizo
			if (CHARACTER.flip) {
				SPELL.pos_x = (CHARACTER.pos_x - 32);
				SPELL.speed = -SPELL_SPEED;
			} else {
				SPELL.pos_x = (CHARACTER.pos_x + 32);
				SPELL.speed = SPELL_SPEED;
			}
			SPELL.pos_y = CHARACTER.pos_y;
			SPELL.pos_fx = (SPELL.pos_x << 8);
			SPELL.pos_fy = (SPELL.pos_y << 8);
			SPELL.flip = CHARACTER.flip;
			SPELL.stage = CHARACTER.stage;

			// Inicializa la animacion
			SPELL.frame = 0;
			SPELL.frame_cnt = 0;

			// E indica que se la lanzado con exito
			SPELL.active = true;
			SPELL.shot = false;

			// Quita la vida por lanzar el hechizo
			CHARACTER.energy -= 8;
			if (CHARACTER.energy <= 0) CHARACTER.energy = 0;
			GUI.update_energy_bar = true;

	}

}



// Funcion SpellMove();
void SpellMove(void) {

	// Variables
	u16 t_left = T_AIR, t_right = T_AIR;

	// Si estas activo...
	if (SPELL.active) {

		// Calcula la nueva posicion
		SPELL.pos_fx += SPELL.speed;

		// Ajusta la posicion
		SPELL.pos_x = (SPELL.pos_fx >> 8);
		SPELL.pos_y = (SPELL.pos_fy >> 8);
		SPELL.stage = GetStage(SPELL.pos_x, SPELL.pos_y);

		// Animacion del hechizo
		SPELL.frame_cnt ++;
		if (SPELL.frame_cnt > 5) {
			SPELL.frame_cnt = 0;
			SPELL.frame ++;
			if (SPELL.frame > 2) SPELL.frame = 0;
		}

		// Lee los dos tiles significativos de posicion
		t_left = NF_GetTile(MAINMAP_SLOT, (SPELL.pos_x - SPELL.left), SPELL.pos_y);
		t_right = NF_GetTile(MAINMAP_SLOT, (SPELL.pos_x + SPELL.right), SPELL.pos_y);

		// Si el hechizo se debe cancelar por...
		if (
			// Esta fuera de las dos pantallas
			(
			(!SPELL.on_screen[0] && !SPELL.on_screen[1])
			&&
			// Se ha cancelado
			!CHARACTER.spell
			)
			||
			// O le ha dado a un muro
			((t_left == T_WALL) || (t_right == T_WALL))
			) {
			SPELL.cancel = true;
		}

	}

}
