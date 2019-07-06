/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los NPC

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




// Funcion CameraNpcHide();
void CameraNpcHide(u8 screen, u8 stage) {

	ArmorCamHide(screen, stage);		// Armadura
	PrincessCamHide(screen, stage);		// Princesa
	EagleCamHide(screen, stage);		// Aguila

}



// Funcion CameraNpcShow();
void CameraNpcShow(u8 screen, u8 stage) {

	ArmorCamShow(screen, stage);		// Armadura
	PrincessCamShow(screen, stage);		// Princesa
	EagleCamShow(screen, stage);		// Aguila

}



// Funcion NpcMain();
void NpcMain(void) {

	// Armadura
	if (ARMOR.show && !ARMOR.done) {
		ArmorAi();		
		ArmorMove();
	} else {
		// Deshabilita la IA, pero permite el ajuste de posicion despues de desencantarla
		if (ARMOR.done) {
			ARMOR.ai_jump = false;
			ARMOR.ai_left = false;
			ARMOR.ai_right = false;
			ARMOR.ai_up = false;
			ARMOR.ai_down = false;
			ArmorMove();
		}
	}

	// Princesa
	if (PRINCESS.show && !PRINCESS.done) {
		PrincessAi();
		PrincessMove();
	} else {
		// Deshabilita la IA, pero permite el ajuste de posicion despues de desencantarla
		if (PRINCESS.done) {
			PRINCESS.ai_jump = false;
			PRINCESS.ai_left = false;
			PRINCESS.ai_right = false;
			PRINCESS.ai_up = false;
			PRINCESS.ai_down = false;
			PrincessMove();
			PRINCESS.frame = 6;
			if (PRINCESS.pos_x > CHARACTER.pos_x) {
				PRINCESS.flip = false;
			} else {
				PRINCESS.flip = true;
			}
		}
	}

	// Aguila
	if (EAGLE.show && !EAGLE.done) {
		EagleAi();
		EagleMove();
	}

}
