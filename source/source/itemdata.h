#ifndef __ITEMDATA_H__
#define __ITEMDATA_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los datos
	iniciales de los items

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





// Funcion LoadDefaultItemData();
void LoadDefaultItemData(void);
// Carga los datos estaticos de los items



// Funcion SetCristallBall();
void SetCristallBall(u8 pos);
// Posiciona la Bola de cristal



// Funcion SetSpellbook();
void SetSpellbook(u8 pos);
// Posiciona el Libro de hechizos



// Funcion SetMagicwand();
void SetMagicwand(u8 pos);
// Posiciona la Varita magica




#endif
