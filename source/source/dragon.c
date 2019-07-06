/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del evento
	"Guarida del Dragon"

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





// Funcion DragonEyeMain();
void DragonEyeMain(void) {

	DragonEyeAnimation();	// Animacion

}



// Funcion DragonEyeAnimation();
void DragonEyeAnimation(void) {

	// Variables
	bool update_thread = false;
	u8 next_thread = 0;

	// Acciones de la animacion
	switch(DRAGONEYE.animation) {

		// Coloca al personaje
		case 0:
			// Override de las teclas
			KEYHELD.up = false;
			KEYHELD.down = true;
			KEYHELD.left = false;
			KEYHELD.right = false;
			// Procesos
			CharacterMain();				// Control del personaje
			// Si el personaje se ha colocado, siguiente thread
			if (CHARACTER.pos_y > 1952) {
				next_thread = 1;
				update_thread = true;
			}
			break;

		// Abre los ojos (1)
		case 1:
			DRAGONEYE.frame_cnt ++;
			if (DRAGONEYE.frame_cnt > 4) {
				DRAGONEYE.frame_cnt = 0;
				DRAGONEYE.frame ++;
				if (DRAGONEYE.frame > 3) {
					DRAGONEYE.frame = 3;
					next_thread = 2;
					update_thread = true;
				}
			}
			break;

		// Espera (1)
		case 2:
			DRAGONEYE.frame_cnt ++;
			if (DRAGONEYE.frame_cnt > 15) {
				DRAGONEYE.frame_cnt = 0;
				next_thread = 3;
				update_thread = true;
			}
			break;

		// Cierra los ojos (1)
		case 3:
			DRAGONEYE.frame_cnt ++;
			if (DRAGONEYE.frame_cnt > 4) {
				DRAGONEYE.frame_cnt = 0;
				DRAGONEYE.frame --;
				if (DRAGONEYE.frame < 0) {
					DRAGONEYE.frame = 0;
					next_thread = 4;
					update_thread = true;
				}
			}
			break;

		// Abre los ojos (2)
		case 4:
			DRAGONEYE.frame_cnt ++;
			if (DRAGONEYE.frame_cnt > 2) {
				DRAGONEYE.frame_cnt = 0;
				DRAGONEYE.frame ++;
				if (DRAGONEYE.frame > 3) {
					DRAGONEYE.frame = 3;
					next_thread = 5;
					update_thread = true;
				}
			}
			break;

		// Cierra los ojos (2)
		case 5:
			DRAGONEYE.frame_cnt ++;
			if (DRAGONEYE.frame_cnt > 2) {
				DRAGONEYE.frame_cnt = 0;
				DRAGONEYE.frame --;
				if (DRAGONEYE.frame < 0) {
					DRAGONEYE.frame = 0;
					next_thread = 6;
					update_thread = true;
				}
			}
			break;

		// Abre los ojos (3)
		case 6:
			DRAGONEYE.frame_cnt ++;
			if (DRAGONEYE.frame_cnt > 2) {
				DRAGONEYE.frame_cnt = 0;
				DRAGONEYE.frame ++;
				if (DRAGONEYE.frame > 3) {
					DRAGONEYE.frame = 3;
					next_thread = 7;
					update_thread = true;
				}
			}
			break;

		// Cierra los ojos (3)
		case 7:
			DRAGONEYE.frame_cnt ++;
			if (DRAGONEYE.frame_cnt > 2) {
				DRAGONEYE.frame_cnt = 0;
				DRAGONEYE.frame --;
				if (DRAGONEYE.frame < 0) {
					DRAGONEYE.frame = 0;
					next_thread = 8;
					update_thread = true;
				}
			}
			break;

		// Abre los ojos (4)
		case 8:
			DRAGONEYE.frame_cnt ++;
			if (DRAGONEYE.frame_cnt > 4) {
				DRAGONEYE.frame_cnt = 0;
				DRAGONEYE.frame ++;
				if (DRAGONEYE.frame > 3) {
					DRAGONEYE.frame = 3;
					next_thread = 9;
					update_thread = true;
				}
			}
			break;

		// Espera (4)
		case 9:
			DRAGONEYE.frame_cnt ++;
			if (DRAGONEYE.frame_cnt > 30) {
				DRAGONEYE.frame_cnt = 0;
				next_thread = 10;
				update_thread = true;
			}
			break;

		// Mata al personaje
		case 10:
			// Mata al personaje
			CHARACTER.energy = 0;
			// Actualiza la barra de vida
			GUI.update_energy_bar = true;
			// Devuelve el control del juego
			MAINGAME.thread = GAMETHREAD_PLAYGAME;
			break;

		// Error trap
		default:
			break;

	}

	// Procesos comunes
	SpellMain();					// Control del lanzamiento de hechizos
	EngineBackgroundProcesses();	// Procesos comunes
	CollisionsMain();				// Gestion de colisiones entre sprites

	// Actualiza el thread si es necesario
	if (update_thread) DRAGONEYE.animation = next_thread;

}



