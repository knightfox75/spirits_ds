/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los Trucos

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



// Funcion LoadDefaultCheatsData();
void LoadDefaultCheatsData(void) {

	// Flag de trucos activos abajo
	CHEATS.enabled = false;

}



// Funcion CheatsInGame();
void CheatsInGame(void) {

	// Teletransporte
	if (KEYPRESS.select && KEYHELD.up) {

		switch (SUBCAM.slot) {

			case 0:		// Bola de cristal
				CHARACTER.pos_x = CRISTALLBALL.cam_x;
				CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
				CHARACTER.pos_y = (CRISTALLBALL.cam_y - 32);
				CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
				CHARACTER.immunity = CHARACTER_IMMUNITY;
				break;

			case 1:		// Libro de hechizos
				CHARACTER.pos_x = SPELLBOOK.cam_x;
				CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
				CHARACTER.pos_y = (SPELLBOOK.cam_y - 32);
				CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
				CHARACTER.immunity = CHARACTER_IMMUNITY;
				break;

			case 2:		// Varita de hechizos
				CHARACTER.pos_x = MAGICWAND.cam_x;
				CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
				CHARACTER.pos_y = (MAGICWAND.cam_y - 32);
				CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
				CHARACTER.immunity = CHARACTER_IMMUNITY;
				break;

			case 3:		// Armadura
				CHARACTER.pos_x = ARMOR.pos_x;
				CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
				CHARACTER.pos_y = ARMOR.pos_y;
				CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
				CHARACTER.immunity = CHARACTER_IMMUNITY;
				break;

			case 4:		// Princesa
				CHARACTER.pos_x = PRINCESS.pos_x;
				CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
				CHARACTER.pos_y = PRINCESS.pos_y;
				CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
				CHARACTER.immunity = CHARACTER_IMMUNITY;
				break;

			case 5:		// Eagle
				CHARACTER.pos_x = EAGLE.pos_x;
				CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
				CHARACTER.pos_y = EAGLE.pos_y;
				CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
				CHARACTER.immunity = CHARACTER_IMMUNITY;
				break;

			default:
				break;

		}

	}


	// Rellena vida
	if (KEYPRESS.select && KEYHELD.left) {
		CHARACTER.energy = (40 << 3);
		CHARACTER.damage = CHARACTER.energy;
		GUI.update_energy_bar = true;
	}

	// Recupera vidas
	if (KEYPRESS.select && KEYHELD.right) {
		CHARACTER.lives = 3;
		GUI.update_lives_counter = true;
	}

	// Muestra todo el mapa
	if (CHEATS.map) {
		if (KEYPRESS.select && KEYHELD.down && MINIMAP.active) {
			memset(NF_BUFFER_BGMAP[MINIMAP.rambuffer], 0, NF_TILEDBG[MINIMAP.rambuffer].mapsize);
			CHEATS.map = false;
			NF_UpdateVramMap(1, MINIMAP_FOG_LAYER);
		}
	}

}


// Funcion CheatsEnable();
void CheatsEnable(void) {

	// Verifica la secuencia de activacion
	switch (CHEATS.steep) {

		case 0:
			if (KEYPRESS.up) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 1:
			if (KEYPRESS.up) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 2:
			if (KEYPRESS.down) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 3:
			if (KEYPRESS.down) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 4:
			if (KEYPRESS.left) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 5:
			if (KEYPRESS.right) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 6:
			if (KEYPRESS.left) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 7:
			if (KEYPRESS.right) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 8:
			if (KEYPRESS.b) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 9:
			if (KEYPRESS.a) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 10:
			if (KEYPRESS.b) {
				CHEATS.steep ++;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		case 11:
			if (KEYPRESS.a) {
				CHEATS.steep ++;
				CHEATS.enabled = true;
			} else {
				if (KEYPRESS.up || KEYPRESS.down || KEYPRESS.left || KEYPRESS.right || KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y || KEYPRESS.l || KEYPRESS.r) CHEATS.steep = 0;
			}
			break;

		default:
			break;

	}

}