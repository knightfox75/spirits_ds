#ifndef __CAT_H__
#define __CAT_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion del gato

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





// Funcion CatMain();
void CatMain(void);
// Gestion del Gato



// Funcion CatTimer
void CatTimer(void);
// Temporizador de accion del Gato



// Funcion CatGetPos();
extern bool CatGetPos(void);
// Busca una posicion valida de inicio, devuelve TRUE si a habido exito



// Funcion CatMove();
void CatMove(void);
// Mueve al gato



// Funcion CatWalk();
void CatWalk(void);
// El gato corretea



// Funcion CatVanish();
void CatVanish(void);
// El gato se desvanece



// Funcion CatFall();
void CatFall(void);
// El gato se cae?



// CatAdjustPosition();
void CatAdjustPosition(void);
// Ajusta la posicion del gato



// Funcion CatCheckRight();
extern u16 CatCheckRight(s8 add);
// Tiles a la derecha



// Funcion CatCheckLeft();
extern u16 CatCheckLeft(s8 add);
// Tiles a la izquierda



// Funcion CatCheckDown();
extern u16 CatCheckDown(s8 add);
// Tiles debajo



// Funcion CatCamHide();
void CatCamHide(u8 screen, u8 stage);
// Oculta al gato si es necesario



// Funcion CatCamShow();
void CatCamShow(u8 screen, u8 stage);
// Muestra al gato si es necesario





#endif