// Funcion DragonEyeCamHide();
void DragonEyeCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		los ojos del Dragon
	-------------------------------------------------
	*/

	if (stage != 19) {
		// No lo esta en pantalla
		DRAGONEYE.on_screen[screen] = false;
		// Destruye los sprites
		if (DRAGONEYE.created[screen]) {
			DRAGONEYE.created[screen] = false;
			// Ojo izquierdo
			NF_DeleteSprite(screen, DRAGONEYE_SPR_ID);
			NF_FreeSpriteGfx(screen, DRAGONEYE_SPR_ID);
			// Ojo derecho
			NF_DeleteSprite(screen, (DRAGONEYE_SPR_ID + 1));
			NF_FreeSpriteGfx(screen, (DRAGONEYE_SPR_ID + 1));
		}
	}

}



// Funcion DragonEyeCamShow();
void DragonEyeCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		los ojos del Dragon
	-------------------------------------------------
	*/

	if (stage == 19) {
		// Esta en pantalla
		DRAGONEYE.on_screen[screen] = true;
		// Si no esta creado, crealo
		if (!DRAGONEYE.created[screen]) {
			DRAGONEYE.created[screen] = true;
			// Ojo izquierdo
			NF_VramSpriteGfx(screen, ID_DRAGONEYE, DRAGONEYE_SPR_ID, true);
			if (GAMEOPTIONS[0].remake) {
				NF_CreateSprite(screen, DRAGONEYE_SPR_ID, DRAGONEYE_SPR_ID, DRAGONEYE_SPR_PAL, 138, 48);
			} else {
				NF_CreateSprite(screen, DRAGONEYE_SPR_ID, DRAGONEYE_SPR_ID, DRAGONEYE_SPR_PAL, 136, 48);
			}
			NF_SpriteLayer(screen, DRAGONEYE_SPR_ID, SPRITES_LAYER);
			NF_HflipSprite(screen, DRAGONEYE_SPR_ID, false);
			// Ojo derecho
			NF_VramSpriteGfx(screen, ID_DRAGONEYE, (DRAGONEYE_SPR_ID + 1), true);
			if (GAMEOPTIONS[0].remake) {
				NF_CreateSprite(screen, (DRAGONEYE_SPR_ID + 1), (DRAGONEYE_SPR_ID + 1), DRAGONEYE_SPR_PAL, 184, 48);
			} else {
				NF_CreateSprite(screen, (DRAGONEYE_SPR_ID + 1), (DRAGONEYE_SPR_ID + 1), DRAGONEYE_SPR_PAL, 184, 48);
			}
			NF_SpriteLayer(screen, (DRAGONEYE_SPR_ID + 1), SPRITES_LAYER);
			NF_HflipSprite(screen, (DRAGONEYE_SPR_ID + 1), true);
		}
		// Actualiza el frame de animacion
		NF_SpriteFrame(screen, DRAGONEYE_SPR_ID, DRAGONEYE.frame);
		NF_SpriteFrame(screen, (DRAGONEYE_SPR_ID + 1), DRAGONEYE.frame);
	}

}
