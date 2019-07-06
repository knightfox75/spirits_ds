#ifndef __CREATE_H__
#define __CREATE_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de creacion del juego

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



// Funcion CreateGameStage();
void CreateGameStage(void);
// Crea todo el entorno del juego



// Funcion CreateVramSprites();
void CreateVramSprites(void);
// Manda los graficos de la RAM a la VRAM (Sprites siempre en VRAM)


// Funcion  CreatePalettes();
void CreatePalettes(void);
// Manda las paleta de la RAM a la VRAM



#endif
