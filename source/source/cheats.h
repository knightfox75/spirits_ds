#ifndef __CHEATS_H__
#define __CHEATS_H__



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

// Includes propietarios NDS
#include <nds.h>




// Funcion LoadDefaultCheatsData();
void LoadDefaultCheatsData(void);
// Inicializa los datos de los cheats



// Funcion CheatsInGame();
void CheatsInGame(void);
// Trucos del juego (in-game, debug)



// Funcion CheatsEnable();
void CheatsEnable(void);
// Mira si se introduce el codigo de activacion






#endif
