/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la muerte
	del personaje

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





// Funcion CharacterLiveControl();
bool CharacterLiveControl(void) {

	// Variables
	bool status = true;

	// Si la vida del personaje ha llegado a 0
	if (CHARACTER.energy == 0) {
		// Resta una vida
		CHARACTER.lives --;
		if (CHARACTER.lives < 0) CHARACTER.lives = 0;
		// Actualiza el contador de vidas
		GUI.update_lives_counter = true;
		// Indicalo
		status = false;
	} else {
		// Si sigues vivo, registra tu posicion al cambiar de stage, si no estas sufriendo daños
		if (CHARACTER.energy == CHARACTER.damage) {
			CharacterRevivePoint();
		} else {
			CHARACTER.damage = CHARACTER.energy;
		}
	}

	// Devuelve el resultado
	return status;

}



// Funcion FallDamage();
void FallDamage(void) {

	// Variables
	s32 damage = 0;

	// Calcula la posicion final de la caida
	damage = ((CHARACTER.pos_y - CHARACTER.fall_y) - 176);

	// Si hay daño...
	if (damage > 0) {
		// Quita la vida y actualiza la barra
		CHARACTER.energy -= damage;
		if (CHARACTER.energy <= 0) CHARACTER.energy = 0;
		GUI.update_energy_bar = true;
	}

}
