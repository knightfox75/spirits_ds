#ifndef __DAMAGE_H__
#define __DAMAGE_H__



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

// Includes propietarios NDS
#include <nds.h>





// Funcion CharacterLiveControl();
extern bool CharacterLiveControl(void);
// Control general de la vida del personaje



// Funcion AlivePosition();
void AlivePosition(void);
// Almacena la ultima posicion valida del personaje



// Funcion FallDamage();
void FallDamage(void);
// Calcula si hay daño en una caida





#endif
