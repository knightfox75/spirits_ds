#ifndef __CHARACTER_H__
#define __CHARACTER_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del personaje

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



// Funcion CharacterMain();
void CharacterMain(void);
// Engine de control del personaje



// Funcion CharacterCheckRight();
extern u16 CharacterCheckRight(s8 add);
// Devuelve el tile mas significativo a la derecha



// Funcion CharacterCheckLeft();
extern u16 CharacterCheckLeft(s8 add);
// Devuelve el tile mas significativo a la izquierda



// Funcion CharacterCheckUp();
extern u16 CharacterCheckUp(s8 add);
// Devuelve el tile mas significativo encima



// Funcion CharacterCheckDown();
extern u16 CharacterCheckDown(s8 add);
// Devuelve el tile mas significativo de debajo



// Funcion CharacterFall();
void CharacterFall(void);
// Ejecuta: Caida



// Funcion CharacterStairs();
void CharacterStairs(void);
// Ejecuta: Muevete por las escaleras



// Funcion CharacterJump();
void CharacterJump(void);
// Ejecuta: Salta



// Funcion CharacterWalk();
void CharacterWalk(void);
// Ejecuta: Anda



// Funcion CharacterAdjustPosition();
void CharacterAdjustPosition(void);
// Ajusta el personaje para que no traviese ningun muro, puerta, etc.



// Funcion CharacterAnimation();
void CharacterAnimation(void);
// Animacion del personaje



// Funcion CharacterMove();
void CharacterMove(void);
// Mueve al personaje



// Funcion CameraCharacterShowHide();
void CameraCharacterHide(u8 screen, u8 stage);
// Gestiona si desaparece el personaje en alguna camara



// Funcion CameraCharacterShow();
void CameraCharacterShow(u8 screen, u8 stage);
// Gestiona si aparece el personaje en alguna camara



// Funcion CharacterGetItem();
void CharacterGetItem(void);
// Gestiona si se puede coger algun item



// Funcion CharacterRevivePoint();
void CharacterRevivePoint(void);
// Si es necesario, calcula el punto de resurreccion



// Funcion CharacterBackupPos();
void CharacterBackupPos(void);
// Copia la situacion actual del personaje



// Funcion CharacterRestorePos();
void CharacterRestorePos(void);
// Restaura la posicion guardada del personaje





#endif
