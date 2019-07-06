#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos

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



// Funcion LoadGameDefaultData();
void LoadGameDefaultData(void);
// Carga los datos del juego



// Funcion LoadDefaultStageData();
void LoadDefaultStageData(void);
// Carga la info de las pantallas



// Funcion LoadDefaultRandomData();
void LoadDefaultRandomData(void);
// Carga la info de las posiciones aleatorias de los items y NPC



// Funcion LoadStartGameData();
void LoadStartGameData(void);
// Carga los datos de la partida



// Funcion GetRandomPlaces();
void GetRandomPlaces(void);
// Obten las 6 posiciones aleatorias para los items y NPC





#endif
