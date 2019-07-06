#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de colisiones
	entre Sprites

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





// Funcion CollisionsMain();
void CollisionsMain(void);
// Nucleo de testeo de las colisiones entre Sprites



// Funcion CheckRectCollision();
extern bool CheckRectCollision(s32 xa1, s32 ya1, s32 xb1, s32 yb1, s32 xa2, s32 ya2, s32 xb2, s32 yb2);
// Verifica si hay colision entre dos rectangulos



// Funcion CollisionCharacterEnemy();
void CollisionCharacterEnemy(void);
// Verifica si hay alguna colision entre el personaje y los enemigos



// Funcion CollisionCharacterEagle();
void CollisionCharacterEagle(void);
// Verifica si hay alguna colision entre el personaje y la Aguila



// Funcion CollisionCharacterLamp();
void CollisionCharacterLamp(void);
// Verifica si hay alguna colision entre el personaje y las lamparas



// Funcion CollisionCharacterTrap();
void CollisionCharacterTrap(void);
// Verifica si hay alguna colision entre el personaje y las trampas



// Funcion CollisionCharacterFiretrap();
void CollisionCharacterFiretrap(void);
// Verifica si hay alguna colision entre el personaje y las trampas de fuego



// Funcion CollisionCharacterCat();
void CollisionCharacterCat(void);
// Verifica si hay alguna colision entre el personaje y el gato



// Funcion CollisionCharacterDevil();
void CollisionCharacterDevil(void);
// Verifica si hay alguna colision entre el personaje y el diablo



// Funcion CollisionCharacterArrow();
void CollisionCharacterArrow(void);
// Verifica si hay alguna colision entre el personaje y la flecha



// Funcion CollisionSpellEnemy();
void CollisionSpellEnemy(void);
// Verifica si hay alguna colision entre el hechizo y los enemigos



// Funcion CollisionSpellNpc();
void CollisionSpellNpc(void);
// Verifica si hay alguna colision entre el hechizo y los NPC





#endif
