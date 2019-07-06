#ifndef __LOAD_H__
#define __LOAD_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de archivos

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



// Funcion LoadGameFiles();
void LoadGameFiles(void);
// Carga los archivos del juego



// Funcion LoadBackgrounds8bits();
void LoadBackgrounds8bits(void);
// Carga los fondos del juego en modo 8 bits



// Funcion LoadBackgroundsHq();
void LoadBackgroundsHq(void);
// Carga los fondos del juego en modo HQ (remake)



// Funcion LoadSprites8bits();
void LoadSprites8bits(void);
// Carga los sprites del juego en modo 8 bits



// Funcion LoadSpritesHq();
void LoadSpritesHq(void);
// Carga los sprites del juego en modo HQ (remake)



#endif
